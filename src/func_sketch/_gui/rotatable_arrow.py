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

"""Class of widgets of rotatable arrows."""

import kivy.graphics
import kivy.properties
import kivy.uix.label

from func_sketch._gui.constants import ROTATABLE_ARROW_COLOR


class RotatableArrow(kivy.uix.label.Label):
    """Widget of a rotatable arrow."""

    rotation_angle = kivy.properties.NumericProperty(0)
    """Angle of rotation in degrees."""

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.text = ">"
        self.halign = "center"
        self.valign = "middle"
        self.color = ROTATABLE_ARROW_COLOR

        with self.canvas.before:
            kivy.graphics.PushMatrix()
            self._rotation = kivy.graphics.Rotate(
                angle=self.rotation_angle, origin=self.center
            )
        with self.canvas.after:
            kivy.graphics.PopMatrix()

        self.bind(rotation_angle=self._update_angle, pos=self._update_origin)

    def _update_angle(self, _instance: object, _value: object) -> None:
        """Update the rotation angle of the arrow."""
        self._rotation.angle = self.rotation_angle

    def _update_origin(self, _instance: object, _value: object) -> None:
        """Update the origin of the rotation."""
        self._rotation.origin = self.center
