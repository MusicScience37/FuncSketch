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

"""Class of widgets to show status bar."""

import kivy.properties
import kivy.uix.label

from func_sketch._cpp import Point


class StatusBarWidget(kivy.uix.label.Label):
    """Widget to show status bar."""

    shared_state = kivy.properties.ObjectProperty()
    """Shared state object."""

    def __init__(self, **kwargs) -> None:
        """Constructor."""
        super().__init__(**kwargs)

        self.text = ""
        self.halign = "left"
        self.valign = "middle"

    def on_shared_state(self, _instance: object, _value: object) -> None:
        """Callback when the shared_state property is set."""
        self.shared_state.bind(on_mouse_pos_in_plot_changed=self._on_mouse_pos_in_plot)
        self._update_status()

    def _on_mouse_pos_in_plot(
        self, _instance: object, _source: object, _value: Point | None
    ) -> None:
        """Callback when the on_mouse_pos_in_plot_changed event is dispatched."""
        self._update_status()

    def _update_status(self) -> None:
        """Update the status text based on the current shared state."""
        text = ""

        mouse_pos_in_plot = self.shared_state.mouse_pos_in_plot
        if mouse_pos_in_plot is not None:
            text = f"Mouse position: ({mouse_pos_in_plot.x:.5g}, {mouse_pos_in_plot.y:.5g}). "

        if not text:
            text = " "  # Prevent empty status bar text.

        self.text = text
