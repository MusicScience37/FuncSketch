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
import kivy.graphics
import kivy.graphics.texture
import kivy.input
import kivy.properties
import kivy.uix.image

from func_sketch._gui.common.constants import (
    PLOT_BACKGROUND_PADDING_COLOR,
)
from func_sketch._gui.plot_2d.plot_widget_model import PlotWidgetModel

LOGGER = logging.getLogger(__name__)


class PlotWidget(kivy.uix.image.Image):
    """Class of widgets to show plots."""

    shared_state = kivy.properties.ObjectProperty()
    """Shared state object."""

    def __init__(self, **kwargs) -> None:
        """Constructor."""
        super().__init__(**kwargs)

        self._model = PlotWidgetModel()
        self._prepare_texture()
        self._model.bind(
            image_buffer=lambda _instance, _value: self._prepare_texture(),
            on_image_buffer_written=self._on_image_buffer_written,
        )
        self.bind(
            size=lambda _instance, value: self._model.on_widget_size(value),
            norm_image_size=lambda _instance, value: self._model.on_norm_image_size(
                value
            ),
            shared_state=lambda _instance, value: setattr(
                self._model, "shared_state", value
            ),
        )

        kivy.core.window.Window.bind(mouse_pos=self._on_mouse_pos)

        self.fit_mode = "contain"

        with self.canvas.before:
            kivy.graphics.Color(*PLOT_BACKGROUND_PADDING_COLOR)
            self._background_rect = kivy.graphics.Rectangle(
                pos=self.pos,
                size=self.size,
            )
        self.bind(
            pos=lambda _instance, _value: setattr(
                self._background_rect, "pos", self.pos
            ),
            size=lambda _instance, _value: setattr(
                self._background_rect, "size", self.size
            ),
        )

    def on_kv_post(self, base_widget: object) -> None:
        """Callback after the kv rules of this widget are applied."""
        super().on_kv_post(base_widget)

        self._model.init()

    def _prepare_texture(self) -> None:
        """Prepare texture for the plot."""
        image_buffer = self._model.image_buffer
        height, width = image_buffer.shape[:2]

        self._texture = kivy.graphics.texture.Texture.create(
            size=(width, height), colorfmt="rgb"
        )
        self._texture.blit_buffer(
            image_buffer.tobytes(), colorfmt="rgb", bufferfmt="ubyte"
        )
        self._texture.flip_vertical()
        self.texture = self._texture

    def _on_image_buffer_written(self, _instance: object) -> None:
        """Callback when the image buffer is written (no update for the image size)."""
        # In this case, texture does not need to be recreated, only updated.
        self._texture.blit_buffer(
            self._model.image_buffer.tobytes(), colorfmt="rgb", bufferfmt="ubyte"
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
                self._model.on_mouse_scroll(is_scroll_down=touch.button == "scrolldown")
                return True
            elif touch.is_touch:
                if touch.button == "left":
                    self._handle_left_button_down(touch)
                    return True
                elif touch.button == "right":
                    # TODO Right click will be handled in the future.
                    return True

        return super().on_touch_down(touch)

    def _handle_left_button_down(self, touch: kivy.input.MotionEvent) -> None:
        """Handle events when the left mouse button is pressed.

        Args:
            touch: The touch event.
        """
        mouse_pos_in_plot = self.shared_state.mouse_pos_in_plot
        if mouse_pos_in_plot is not None:
            touch.grab(self)
            touch.push()
            touch.apply_transform_2d(self._to_widget_pos)
            self._model.on_mouse_left_button_down(
                relative_pos=touch.pos,
                current_touch_modifiers=kivy.core.window.Window.modifiers.copy(),
            )
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
        touch.push()
        touch.apply_transform_2d(self._to_widget_pos)
        self._model.on_mouse_left_button_dragging(relative_pos=touch.pos)
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
        touch.push()
        touch.apply_transform_2d(self._to_widget_pos)
        self._model.on_mouse_left_button_up(relative_pos=touch.pos)
        touch.pop()

    def _on_mouse_pos(self, _instance: object, value: tuple[float, float]) -> None:
        """Callback when the mouse position is changed."""
        if not self.collide_point(*self.to_widget(*value)):
            self.shared_state.update_mouse_pos_in_plot(self, None)
            return

        relative_pos = self.to_widget(*value, relative=True)
        self._model.on_mouse_pos_in_widget(relative_pos)

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
