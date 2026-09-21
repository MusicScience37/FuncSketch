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

"""Class of the widget of the status bar."""

import kivy.graphics
import kivy.uix.label

from func_sketch._gui.common.constants import (
    FONT_SIZE_STATUS_BAR,
    PADDING_STATUS_BAR,
    STATUS_BAR_BACKGROUND_COLOR,
)


class StatusBar(kivy.uix.label.Label):
    """Class of the widget of the status bar."""

    def __init__(self, **kwargs) -> None:
        """Constructor."""
        super().__init__(**kwargs)

        self.halign = "left"
        self.valign = "middle"

        with self.canvas.before:
            kivy.graphics.Color(rgba=STATUS_BAR_BACKGROUND_COLOR)
            self._background_rect = kivy.graphics.Rectangle(
                pos=self.pos, size=self.size
            )
        self.bind(
            pos=lambda _instance, value: setattr(self._background_rect, "pos", value)
        )
        self.bind(
            size=lambda _instance, value: setattr(self._background_rect, "size", value)
        )

        self.size_hint_y = None
        self.height = max(
            FONT_SIZE_STATUS_BAR + 2 * PADDING_STATUS_BAR, self.texture_size[1]
        )
        self.text_size = (self.width, None)
        self.font_size = FONT_SIZE_STATUS_BAR
        self.padding = PADDING_STATUS_BAR
        self.bind(
            texture_size=lambda _instance, value: setattr(
                self,
                "height",
                max(FONT_SIZE_STATUS_BAR + 2 * PADDING_STATUS_BAR, value[1]),
            ),
            width=lambda _instance, value: setattr(self, "text_size", (value, None)),
        )
