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

"""Class of the view model of the widget to show plots."""

import logging
import time

import kivy.event
import kivy.properties
import numpy

from func_sketch._cpp import PlotConfig, PlotRange, Plotter, Point, SampledCurve
from func_sketch._gui.common.constants import (
    DEFAULT_PLOT_CONFIG,
    DEFAULT_PLOT_RANGE,
)

LOGGER = logging.getLogger(__name__)


class PlotWidgetModel(kivy.event.EventDispatcher):
    """Class of the view model of the widget to show plots."""

    shared_state = kivy.properties.ObjectProperty(None, allownone=True)
    """Shared state object."""

    image_buffer = kivy.properties.ObjectProperty(
        None, allownone=True, force_dispatch=True
    )
    """Buffer of the image."""

    def __init__(self, **kwargs) -> None:
        """Constructor."""
        self.register_event_type("on_image_buffer_written")
        super().__init__(**kwargs)

        self._plotter = Plotter(DEFAULT_PLOT_RANGE, DEFAULT_PLOT_CONFIG)

        self._widget_height: int = 300
        self._widget_width: int = 300
        self._normalized_image_height: int = 300
        self._normalized_image_width: int = 300

        # Initialize the image buffer with a small placeholder image.
        self.image_buffer = numpy.zeros((10, 10, 3), dtype=numpy.uint8)

        self._last_mouse_pos_in_pixel: tuple[float, float] | None = None
        self._current_touch_modifiers: list[str] = []

    def init(self) -> None:
        """Initialize.

        Note:
            This method should be called after the shared state is set.
        """
        self.shared_state.bind(
            on_plot_range_changed=self._on_shared_plot_range,
            on_plot_config_changed=self._on_shared_plot_config,
            on_sampled_curve_changed_any=self._on_shared_sampled_curve,
            on_fixed_desired_size_changed=self._on_shared_fixed_desired_size,
        )
        self._update_plot()

    def on_widget_size(self, size: tuple[float, float]) -> None:
        """Callback when the widget size is changed.

        Args:
            size (tuple[float, float]): The new size of the widget.
                As in Kivy, this is a tuple of (width, height) in pixels.
        """
        self._widget_height = int(size[1])
        self._widget_width = int(size[0])
        self._update_plot()

    def on_norm_image_size(self, value: tuple[float, float]) -> None:
        """Callback when the normalized image size is changed.

        Args:
            value (tuple[float, float]): The new normalized image size.
                As in Kivy, this is a tuple of (width, height) in pixels.
        """
        self._normalized_image_height = int(value[1])
        self._normalized_image_width = int(value[0])

    def _on_shared_plot_range(
        self, _instance: object, _source: object, value: PlotRange
    ) -> None:
        """Callback when the on_plot_range_changed event is dispatched."""
        self._plotter.range = value
        self._update_plot()

    def _on_shared_plot_config(
        self, _instance: object, _source: object, value: PlotConfig
    ) -> None:
        """Callback when the on_plot_config_changed event is dispatched."""
        self._plotter.config = value
        self._update_plot()

    def _on_shared_sampled_curve(self, _instance: object, _source: object) -> None:
        """Callback when the on_sampled_curve_changed event is dispatched."""
        self._update_plot()

    def _on_shared_fixed_desired_size(
        self, _instance: object, _source: object, _value: object
    ) -> None:
        """Callback when the on_fixed_desired_size_changed event is dispatched."""
        self._update_plot()

    def _update_image_buffer_if_needed(self) -> None:
        """Update the buffer of the image if needed."""
        if self.shared_state.fixed_desired_size is None:
            height = self._widget_height
            width = self._widget_width
        else:
            height, width = self.shared_state.fixed_desired_size
        self._plotter.desired_size(height=height, width=width)

        height, width = self._plotter.actual_size
        if height == self.image_buffer.shape[0] and width == self.image_buffer.shape[1]:
            return

        self.image_buffer = numpy.zeros((height, width, 3), dtype=numpy.uint8)
        self.shared_state.update_image_buffer(self, self.image_buffer)

    def _update_plot(self) -> None:
        """Update the plot."""
        sampled_curves: list[SampledCurve] = self.shared_state.sampled_curves
        self._plotter.legend_entries = [
            (curve.name, curve.color) for curve in sampled_curves if not curve.empty()
        ]

        self._update_image_buffer_if_needed()

        start_time = time.perf_counter()
        self._plotter.write(sampled_curves, self.image_buffer)
        end_time = time.perf_counter()
        LOGGER.debug(
            "PlotWidget: Plotted in %.2f ms.", (end_time - start_time) * 1000.0
        )
        self.dispatch("on_image_buffer_written")

    def on_mouse_pos_in_widget(self, relative_pos: tuple[float, float]) -> None:
        """Callback when the mouse position in the widget is changed.

        Args:
            relative_pos (tuple[float, float]): Mouse position relative to the widget.
        """
        plot_pos = self._widget_to_plot(relative_pos)

        if not self.shared_state.plot_range.contains(plot_pos):
            self.shared_state.update_mouse_pos_in_plot(self, None)
            return

        self.shared_state.update_mouse_pos_in_plot(self, plot_pos)

    def on_mouse_scroll(self, is_scroll_down: bool) -> None:
        """Callback when the mouse scroll event occurs.

        Args:
            is_scroll_down (bool): True if the event is a scroll down, False otherwise.
        """
        mouse_pos_in_plot = self.shared_state.mouse_pos_in_plot
        if mouse_pos_in_plot is None:
            return

        is_zoom_in = is_scroll_down
        factor = 2.0 if is_zoom_in else 0.5
        plot_range = self.shared_state.plot_range  # type: PlotRange
        plot_range.zoom(center=mouse_pos_in_plot, factor=factor)
        self.shared_state.update_plot_range(self, plot_range)

    def on_mouse_left_button_down(
        self, relative_pos: tuple[float, float], current_touch_modifiers: list[str]
    ) -> None:
        """Callback when the left mouse button is pressed down in the widget.

        Args:
            relative_pos (tuple[float, float]): Mouse position relative to the widget.
            current_touch_modifiers (list[str]): Current touch modifiers (e.g., ["ctrl"]).
        """
        if self.shared_state.mouse_pos_in_plot is None:
            return
        # Begin to pan the range or select the new range.
        self._current_touch_modifiers = current_touch_modifiers
        self._last_mouse_pos_in_pixel = relative_pos

    def on_mouse_left_button_dragging(self, relative_pos: tuple[float, float]) -> None:
        """Callback when the left mouse button is being dragged in the widget.

        Args:
            relative_pos (tuple[float, float]): Mouse position relative to the widget.
        """
        if (
            "ctrl" not in self._current_touch_modifiers
            and self._last_mouse_pos_in_pixel is not None
        ):
            # Pan the plot range.
            dx_pixel = relative_pos[0] - self._last_mouse_pos_in_pixel[0]
            dy_pixel = relative_pos[1] - self._last_mouse_pos_in_pixel[1]
            x_coeff, y_coeff = self._plotter.point_converter.image_to_plot_coefficient
            norm_height = self._normalized_image_height
            norm_width = self._normalized_image_width
            image_height, image_width = self._plotter.actual_size
            x_coeff = x_coeff * image_width / norm_width
            y_coeff = y_coeff * image_height / norm_height
            diff_plot = Point(x=-dx_pixel * x_coeff, y=-dy_pixel * y_coeff)

            plot_range = self.shared_state.plot_range
            plot_range.pan(diff_plot)
            self.shared_state.update_plot_range(self, plot_range)

            self._last_mouse_pos_in_pixel = relative_pos

    def on_mouse_left_button_up(self, relative_pos: tuple[float, float]) -> None:
        """Callback when the left mouse button is released in the widget.

        Args:
            relative_pos (tuple[float, float]): Mouse position relative to the widget.
        """
        if (
            "ctrl" in self._current_touch_modifiers
            and self._last_mouse_pos_in_pixel is not None
        ):
            mouse_pos_in_plot = self.shared_state.mouse_pos_in_plot
            if mouse_pos_in_plot is not None:
                # Finish to select the new range.
                first_pos_in_plot = self._widget_to_plot(self._last_mouse_pos_in_pixel)
                second_pos_in_plot = self._widget_to_plot(relative_pos)
                x_min = min(first_pos_in_plot.x, second_pos_in_plot.x)
                x_max = max(first_pos_in_plot.x, second_pos_in_plot.x)
                y_min = min(first_pos_in_plot.y, second_pos_in_plot.y)
                y_max = max(first_pos_in_plot.y, second_pos_in_plot.y)
                self.shared_state.update_plot_range(
                    self,
                    PlotRange(x_range=(x_min, x_max), y_range=(y_min, y_max)),
                )
        self._last_mouse_pos_in_pixel = None
        self._current_touch_modifiers = []

    def _widget_to_plot(self, pos_in_widget: tuple[float, float]) -> Point:
        """Convert a position in widget coordinates to plot coordinates.

        Args:
            pos_in_widget: Position in widget coordinates.

        Returns:
            Position in plot coordinates.
        """
        widget_height = self._widget_height
        widget_width = self._widget_width
        norm_width = self._normalized_image_width
        norm_height = self._normalized_image_height
        offset_x = (widget_width - norm_width) / 2
        offset_y = (widget_height - norm_height) / 2
        image_height, image_width = self._plotter.actual_size
        image_x = int((pos_in_widget[0] - offset_x) * image_width / norm_width)
        # Kivy's coordinate system has the origin at the bottom-left corner,
        # but OpenCV's coordinate system has the origin at the top-left corner.
        image_y = int(
            (norm_height - 1 - (pos_in_widget[1] - offset_y))
            * image_height
            / norm_height
        )
        return self._plotter.point_converter.convert_image_to_plot((image_x, image_y))

    def on_image_buffer_written(self) -> None:
        """Callback when the image buffer is written."""
