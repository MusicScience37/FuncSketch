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

"""Class of the widget for a list of curve configuration widgets."""

import logging
import time

import kivy.properties
import kivy.uix.boxlayout

from func_sketch._cpp import CurveSampler, PlotConfig, PlotRange, SampledCurve
from func_sketch._gui.constants import (
    CURVE_COLORS,
    DEFAULT_PLOT_CONFIG,
    DEFAULT_PLOT_RANGE,
    NUM_CURVES,
)
from func_sketch._gui.curve_spec_widget import CurveSpecWidget

LOGGER = logging.getLogger(__name__)


class CurveSpecListWidget(kivy.uix.boxlayout.BoxLayout):
    """Class of the widget for a list of curve specification widgets."""

    shared_state = kivy.properties.ObjectProperty()
    """Shared state object."""

    def __init__(self, **kwargs) -> None:
        """Constructor."""
        self._curve_spec_widgets: list[CurveSpecWidget] = []
        self._curve_sampler = CurveSampler(
            DEFAULT_PLOT_RANGE, DEFAULT_PLOT_CONFIG.sampling
        )
        super().__init__(**kwargs)

    def on_kv_post(self, base_widget: object) -> None:
        """Callback after the kv rules of this widget are applied."""
        super().on_kv_post(base_widget)

        for i in range(NUM_CURVES):
            curve_spec_widget = CurveSpecWidget(
                curve_name=f"Curve {i + 1}", curve_color=CURVE_COLORS[i]
            )
            self._curve_spec_widgets.append(curve_spec_widget)
            self.ids.curve_spec_list_layout.add_widget(curve_spec_widget)
            curve_spec_widget.bind(
                curve_spec=lambda _instance, _value, i=i: self._on_curve_spec_at_child(
                    i
                )
            )

    def on_shared_state(self, _instance: object, _value: object) -> None:
        """Callback when the shared_state property is set."""
        self.shared_state.bind(
            on_plot_range_changed=self._on_shared_plot_range,
            on_plot_config_changed=self._on_shared_plot_config,
        )

    def _on_curve_spec_at_child(self, index: int) -> None:
        """Callback when a curve specification is changed at a child widget.

        Args:
            index: Index of the curve specification that changed.
        """
        curve_spec = self._curve_spec_widgets[index].curve_spec
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

    def _resample_one_curve_without_event(self, index: int) -> SampledCurve:
        """Resample a curve without event dispatching.

        Args:
            index: Index of the curve to resample.

        Returns:
            SampledCurve: The resampled curve.
        """
        curve_spec = self.shared_state.curve_specs[index]
        if not curve_spec.function_expression_str:
            self._curve_spec_widgets[index].error_message = ""
            return SampledCurve(name=curve_spec.name, points=[], color=curve_spec.color)
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
            self._curve_spec_widgets[index].error_message = str(e)
            sampled_curve = SampledCurve(
                name=curve_spec.name, points=[], color=curve_spec.color
            )
        else:
            self._curve_spec_widgets[index].error_message = ""
        return sampled_curve

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
        self._curve_sampler.config = value.sampling
        self._resample_all_curves()
