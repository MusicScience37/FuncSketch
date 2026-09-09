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

import kivy.properties
import kivy.uix.boxlayout

from func_sketch._cpp import PlotConfig, PlotRange, PointList
from func_sketch._gui.constants import (
    CURVE_COLORS,
    DEFAULT_PLOT_CONFIG,
    DEFAULT_PLOT_RANGE,
    NUM_CURVES,
)
from func_sketch._gui.curve_config_widget import CurveConfigWidget
from func_sketch._impl.curve_sampler import CurveSampler
from func_sketch._impl.sampled_curve import SampledCurve

LOGGER = logging.getLogger(__name__)


class CurveConfigListWidget(kivy.uix.boxlayout.BoxLayout):
    """Class of the widget for a list of curve configuration widgets."""

    curve_config_list_layout = kivy.properties.ObjectProperty()
    """Layout widget for the list of curve configuration widgets."""

    shared_state = kivy.properties.ObjectProperty()
    """Shared state object."""

    def __init__(self, **kwargs) -> None:
        """Constructor."""
        self._curve_config_widgets: list[CurveConfigWidget] = []
        self._curve_sampler = CurveSampler(
            DEFAULT_PLOT_RANGE, DEFAULT_PLOT_CONFIG.sampling
        )
        super().__init__(**kwargs)

    def on_curve_config_list_layout(self, _instance: object, _value: object) -> None:
        """Callback when the curve_config_list_layout property is set."""
        for i in range(NUM_CURVES):
            curve_name = f"Curve {i + 1}"
            curve_config_widget = CurveConfigWidget(
                curve_name=curve_name, curve_color=CURVE_COLORS[i]
            )
            self._curve_config_widgets.append(curve_config_widget)
            self.curve_config_list_layout.add_widget(curve_config_widget)
            curve_config_widget.bind(
                curve_config=lambda _instance, _value, i=i: self._on_curve_config_at_child(
                    i
                )
            )

    def on_shared_state(self, _instance: object, _value: object) -> None:
        """Callback when the shared_state property is set."""
        self.shared_state.bind(
            on_plot_range_changed=self._on_shared_plot_range,
            on_plot_config_changed=self._on_shared_plot_config,
        )

    def _on_curve_config_at_child(self, index: int) -> None:
        """Callback when a curve configuration is changed at a child widget.

        Args:
            index: Index of the curve configuration that changed.
        """
        curve_config = self._curve_config_widgets[index].curve_config
        self.shared_state.update_curve_config(self, index, curve_config)
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
        curve_config = self.shared_state.curve_configs[index]
        try:
            # Empty expression is handled in CurveSampler.
            sampled_curve = self._curve_sampler(curve_config)
        except RuntimeError as e:
            self._curve_config_widgets[index].error_message = str(e)
            sampled_curve = SampledCurve(
                samples=PointList([]), color=curve_config.color
            )
        else:
            self._curve_config_widgets[index].error_message = ""
        return sampled_curve

    def _on_shared_plot_range(
        self, _instance: object, _source: object, value: PlotRange
    ) -> None:
        """Callback when the on_plot_range_changed event is dispatched."""
        self._curve_sampler.plot_range = value
        self._resample_all_curves()

    def _on_shared_plot_config(
        self, _instance: object, _source: object, value: PlotConfig
    ) -> None:
        """Callback when the on_plot_config_changed event is dispatched."""
        self._curve_sampler.config = value.sampling
        self._resample_all_curves()
