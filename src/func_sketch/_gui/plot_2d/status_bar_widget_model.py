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

"""Class of the view model of the status bar."""

import kivy.event
import kivy.properties

from func_sketch._cpp import Point


class StatusBarWidgetModel(kivy.event.EventDispatcher):
    """Class of the view model of the status bar."""

    shared_state = kivy.properties.ObjectProperty(None, allownone=True)
    """Shared state object."""

    status_text = kivy.properties.StringProperty("")
    """Text to show in the status bar."""

    def on_shared_state(self, _instance: object, _value: object) -> None:
        """Callback when the shared_state property is set."""
        if self.shared_state is None:
            return
        self.shared_state.bind(
            on_mouse_pos_in_plot_changed=self._on_mouse_pos_in_plot,
        )

    def _on_mouse_pos_in_plot(
        self, _instance: object, _source: object, value: Point | None
    ) -> None:
        """Callback when the on_mouse_pos_in_plot_changed event is dispatched.

        Args:
            value: Mouse position in the plot, or None if the mouse is outside the plot.
        """
        if value is None:
            self.status_text = ""
        else:
            self.status_text = f"Mouse position: ({value.x:.5g}, {value.y:.5g})."
