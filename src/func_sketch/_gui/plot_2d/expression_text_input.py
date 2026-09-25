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

"""Class of text inputs of function expressions."""

import logging

import kivy.core.window
import kivy.properties

from func_sketch._gui.common.plain_text_input import PlainTextInput
from func_sketch._gui.common.sync_properties import sync_properties

LOGGER = logging.getLogger(__name__)

_CURSOR_MOVEMENT_KEYS = frozenset(
    {
        "cursor_up",
        "cursor_down",
        "cursor_left",
        "cursor_right",
        "cursor_home",
        "cursor_end",
        "cursor_pgup",
        "cursor_pgdown",
    }
)


class ExpressionTextInput(PlainTextInput):
    """Class of text inputs of function expressions."""

    model = kivy.properties.ObjectProperty(None)
    """An ExpressionTextInputModel instance."""

    def __init__(self, **kwargs) -> None:
        super().__init__(**kwargs)
        self.multiline = False

    def on_kv_post(self, base_widget: object) -> None:
        """Callback after the kv rules of this widget are applied."""
        super().on_kv_post(base_widget)
        if self.model is None:
            raise ValueError("model for ExpressionTextInput is not set.")
        sync_properties(self.model, "expression_text", self, "text")
        sync_properties(self, "cursor", self.model, "cursor")

    def keyboard_on_key_down(
        self,
        window: object,
        keycode: tuple[int, str],
        text: str | None,
        modifiers: list[str],
    ) -> bool:
        """Callback when a key is pressed in the text input.

        Args:
            window: The window instance.
            keycode: A tuple of (key code, key string).
            text: The text corresponding to the key.
            modifiers: A list of active modifier keys.

        Returns:
            True if the key event was handled, False otherwise.

        Note:
            When the window doesn't manage text inputs (e.g., when SDL2 is not used),
            text is inserted in this method instead of keyboard_on_textinput.
        """
        result = super().keyboard_on_key_down(window, keycode, text, modifiers)
        key_name = self.interesting_keys.get(keycode[0])
        if key_name == "backspace":
            self.model.on_backspace()
        elif key_name in _CURSOR_MOVEMENT_KEYS:
            self.model.clear_current_token()
        elif (
            not kivy.core.window.Window.managed_textinput
            and text
            and set(modifiers) <= {"shift", "capslock", "numlock"}
            and key_name is None
        ):
            self.model.on_key_type(text)
        return result

    def keyboard_on_textinput(self, window: object, text: str) -> None:
        """Callback when a text is input from the keyboard.

        Args:
            window: The window instance.
            text: The input text.

        Note:
            This method is called when Kivy is using SDL2 backend.
        """
        super().keyboard_on_textinput(window, text)
        self.model.on_key_type(text)
