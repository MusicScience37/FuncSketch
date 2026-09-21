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

"""Class of widgets for menu bars."""

import logging
import typing

import kivy.graphics
import kivy.uix.behaviors.button
import kivy.uix.boxlayout
import kivy.uix.dropdown
import kivy.uix.label

from func_sketch._gui.common.constants import (
    MENU_BAR_BACKGROUND_COLOR,
    MENU_DROP_DOWN_WIDTH,
    PADDING_MENU_BAR,
    PADDING_MENU_BUTTON,
    SPACING_MENU_BAR,
)

LOGGER = logging.getLogger(__name__)


class CommandButton(kivy.uix.behaviors.button.ButtonBehavior, kivy.uix.label.Label):
    """Class of the command button in the menu."""

    def __init__(self, callback: typing.Callable[[], None], **kwargs) -> None:
        """Constructor.

        Args:
            callback: Callback function to be called when the button is pressed.
            **kwargs: Additional keyword arguments for the Label.
        """
        super().__init__(**kwargs)

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
        self.valign = "middle"

        self.padding = PADDING_MENU_BUTTON + SPACING_MENU_BAR

        self.bind(on_release=lambda instance: callback())


class MenuDropDown(kivy.uix.dropdown.DropDown):
    """Class of the dropdown menu in the menu bar."""

    def __init__(
        self, items: list[tuple[str, typing.Callable[[], None]]], **kwargs
    ) -> None:
        """Constructor.

        Args:
            items: List of tuples containing the menu item text and the corresponding callback function.
            **kwargs: Additional keyword arguments for the DropDown.
        """
        super().__init__(**kwargs)

        self._items = items

        with self.canvas.before:
            kivy.graphics.Color(rgba=MENU_BAR_BACKGROUND_COLOR)
            self._background_rect = kivy.graphics.Rectangle(
                pos=self.pos, size=self.size
            )
        self.bind(
            pos=lambda _instance, value: setattr(self._background_rect, "pos", value)
        )
        self.bind(
            size=lambda _instance, value: setattr(self._background_rect, "size", value)
        )

        self.auto_width = False

        self._buttons: list[CommandButton] = []
        for item_text, _ in items:
            button = CommandButton(
                text=item_text,
                callback=lambda item_text=item_text: self.select(item_text),  # type: ignore
            )
            button.bind(texture_size=lambda _instance, _value: self._update_width())
            self.add_widget(button)
            self._buttons.append(button)

        self._update_width()

    def _update_width(self) -> None:
        """Update the width."""
        self.width = max(
            max(
                (child.texture_size[0] for child in self._buttons),
                default=MENU_DROP_DOWN_WIDTH,
            ),
            MENU_DROP_DOWN_WIDTH,
        )

    def on_select(self, item_text: str) -> None:
        """Handle the selection of a menu item."""
        for text, callback in self._items:
            if text == item_text:
                callback()
                break


class MenuButton(kivy.uix.behaviors.button.ButtonBehavior, kivy.uix.label.Label):
    """Class of the button in the menu bar."""

    def __init__(
        self, items: list[tuple[str, typing.Callable[[], None]]], **kwargs
    ) -> None:
        """Constructor.

        Args:
            items: List of tuples containing the button text and the corresponding callback function.
            **kwargs: Additional keyword arguments for the Label.
        """
        super().__init__(**kwargs)

        self.size_hint_x = None
        self.width = self.texture_size[0]
        self.bind(
            texture_size=lambda _instance, value: setattr(self, "width", value[0])
        )

        self.size_hint_y = None
        self.height = self.texture_size[1]
        self.bind(
            texture_size=lambda _instance, value: setattr(self, "height", value[1])
        )

        self.padding = PADDING_MENU_BUTTON

        self.dropdown = MenuDropDown(items=items)
        self.bind(on_release=self.dropdown.open)


class MenuBar(kivy.uix.boxlayout.BoxLayout):
    """Class of the widget of the menu bar."""

    shared_state = kivy.properties.ObjectProperty()
    """Shared state object."""

    def __init__(
        self,
        menu_contents: list[tuple[str, list[tuple[str, typing.Callable[[], None]]]]],
        **kwargs,
    ) -> None:
        """Constructor.

        Args:
            menu_contents: List of tuples containing the menu title and the corresponding menu items.
            **kwargs: Additional keyword arguments for the BoxLayout.
        """
        super().__init__(**kwargs)

        self.canvas.before.clear()
        with self.canvas.before:
            kivy.graphics.Color(rgba=MENU_BAR_BACKGROUND_COLOR)
            self._background_rect = kivy.graphics.Rectangle(
                pos=self.pos, size=self.size
            )
        self.bind(
            pos=lambda _instance, value: setattr(self._background_rect, "pos", value)
        )
        self.bind(
            size=lambda _instance, value: setattr(self._background_rect, "size", value)
        )

        for menu_button_text, menu_items in menu_contents:
            self.add_widget(
                MenuButton(
                    text=menu_button_text,
                    items=menu_items,
                )
            )

        self.size_hint_y = None
        self.height = self.minimum_height
        self.bind(minimum_height=self.setter("height"))

        self.padding = PADDING_MENU_BAR
        self.spacing = SPACING_MENU_BAR
