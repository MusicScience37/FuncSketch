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

"""Class of widgets of collapsible boxes."""

import logging

import kivy.animation
import kivy.properties
import kivy.uix.behaviors.button
import kivy.uix.boxlayout
import kivy.uix.label
import kivy.uix.widget

from func_sketch._gui.common.constants import (
    ANIMATION_DURATION,
    FONT_SIZE_HEADER1,
    SPACING_DEFAULT,
)
from func_sketch._gui.common.rotatable_arrow import RotatableArrow
from func_sketch._gui.common.sync_properties import sync_properties

LOGGER = logging.getLogger(__name__)


class CollapsibleBoxHeader(
    kivy.uix.behaviors.button.ButtonBehavior, kivy.uix.boxlayout.BoxLayout
):
    """Class of headers of collapsible boxes."""

    title = kivy.properties.StringProperty("")
    """Title."""

    title_font_size = kivy.properties.NumericProperty(FONT_SIZE_HEADER1)
    """Font size of the title."""

    collapsed = kivy.properties.BooleanProperty(False)
    """Whether the box is collapsed."""

    def __init__(self, **kwargs) -> None:
        super().__init__(**kwargs)

        self._title_widget = kivy.uix.label.Label()
        self._title_widget.text = self.title
        self.bind(title=self._title_widget.setter("text"))
        self._title_widget.font_size = self.title_font_size
        self.bind(title_font_size=self._title_widget.setter("font_size"))
        self._title_widget.halign = "left"
        self._title_widget.valign = "middle"
        self._title_widget.text_size = (self._title_widget.width, None)
        self._title_widget.bind(size=self._title_widget.setter("text_size"))
        self._title_widget.size_hint_y = None
        self._title_widget.height = self._title_widget.texture_size[1]
        self._title_widget.bind(
            texture_size=lambda _instance, value: setattr(
                self._title_widget, "height", value[1]
            )
        )

        self._arrow_widget = RotatableArrow()
        self._arrow_widget.font_size = self.title_font_size
        self.bind(title_font_size=self._arrow_widget.setter("font_size"))
        self._arrow_widget.size_hint_x = None
        self._arrow_widget.width = self.title_font_size * 2
        self.bind(
            title_font_size=lambda instance, value: setattr(
                self._arrow_widget, "width", value * 2
            )
        )
        self._arrow_widget.size_hint_y = None
        self._arrow_widget.height = self._title_widget.height
        self._title_widget.bind(height=self._arrow_widget.setter("height"))
        self._arrow_widget.rotation_angle = -90

        self.add_widget(self._title_widget)
        self.add_widget(self._arrow_widget)
        self.orientation = "horizontal"
        self.size_hint_y = None
        self.height = self.minimum_height
        self.bind(minimum_height=self.setter("height"))

    def on_release(self) -> None:
        """Callback when the header is released."""
        self.collapsed = not self.collapsed

    def on_collapsed(self, _instance: object, value: bool) -> None:
        """Callback when the collapsed property changes.

        Args:
            value (bool): The new value of the collapsed property.
        """
        kivy.animation.Animation.cancel_all(self._arrow_widget, "rotation_angle")
        kivy.animation.Animation(
            rotation_angle=0 if value else -90,
            d=ANIMATION_DURATION,
            t="out_quad",
        ).start(self._arrow_widget)


class CollapsibleBox(kivy.uix.boxlayout.BoxLayout):
    """Class of widgets of collapsible boxes."""

    title = kivy.properties.StringProperty("")
    """Title."""

    title_font_size = kivy.properties.NumericProperty(FONT_SIZE_HEADER1)
    """Font size of the title."""

    collapsed = kivy.properties.BooleanProperty(False)
    """Whether the box is collapsed."""

    def __init__(self, **kwargs) -> None:
        self._animating = False

        self._header_widget: CollapsibleBoxHeader | None = None
        self._content_widget: kivy.uix.widget.Widget | None = None

        super().__init__(**kwargs)

    def add_widget(self, widget: kivy.uix.widget.Widget, *args, **kwargs) -> None:
        """Add a widget."""
        if self._content_widget is not None:
            raise ValueError("Content widget already added.")

        self._header_widget = CollapsibleBoxHeader()
        self.bind(
            title=self._header_widget.setter("title"),
            title_font_size=self._header_widget.setter("title_font_size"),
        )
        sync_properties(self, "collapsed", self._header_widget, "collapsed")

        self._content_widget = widget
        self._content_widget.size_hint_y = None
        self._content_widget.height = self._content_widget.minimum_height
        self._content_widget.bind(
            minimum_height=lambda _instance, _value: self._update_content_height(False)
        )

        super().add_widget(self._header_widget, *args, **kwargs)
        super().add_widget(self._content_widget, *args, **kwargs)
        self.orientation = "vertical"
        self.size_hint_y = None
        self.height = self.minimum_height
        self.bind(minimum_height=self.setter("height"))
        self.spacing = SPACING_DEFAULT

    def on_collapsed(self, _instance: object, _value: bool) -> None:
        """Toggle the collapsed state of the content widget."""
        self._update_content_height(True)

    def on_touch_down(self, touch: kivy.input.MotionEvent) -> bool:
        """Callback when the touch down event occurs.

        Args:
            touch: The touch event.

        Returns:
            True if the event is handled, False otherwise.
        """
        if self._header_widget is not None and self._header_widget.dispatch(
            "on_touch_down", touch
        ):
            return True
        return super().on_touch_down(touch)

    def on_touch_up(self, touch: kivy.input.MotionEvent) -> bool:
        """Callback when the touch up event occurs.

        Args:
            touch: The touch event.

        Returns:
            True if the event is handled, False otherwise.
        """
        if self._header_widget is not None and self._header_widget.dispatch(
            "on_touch_up", touch
        ):
            return True
        return super().on_touch_up(touch)

    def _update_content_height(self, animate: bool) -> None:
        """Update the height of the content widget based on the collapsed state.

        Args:
            animate: Whether to animate the change.
                This will be overridden to True if an animation is already in progress.
        """
        if self._content_widget is None:
            return

        content_minimum_height = self._content_widget.minimum_height
        if content_minimum_height == 0:
            raise ValueError("Content widget has zero minimum height.")

        if self._animating:
            animate = True

        kivy.animation.Animation.cancel_all(self._content_widget, "height", "opacity")

        if not animate:
            self._content_widget.height = (
                0 if self.collapsed else content_minimum_height
            )
            self._content_widget.opacity = 0.0 if self.collapsed else 1.0
            self._content_widget.disabled = self.collapsed
            return

        if self.collapsed:
            animation = kivy.animation.Animation(
                opacity=0.0,
                d=ANIMATION_DURATION,
                t="out_expo",
            ) & kivy.animation.Animation(
                height=0,
                d=ANIMATION_DURATION,
                t="out_quad",
            )
            animation.bind(
                on_complete=lambda *_: setattr(self._content_widget, "disabled", True)
            )
            self._animating = True
            animation.bind(on_complete=lambda *_: setattr(self, "_animating", False))
            animation.start(self._content_widget)
        else:
            self._content_widget.disabled = False
            animation = kivy.animation.Animation(
                height=content_minimum_height,
                d=ANIMATION_DURATION,
                t="out_quad",
            ) & kivy.animation.Animation(
                opacity=1.0,
                d=ANIMATION_DURATION,
                t="in_expo",
            )
            animation.bind(on_complete=lambda *_: setattr(self, "_animating", False))
            self._animating = True
            animation.start(self._content_widget)
