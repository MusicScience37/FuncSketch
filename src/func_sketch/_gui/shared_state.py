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

"""Class of shared states."""

import logging

import kivy.event
import kivy.properties

from func_sketch._cpp import PlotConfig, PlotRange, PointList
from func_sketch._gui.constants import (
    CURVE_COLORS,
    DEFAULT_PLOT_CONFIG,
    DEFAULT_PLOT_RANGE,
    NUM_CURVES,
)
from func_sketch._impl.curve_config import CurveConfig
from func_sketch._impl.sampled_curve import SampledCurve

LOGGER = logging.getLogger(__name__)


class SharedState(kivy.event.EventDispatcher):
    """Class of shared states.

    This class uses custom events to notify changes of the states
    with the source of the change to prevent infinite loops of
    event dispatching. The properties of this class must not be
    updated directly from widgets. Instead, use the `update_xxx` methods
    to update the properties and `on_xxx_changed` events
    will be dispatched to notify the changes with the source of the change.
    """

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
        self.register_event_type("on_plot_range_changed")
        self.register_event_type("on_plot_config_changed")
        self.register_event_type("on_curve_config_changed")
        self.register_event_type("on_sampled_curve_changed")
        super().__init__(**kwargs)

    def update_plot_range(self, source: object, value: PlotRange) -> None:
        """Update range of the plot.

        Args:
            source (object): Source of the update.
            value (PlotRange): New range of the plot.
        """
        self.plot_range = value
        self.dispatch("on_plot_range_changed", source, value)

    def update_plot_config(self, source: object, value: PlotConfig) -> None:
        """Update configuration of the plot.

        Args:
            source (object): Source of the update.
            value (PlotConfig): New configuration of the plot.
        """
        self.plot_config = value
        self.dispatch("on_plot_config_changed", source, value)

    def update_curve_config(
        self, source: object, index: int, value: CurveConfig
    ) -> None:
        """Update configuration of a curve.

        Args:
            source (object): Source of the update.
            index (int): Index of the curve configuration to update.
            value (CurveConfig): New configuration of the curve.
        """
        self.curve_configs[index] = value
        self.dispatch("on_curve_config_changed", source, index, value)

    def update_sampled_curve(
        self, source: object, index: int, value: SampledCurve
    ) -> None:
        """Update a sampled curve.

        Args:
            source (object): Source of the update.
            index (int): Index of the sampled curve to update.
            value (SampledCurve): New sampled curve.
        """
        self.sampled_curves[index] = value
        self.dispatch("on_sampled_curve_changed", source, index, value)

    def on_plot_range_changed(self, source: object, value: PlotRange) -> None:
        """Event handler for plot range changes."""

    def on_plot_config_changed(self, source: object, value: PlotConfig) -> None:
        """Event handler for plot config changes."""

    def on_curve_config_changed(
        self, source: object, index: int, value: CurveConfig
    ) -> None:
        """Event handler for curve config changes."""

    def on_sampled_curve_changed(
        self, source: object, index: int, value: SampledCurve
    ) -> None:
        """Event handler for sampled curve changes."""
