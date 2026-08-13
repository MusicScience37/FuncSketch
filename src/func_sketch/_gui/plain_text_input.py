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

"""Class of text input widget."""

import kivy.graphics
import kivy.properties
import kivy.uix.textinput

from func_sketch._gui.constants import (
    NORMAL_TEXT_COLOR,
    TEXT_INPUT_ERROR_BACKGROUND_COLOR,
    TEXT_INPUT_ERROR_BORDER_COLOR,
    TEXT_INPUT_FOCUSED_BACKGROUND_COLOR,
    TEXT_INPUT_FOCUSED_BORDER_COLOR,
    TEXT_INPUT_NORMAL_BACKGROUND_COLOR,
    TEXT_INPUT_NORMAL_BORDER_COLOR,
)


class PlainTextInput(kivy.uix.textinput.TextInput):
    """Class of text input widget."""

    is_error = kivy.properties.BooleanProperty(False)
    """Whether the text input is in error state."""

    def __init__(self, **kwargs):
        """Constructor."""
        kwargs.setdefault("foreground_color", NORMAL_TEXT_COLOR)
        kwargs.setdefault("background_color", TEXT_INPUT_NORMAL_BACKGROUND_COLOR)
        kwargs.setdefault("background_normal", "")
        kwargs.setdefault("background_active", "")
        kwargs.setdefault("cursor_color", NORMAL_TEXT_COLOR)

        super().__init__(**kwargs)

        with self.canvas.after:
            self._border_color = kivy.graphics.Color(
                rgba=TEXT_INPUT_NORMAL_BORDER_COLOR
            )
            self._border_line = kivy.graphics.Line(
                rectangle=(self.x, self.y, self.width, self.height), width=1
            )

        self.bind(
            focus=self._update_colors,
            is_error=self._update_colors,
            pos=self._update_border_position,
            size=self._update_border_position,
        )

    def _update_colors(self, *_args) -> None:
        """Update the border color and line."""
        if self.is_error:
            self._border_color.rgba = TEXT_INPUT_ERROR_BORDER_COLOR
            self.background_color = TEXT_INPUT_ERROR_BACKGROUND_COLOR
        elif self.focus:
            self._border_color.rgba = TEXT_INPUT_FOCUSED_BORDER_COLOR
            self.background_color = TEXT_INPUT_FOCUSED_BACKGROUND_COLOR
        else:
            self._border_color.rgba = TEXT_INPUT_NORMAL_BORDER_COLOR
            self.background_color = TEXT_INPUT_NORMAL_BACKGROUND_COLOR

    def _update_border_position(self, *_args) -> None:
        """Update the border position."""
        self._border_line.rectangle = (self.x, self.y, self.width, self.height)
