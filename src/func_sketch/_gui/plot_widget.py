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

"""Class of widgets to show plots."""

import logging

import kivy.core.window
import kivy.graphics.texture
import kivy.input
import kivy.properties
import kivy.uix.image
import numpy

from func_sketch._cpp import PlotConfig, PlotRange, Point
from func_sketch._gui.constants import DEFAULT_PLOT_CONFIG, DEFAULT_PLOT_RANGE
from func_sketch._impl.plotter import Plotter

LOGGER = logging.getLogger(__name__)


class PlotWidget(kivy.uix.image.Image):
    """Class of widgets to show plots."""

    shared_state = kivy.properties.ObjectProperty()
    """Shared state object."""

    def __init__(self, **kwargs) -> None:
        """Constructor."""
        super().__init__(**kwargs)

        self._range = DEFAULT_PLOT_RANGE
        self._plotter = Plotter(self._range, DEFAULT_PLOT_CONFIG)

        # Initialize with a small image to prevent errors in _prepare_texture.
        # This will be altered with the actual plot size later.
        self._image_buffer = numpy.zeros((1, 1, 3), dtype=numpy.uint8)
        self._prepare_texture()

        self._last_mouse_pos_in_pixel: tuple[float, float] | None = None
        self._current_touch_modifiers: list[str] = []
        kivy.core.window.Window.bind(mouse_pos=self._on_mouse_pos)

    def on_shared_state(self, _instance: object, _value: object) -> None:
        """Callback when the shared_state property is set."""
        self.shared_state.bind(
            on_plot_range_changed=self._on_shared_plot_range,
            on_plot_config_changed=self._on_shared_plot_config,
            on_sampled_curve_changed_any=self._on_shared_sampled_curve,
        )
        self._prepare_texture()
        self._update_plot()

    def on_size(self, _instance: object, _value: object) -> None:
        """Callback when the size of the widget is changed."""
        self._prepare_texture()
        self._update_plot()

    def _on_shared_plot_range(
        self, _instance: object, _source: object, value: PlotRange
    ) -> None:
        """Callback when the on_plot_range_changed event is dispatched."""
        self._range = value
        self._plotter.plot_range = self._range
        self._prepare_texture()
        self._update_plot()

    def _on_shared_plot_config(
        self, _instance: object, _source: object, value: PlotConfig
    ) -> None:
        """Callback when the on_plot_config_changed event is dispatched."""
        self._plotter.config = value
        self._prepare_texture()
        self._update_plot()

    def _on_shared_sampled_curve(self, _instance: object, _source: object) -> None:
        """Callback when the on_sampled_curve_changed event is dispatched."""
        self._update_plot()

    def _prepare_texture(self) -> None:
        """Prepare texture for the plot."""
        width, height = self.size
        self._plotter.desired_size(int(height), int(width))
        height, width = self._plotter.actual_size
        if (
            height == self._image_buffer.shape[0]
            and width == self._image_buffer.shape[1]
        ):
            return

        self._image_buffer = numpy.zeros((height, width, 3), dtype=numpy.uint8)
        self._texture = kivy.graphics.texture.Texture.create(
            size=(width, height), colorfmt="rgb"
        )
        self._texture.blit_buffer(
            self._image_buffer.tobytes(), colorfmt="rgb", bufferfmt="ubyte"
        )
        self._texture.flip_vertical()
        self.texture = self._texture

    def _update_plot(self) -> None:
        """Update the plot."""
        self._plotter(self.shared_state.sampled_curves, self._image_buffer)
        self._texture.blit_buffer(
            self._image_buffer.tobytes(), colorfmt="rgb", bufferfmt="ubyte"
        )

    def on_touch_down(self, touch: kivy.input.MotionEvent) -> bool:
        """Callback when a touch down event occurs.

        Args:
            touch: The touch event.

        Returns:
            True if the event is handled, False otherwise.
        """
        if self.collide_point(*touch.pos):
            if touch.is_mouse_scrolling:
                self._handle_scrolling(touch)
                return True
            elif touch.is_touch:
                if touch.button == "left":
                    self._handle_left_button_down(touch)
                    return True
                elif touch.button == "right":
                    # TODO Right click will be handled in the future.
                    return True

        return super().on_touch_down(touch)

    def _handle_scrolling(self, touch: kivy.input.MotionEvent) -> None:
        """Handle events of scrolling.

        Args:
            touch: The touch event.
        """
        mouse_pos_in_plot = self.shared_state.mouse_pos_in_plot
        if mouse_pos_in_plot is not None:
            # Zoom the plot range.
            is_zoom_in = touch.button == "scrolldown"
            self._zoom(center=mouse_pos_in_plot, is_zoom_in=is_zoom_in)

    def _handle_left_button_down(self, touch: kivy.input.MotionEvent) -> None:
        """Handle events when the left mouse button is pressed.

        Args:
            touch: The touch event.
        """
        mouse_pos_in_plot = self.shared_state.mouse_pos_in_plot
        if mouse_pos_in_plot is not None:
            # Begin to pan the range or select the new range.
            touch.grab(self)
            touch.push()
            touch.apply_transform_2d(self._to_widget_pos)
            self._last_mouse_pos_in_pixel = touch.pos
            self._current_touch_modifiers = kivy.core.window.Window.modifiers.copy()
            touch.pop()

    def on_touch_move(self, touch: kivy.input.MotionEvent) -> bool:
        """Callback when a touch move event occurs.

        Args:
            touch: The touch event.

        Returns:
            True if the event is handled, False otherwise.
        """
        if touch.grab_current is self and touch.is_touch and touch.button == "left":
            self._handle_left_button_dragging(touch)
            return True

        return super().on_touch_move(touch)

    def _handle_left_button_dragging(self, touch: kivy.input.MotionEvent) -> None:
        """Handle events when the left mouse button is pressed and the mouse is dragged.

        Args:
            touch: The touch event.
        """
        if (
            "ctrl" not in self._current_touch_modifiers
            and self._last_mouse_pos_in_pixel is not None
        ):
            # Pan the plot range.
            touch.push()
            touch.apply_transform_2d(self._to_widget_pos)
            dx_pixel = touch.pos[0] - self._last_mouse_pos_in_pixel[0]
            dy_pixel = touch.pos[1] - self._last_mouse_pos_in_pixel[1]
            x_coeff, y_coeff = self._plotter.point_converter.image_to_plot_coefficient
            widget_width, widget_height = self.size
            image_height, image_width = self._plotter.actual_size
            x_coeff = x_coeff * image_width / widget_width
            y_coeff = y_coeff * image_height / widget_height
            diff_plot = Point(x=-dx_pixel * x_coeff, y=-dy_pixel * y_coeff)

            plot_range = self.shared_state.plot_range
            plot_range.pan(diff_plot)
            self.shared_state.update_plot_range(self, plot_range)

            self._last_mouse_pos_in_pixel = touch.pos
            touch.pop()

    def on_touch_up(self, touch: kivy.input.MotionEvent) -> bool:
        """Callback when a touch up event occurs.

        Args:
            touch: The touch event.

        Returns:
            True if the event is handled, False otherwise.
        """
        if touch.grab_current is self:
            touch.ungrab(self)
            if touch.button == "left":
                self._handle_left_button_up(touch)
            return True

        return super().on_touch_up(touch)

    def _handle_left_button_up(self, touch: kivy.input.MotionEvent) -> None:
        """Handle events when the left mouse button is released."""
        if (
            "ctrl" in self._current_touch_modifiers
            and self._last_mouse_pos_in_pixel is not None
        ):
            mouse_pos_in_plot = self.shared_state.mouse_pos_in_plot
            if mouse_pos_in_plot is not None:
                # Finish to select the new range.
                touch.push()
                touch.apply_transform_2d(self._to_widget_pos)
                first_pos_in_plot = self._widget_to_plot(self._last_mouse_pos_in_pixel)
                second_pos_in_plot = self._widget_to_plot(touch.pos)
                x_min = min(first_pos_in_plot.x, second_pos_in_plot.x)
                x_max = max(first_pos_in_plot.x, second_pos_in_plot.x)
                y_min = min(first_pos_in_plot.y, second_pos_in_plot.y)
                y_max = max(first_pos_in_plot.y, second_pos_in_plot.y)
                self.shared_state.update_plot_range(
                    self,
                    PlotRange(x_range=(x_min, x_max), y_range=(y_min, y_max)),
                )
                touch.pop()
        self._last_mouse_pos_in_pixel = None
        self._current_touch_modifiers = []

    def _on_mouse_pos(self, _instance: object, value: tuple[float, float]) -> None:
        """Callback when the mouse position is changed."""
        if not self.collide_point(*self.to_widget(*value)):
            self.shared_state.update_mouse_pos_in_plot(self, None)
            return

        relative_pos = self.to_widget(*value, relative=True)
        plot_pos = self._widget_to_plot(relative_pos)

        if not self._range.contains(plot_pos):
            self.shared_state.update_mouse_pos_in_plot(self, None)
            return

        self.shared_state.update_mouse_pos_in_plot(self, plot_pos)

    def _to_widget_pos(self, x: float, y: float) -> tuple[float, float]:
        """Convert a position in window coordinates to widget-relative coordinates.

        This is intended for use with ``touch.apply_transform_2d``, since
        ``Widget.to_local`` is an identity transform by default (it does not
        account for ``self.pos``) unlike ``self.to_widget(..., relative=True)``.

        Args:
            x: X coordinate in window coordinates.
            y: Y coordinate in window coordinates.

        Returns:
            Position in widget-relative coordinates.
        """
        return self.to_widget(x, y, relative=True)

    def _widget_to_plot(self, pos_in_widget: tuple[float, float]) -> Point:
        """Convert a position in widget coordinates to plot coordinates.

        Args:
            pos_in_widget: Position in widget coordinates.

        Returns:
            Position in plot coordinates.
        """
        widget_width, widget_height = self.size
        image_height, image_width = self._plotter.actual_size
        image_x = int(pos_in_widget[0] * image_width / widget_width)
        # Kivy's coordinate system has the origin at the bottom-left corner,
        # but OpenCV's coordinate system has the origin at the top-left corner.
        image_y = int(
            (image_height - 1 - pos_in_widget[1]) * image_height / widget_height
        )
        return self._plotter.point_converter.convert_image_to_plot((image_x, image_y))

    def _zoom(self, center: Point, is_zoom_in: bool) -> None:
        """Zoom the plot.

        Args:
            center: Center point for zooming in plot coordinates.
            is_zoom_in: True to zoom in, False to zoom out.
        """
        factor = 2.0 if is_zoom_in else 0.5
        plot_range = self.shared_state.plot_range
        plot_range.zoom(center, factor)
        self.shared_state.update_plot_range(self, plot_range)
