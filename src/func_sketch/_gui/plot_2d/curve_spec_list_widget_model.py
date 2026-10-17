# Copyright 2026 MusicScience37 (Kenta Kabashima)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Class of the view model of a list of curve specification widgets."""

import logging
import time

import kivy.event
import kivy.properties

from func_sketch._cpp import (
    CurveSampler,
    ExplicitCurveSpec,
    ParameterizedCurveSpec,
    PlotConfig,
    PlotRange,
    SampledExplicitCurve,
    SampledParameterizedCurve,
)
from func_sketch._gui.common.constants import (
    DEFAULT_PLOT_CONFIG,
    DEFAULT_PLOT_RANGE,
    NUM_CURVES,
)
from func_sketch._gui.plot_2d.curve_spec_widget_model import CurveSpecWidgetModel

LOGGER = logging.getLogger(__name__)


def _has_empty_expression(
    curve_spec: ExplicitCurveSpec | ParameterizedCurveSpec,
) -> bool:
    """Check whether any expression in a curve specification is empty.

    Args:
        curve_spec: Curve specification.

    Returns:
        True if any expression is empty, False otherwise.
    """
    if isinstance(curve_spec, ExplicitCurveSpec):
        return not curve_spec.function_expression_str
    if isinstance(curve_spec, ParameterizedCurveSpec):
        return not curve_spec.x_expression_str or not curve_spec.y_expression_str
    raise TypeError(f"Unsupported curve specification: {curve_spec}")


def _create_empty_sampled_curve(
    curve_spec: ExplicitCurveSpec | ParameterizedCurveSpec,
) -> SampledExplicitCurve | SampledParameterizedCurve:
    """Create an empty sampled curve for a curve specification.

    Args:
        curve_spec: Curve specification.

    Returns:
        Empty sampled curve of the type corresponding to the curve specification.
    """
    if isinstance(curve_spec, ExplicitCurveSpec):
        return SampledExplicitCurve(
            name=curve_spec.name, points=[], color=curve_spec.color
        )
    if isinstance(curve_spec, ParameterizedCurveSpec):
        return SampledParameterizedCurve(
            name=curve_spec.name, points=[], color=curve_spec.color
        )
    raise TypeError(f"Unsupported curve specification: {curve_spec}")


class CurveSpecListWidgetModel(kivy.event.EventDispatcher):
    """Class of the view model of a list of curve specification widgets."""

    shared_state = kivy.properties.ObjectProperty()
    """Shared state object."""

    show_legend = kivy.properties.BooleanProperty(False)
    """Whether to show the legend."""

    def __init__(self, **kwargs) -> None:
        """Constructor."""
        self._curve_sampler = CurveSampler(
            DEFAULT_PLOT_RANGE, DEFAULT_PLOT_CONFIG.sampling
        )

        self._curve_models: list[CurveSpecWidgetModel] = []

        super().__init__(**kwargs)

    @property
    def curve_models(self) -> list[CurveSpecWidgetModel]:
        """List of curve specification widget models."""
        return self._curve_models

    def init(self) -> None:
        """Initialize.

        Note:
            This method should be called after the shared state is set.
        """
        for i, curve in enumerate(self.shared_state.curve_specs):
            curve_model = CurveSpecWidgetModel(
                curve_sampler=self._curve_sampler, initial_curve_spec=curve
            )
            curve_model.bind(
                curve_spec=lambda _instance, _value, i=i: self._on_curve_spec_at_child(
                    i
                )
            )
            self._curve_models.append(curve_model)

        self.show_legend = self.shared_state.plot_config.legend.visible

        self.shared_state.bind(
            on_plot_range_changed=self._on_shared_plot_range,
            on_plot_config_changed=self._on_shared_plot_config,
        )

    def _on_shared_plot_range(
        self, _instance: object, _source: object, value: PlotRange
    ) -> None:
        """Callback when the on_plot_range_changed event is dispatched."""
        self._curve_sampler.range = value
        self._resample_all_curves()

    def _on_shared_plot_config(
        self, _instance: object, _source: object, value: PlotConfig
    ) -> None:
        """Callback when the on_plot_config_changed event is dispatched."""
        self.show_legend = value.legend.visible
        self._curve_sampler.config = value.sampling
        self._resample_all_curves()

    def _on_curve_spec_at_child(self, index: int) -> None:
        """Callback when a curve specification is changed at a child widget.

        Args:
            index: Index of the curve specification that changed.
        """
        curve_spec = self._curve_models[index].curve_spec
        self.shared_state.update_curve_spec(self, index, curve_spec)
        self._resample_one_curve(index)

    def _resample_one_curve(self, index: int) -> None:
        """Resample a curve.

        Args:
            index: Index of the curve to resample.
        """
        sampled_curve = self._resample_one_curve_without_event(index)
        self.shared_state.update_sampled_curve(self, index, sampled_curve)

    def _resample_all_curves(self) -> None:
        """Resample all curves."""
        sampled_curves = [
            self._resample_one_curve_without_event(i) for i in range(NUM_CURVES)
        ]
        self.shared_state.update_sampled_curve_all(self, sampled_curves)

    def _resample_one_curve_without_event(
        self, index: int
    ) -> SampledExplicitCurve | SampledParameterizedCurve:
        """Resample a curve without event dispatching.

        Args:
            index: Index of the curve to resample.

        Returns:
            SampledExplicitCurve | SampledParameterizedCurve: The resampled curve.
        """
        curve_spec = self.shared_state.curve_specs[index]
        if _has_empty_expression(curve_spec):
            self._curve_models[index].error_message = ""
            return _create_empty_sampled_curve(curve_spec)
        try:
            start_time = time.perf_counter()
            sampled_curve = self._curve_sampler(curve_spec)
            end_time = time.perf_counter()
            LOGGER.debug(
                "CurveSpecListWidget: Sampled %d points in %.2f ms.",
                len(sampled_curve.points),
                (end_time - start_time) * 1000.0,
            )
        except RuntimeError as e:
            self._curve_models[index].error_message = str(e)
            sampled_curve = _create_empty_sampled_curve(curve_spec)
        else:
            self._curve_models[index].error_message = ""
        return sampled_curve

    def on_show_legend(self, _instance: object, value: bool) -> None:
        """Callback when the show_legend property is changed."""
        config = self.shared_state.plot_config
        if config.legend.visible == value:
            return
        config.legend.visible = value
        self.shared_state.update_plot_config(self, config)
