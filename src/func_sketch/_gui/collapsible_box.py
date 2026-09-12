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
import kivy.input
import kivy.properties
import kivy.uix.boxlayout
import kivy.uix.label
import kivy.uix.widget

from func_sketch._gui.constants import (
    ANIMATION_DURATION,
    FONT_SIZE_HEADER1,
    SPACING_DEFAULT,
)
from func_sketch._gui.rotatable_arrow import RotatableArrow

LOGGER = logging.getLogger(__name__)


class CollapsibleBox(kivy.uix.boxlayout.BoxLayout):
    """Widget of a collapsible box."""

    title = kivy.properties.StringProperty("")
    title_font_size = kivy.properties.NumericProperty(FONT_SIZE_HEADER1)

    def __init__(self, **kwargs) -> None:
        self._collapsed = False

        self._title_widget: kivy.uix.label.Label | None = None
        self._arrow_widget: RotatableArrow | None = None
        self._header_widget: kivy.uix.boxlayout.BoxLayout | None = None
        self._content_widget: kivy.uix.widget.Widget | None = None

        super().__init__(**kwargs)

    def add_widget(self, widget: kivy.uix.widget.Widget, *args, **kwargs) -> None:
        """Add a widget."""
        if self._content_widget is not None:
            raise ValueError("Content widget already added.")

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

        self._header_widget = kivy.uix.boxlayout.BoxLayout()
        self._header_widget.add_widget(self._title_widget)
        self._header_widget.add_widget(self._arrow_widget)
        self._header_widget.orientation = "horizontal"
        self._header_widget.size_hint_y = None
        self._header_widget.height = self._header_widget.minimum_height
        self._header_widget.bind(minimum_height=self._header_widget.setter("height"))

        self._content_widget = widget
        self._content_widget.size_hint_y = None
        self._content_widget.height = self._content_widget.minimum_height
        self._content_widget.bind(
            minimum_height=lambda _instance, _value: self._update_content_height()
        )

        super().add_widget(self._header_widget, *args, **kwargs)
        super().add_widget(self._content_widget, *args, **kwargs)
        self.orientation = "vertical"
        self.size_hint_y = None
        self.height = self.minimum_height
        self.bind(minimum_height=self.setter("height"))
        self.spacing = SPACING_DEFAULT

    def on_touch_down(self, touch: kivy.input.MotionEvent) -> bool:
        """Callback when the touch down event occurs.

        Args:
            touch: The touch event.

        Returns:
            True if the event is handled, False otherwise.

        Note:
            This handles the touch down event for the header widget.
        """
        if self._header_widget is not None and self._header_widget.collide_point(
            *touch.pos
        ):
            LOGGER.debug("Header widget pressed.")
            self._toggle_collapsed()
            return True
        return super().on_touch_down(touch)

    def _toggle_collapsed(self) -> None:
        """Toggle the collapsed state of the content widget."""
        if self._arrow_widget is None or self._content_widget is None:
            return

        self._collapsed = not self._collapsed
        kivy.animation.Animation.cancel_all(self._arrow_widget, "rotation_angle")
        kivy.animation.Animation(
            rotation_angle=0 if self._collapsed else -90,
            d=ANIMATION_DURATION,
            t="out_quad",
        ).start(self._arrow_widget)
        self._update_content_height()

    def _update_content_height(self) -> None:
        """Update the height of the content widget based on the collapsed state."""
        if self._content_widget is None:
            return

        content_minimum_height = self._content_widget.minimum_height
        if content_minimum_height == 0:
            raise ValueError("Content widget has zero minimum height.")

        kivy.animation.Animation.cancel_all(self._content_widget, "height", "opacity")

        if self._collapsed:
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
            animation.start(self._content_widget)
