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

"""Class of widgets of switches."""

import kivy.graphics
import kivy.properties
import kivy.uix.behaviors.button
import kivy.uix.label

from func_sketch._gui.constants import SWITCH_OFF_COLOR, SWITCH_ON_COLOR, SWITCH_PADDING


class SwitchWidget(kivy.uix.behaviors.button.ButtonBehavior, kivy.uix.label.Label):
    """Class of widgets of switches."""

    active = kivy.properties.BooleanProperty(False)
    """Active state of the switch."""

    def __init__(self, **kwargs) -> None:
        super().__init__(**kwargs)

        self.bind(active=lambda *_: self._on_active())

        with self.canvas.before:
            self._box_color = kivy.graphics.Color(0.5, 0.5, 0.5, 1)
            self._box = kivy.graphics.BoxShadow(pos=self.pos, size=self.size)

        self.bind(pos=lambda *_: setattr(self._box, "pos", self.pos))
        self.bind(size=lambda *_: setattr(self._box, "size", self.size))

        self._on_active()

        self.padding = SWITCH_PADDING

    def _on_active(self) -> None:
        """Callback when the active state changes."""
        self.text = "ON" if self.active else "OFF"
        self._box_color.rgba = SWITCH_ON_COLOR if self.active else SWITCH_OFF_COLOR

    def on_release(self) -> None:
        """Callback when the switch is released."""
        self.active = not self.active
