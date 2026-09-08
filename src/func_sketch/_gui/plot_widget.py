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
        if touch.is_mouse_scrolling:
            mouse_pos_in_plot = self.shared_state.mouse_pos_in_plot
            if mouse_pos_in_plot is not None:
                LOGGER.debug("button: %s", touch.button)
                is_zoom_in = touch.button == "scrolldown"
                self._zoom(center=mouse_pos_in_plot, is_zoom_in=is_zoom_in)
                return True

        return super().on_touch_down(touch)

    def _on_mouse_pos(self, _instance: object, value: tuple[int, int]) -> None:
        """Callback when the mouse position is changed."""
        if not self.collide_point(*self.to_widget(*value)):
            self.shared_state.update_mouse_pos_in_plot(self, None)
            return

        relative_pos = self.to_widget(*value, relative=True)
        widget_width, widget_height = self.size
        image_height, image_width = self._plotter.actual_size
        image_x = int(relative_pos[0] * image_width / widget_width)
        # Kivy's coordinate system has the origin at the bottom-left corner,
        # but OpenCV's coordinate system has the origin at the top-left corner.
        image_y = int(
            (image_height - 1 - relative_pos[1]) * image_height / widget_height
        )
        plot_pos = self._plotter.point_converter.convert_image_to_plot(
            (image_x, image_y)
        )

        if not self._range.contains(plot_pos):
            self.shared_state.update_mouse_pos_in_plot(self, None)
            return

        self.shared_state.update_mouse_pos_in_plot(self, plot_pos)

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
