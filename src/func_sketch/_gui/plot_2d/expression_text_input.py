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

import kivy.clock
import kivy.core.window
import kivy.graphics
import kivy.properties
import kivy.uix.behaviors.button
import kivy.uix.dropdown
import kivy.uix.label
import kivy.uix.scrollview
import kivy.uix.widget

from func_sketch._gui.common.constants import (
    PADDING_AUTO_COMPLETE_CANDIDATES,
    TEXT_INPUT_NORMAL_BORDER_COLOR,
)
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


class AutoCompleteCandidate(
    kivy.uix.behaviors.button.ButtonBehavior, kivy.uix.label.Label
):
    """Class of candidates in the auto-complete dropdown."""

    def __init__(self, **kwargs) -> None:
        super().__init__(**kwargs)

        self.padding = PADDING_AUTO_COMPLETE_CANDIDATES
        self.size_hint_y = None
        self.height = self.texture_size[1]
        self.bind(
            texture_size=lambda _instance, value: setattr(self, "height", value[1])
        )
        self.text_size = (self.width, None)
        self.bind(
            width=lambda _instance, value: setattr(self, "text_size", (value, None))
        )
        self.halign = "left"


class AutoCompleteDropDown(kivy.uix.dropdown.DropDown):
    """Class of the dropdown list for auto-complete candidates."""

    token_candidates = kivy.properties.ObjectProperty(None, allownone=True)
    """List of token candidates based on the current token."""

    def __init__(self, **kwargs) -> None:
        super().__init__(**kwargs)

        with self.canvas.before:
            kivy.graphics.Color(1, 1, 1, 1)  # TODO Tune color.
            self._background_rect = kivy.graphics.Rectangle(
                pos=self.pos, size=self.size
            )
            kivy.graphics.Color(rgba=TEXT_INPUT_NORMAL_BORDER_COLOR)
            self._border_line = kivy.graphics.Line(
                rectangle=(self.x, self.y, self.width, self.height), width=1
            )
        self.bind(
            pos=lambda _instance, value: setattr(self._background_rect, "pos", value),
            size=lambda _instance, value: setattr(self._background_rect, "size", value),
        )
        self.bind(
            pos=lambda _instance, value: setattr(
                self._border_line,
                "rectangle",
                (value[0], value[1], self.width, self.height),
            ),
            size=lambda _instance, value: setattr(
                self._border_line, "rectangle", (self.x, self.y, value[0], value[1])
            ),
        )

        self._ancestor_scroll_views: list[kivy.uix.scrollview.ScrollView] = []
        self._reposition_trigger = kivy.clock.Clock.create_trigger(
            lambda _dt: self._reposition()
        )

    def open(self, widget: kivy.uix.widget.Widget) -> None:
        """Open the dropdown list and attach it to a widget.

        Args:
            widget: The widget to attach the dropdown list to.
        """
        super().open(widget)
        self._bind_ancestor_scroll_views(widget)

    def on_dismiss(self) -> None:
        """Callback when the dropdown list is dismissed."""
        self._unbind_ancestor_scroll_views()

    def _bind_ancestor_scroll_views(self, widget: kivy.uix.widget.Widget) -> None:
        """Bind to scroll views in the ancestors of the widget.

        DropDown repositions itself only when the position or the size of the attached widget changes,
        so scrolling of ancestor scroll views must be handled here.
        Repositioning is delayed to the next frame because scroll views update their contents asynchronously.

        Args:
            widget: The widget the dropdown list is attached to.
        """
        self._unbind_ancestor_scroll_views()
        parent = widget.parent
        while parent is not None and parent is not parent.parent:
            if isinstance(parent, kivy.uix.scrollview.ScrollView):
                parent.bind(
                    scroll_x=self._on_ancestor_scroll_view_changed,
                    scroll_y=self._on_ancestor_scroll_view_changed,
                    viewport_size=self._on_ancestor_scroll_view_changed,
                )
                self._ancestor_scroll_views.append(parent)
            parent = parent.parent

    def _unbind_ancestor_scroll_views(self) -> None:
        """Unbind from scroll views bound in _bind_ancestor_scroll_views."""
        for scroll_view in self._ancestor_scroll_views:
            scroll_view.unbind(
                scroll_x=self._on_ancestor_scroll_view_changed,
                scroll_y=self._on_ancestor_scroll_view_changed,
                viewport_size=self._on_ancestor_scroll_view_changed,
            )
        self._ancestor_scroll_views.clear()

    def _on_ancestor_scroll_view_changed(self, *_args: object) -> None:
        """Callback when an ancestor scroll view is scrolled or its contents are resized."""
        self._reposition_trigger()

    def on_token_candidates(self, _instance: object, value: list[str] | None) -> None:
        """Callback when the token candidates are updated."""
        self.clear_widgets()
        if value is None:
            return
        for candidate in value:
            candidate_widget = AutoCompleteCandidate(text=candidate)
            candidate_widget.bind(
                on_release=lambda _instance, candidate=candidate: self.select(candidate)
            )
            self.add_widget(candidate_widget)


class ExpressionTextInput(PlainTextInput):
    """Class of text inputs of function expressions."""

    model = kivy.properties.ObjectProperty(None)
    """An ExpressionTextInputModel instance."""

    def __init__(self, **kwargs) -> None:
        super().__init__(**kwargs)
        self.multiline = False
        self._auto_complete_dropdown = AutoCompleteDropDown()

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

        self._update_auto_completion()

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
        self._update_auto_completion()

    def _update_auto_completion(self) -> None:
        """Update the auto-completion dropdown based on the current token."""
        if self.model is None:
            return
        token_candidates = self.model.token_candidates
        if not token_candidates:
            if self._auto_complete_dropdown.attach_to:
                self._auto_complete_dropdown.dismiss()
            return
        self._auto_complete_dropdown.token_candidates = token_candidates
        if not self._auto_complete_dropdown.attach_to:
            self._auto_complete_dropdown.open(self)
