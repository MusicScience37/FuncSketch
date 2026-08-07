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

from func_sketch._cpp import PointList
from func_sketch._gui.constants import (
    CURVE_COLORS,
    DEFAULT_PLOT_CONFIG,
    DEFAULT_PLOT_RANGE,
    NUM_CURVES,
)
from func_sketch._gui.curve_config_widget import CurveConfigWidget
from func_sketch._impl.curve_config import CurveConfig
from func_sketch._impl.curve_sampler import CurveSampler
from func_sketch._impl.sampled_curve import SampledCurve

LOGGER = logging.getLogger(__name__)


class CurveConfigListWidget(kivy.uix.boxlayout.BoxLayout):
    """Class of the widget for a list of curve configuration widgets.

    Note:
        Following properties can be used:
        - plot_range (writable)
        - plot_config (writable)
        - curve_configs (read only from other widgets)
        - sampled_curves (read only from other widgets)
    """

    curve_config_list_layout = kivy.properties.ObjectProperty()

    plot_range = kivy.properties.ObjectProperty(DEFAULT_PLOT_RANGE)
    plot_config = kivy.properties.ObjectProperty(DEFAULT_PLOT_CONFIG)
    curve_configs = kivy.properties.ListProperty(
        [
            CurveConfig(function_expression_str="", color=CURVE_COLORS[i])
            for i in range(NUM_CURVES)
        ]
    )
    sampled_curves = kivy.properties.ListProperty(
        [
            SampledCurve(samples=PointList([]), color=CURVE_COLORS[i])
            for i in range(NUM_CURVES)
        ]
    )

    def __init__(self, **kwargs) -> None:
        """Constructor."""
        super().__init__(**kwargs)
        self._curve_config_widgets: list[CurveConfigWidget] = []
        self._curve_sampler = CurveSampler(DEFAULT_PLOT_RANGE, DEFAULT_PLOT_CONFIG)

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
                curve_config=lambda _instance, _value, i=i: self._on_curve_config(i)
            )

    def _on_curve_config(self, index: int) -> None:
        """Callback when a curve configuration is changed.

        Args:
            index: Index of the curve configuration that changed.
        """
        curve_config = self._curve_config_widgets[index].curve_config
        self.curve_configs[index] = curve_config
        self._resample_one_curve(index)

    def _resample_one_curve(self, index: int) -> None:
        """Resample a curve.

        Args:
            index: Index of the curve to resample.
        """
        curve_config = self.curve_configs[index]
        if curve_config.function_expression_str == "":
            # Ignore empty expressions.
            sampled_curve = SampledCurve(
                samples=PointList([]), color=curve_config.color
            )
            self._curve_config_widgets[index].error_message = ""
        else:
            try:
                sampled_curve = self._curve_sampler(curve_config)
            except RuntimeError as e:
                self._curve_config_widgets[index].error_message = str(e)
                sampled_curve = SampledCurve(
                    samples=PointList([]), color=curve_config.color
                )
            else:
                self._curve_config_widgets[index].error_message = ""
        self.sampled_curves[index] = sampled_curve

    def _resample_all_curves(self) -> None:
        """Resample all curves."""
        for i in range(NUM_CURVES):
            self._resample_one_curve(i)

    def on_plot_range(self, _instance: object, _value: object) -> None:
        """Callback when the plot_range property is set."""
        self._curve_sampler.plot_range = self.plot_range
        self._resample_all_curves()

    def on_plot_config(self, _instance: object, _value: object) -> None:
        """Callback when the plot_config property is set."""
        self._curve_sampler.config = self.plot_config
        self._resample_all_curves()
