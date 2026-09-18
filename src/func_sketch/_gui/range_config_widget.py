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

"""Class of the widget to configure the range of the plot."""

import kivy.properties
import kivy.uix.boxlayout

from func_sketch._cpp import PlotRange


class RangeConfigWidget(kivy.uix.boxlayout.BoxLayout):
    """Class of the widget to configure the range of the plot."""

    shared_state = kivy.properties.ObjectProperty()
    """Shared state object."""

    error_message = kivy.properties.StringProperty("")
    """Error message to show in the GUI."""

    _range_error_message = kivy.properties.StringProperty("")
    """Error message for the range configuration."""

    def on_kv_post(self, base_widget: object) -> None:
        """Callback after the kv rules of this widget are applied."""
        super().on_kv_post(base_widget)

        self._syncing = False

        self.bind(
            _range_error_message=lambda _instance, _value: self._update_error_message()
        )

        self._sync_range_from_shared_state_to_children()

        self.ids.x_min_text_input.bind(
            value=lambda _instance, _value: self._sync_range_from_children_to_shared_state(),
            is_valid=lambda _instance, _value: self._update_error_message(),
        )
        self.ids.x_max_text_input.bind(
            value=lambda _instance, _value: self._sync_range_from_children_to_shared_state(),
            is_valid=lambda _instance, _value: self._update_error_message(),
        )
        self.ids.y_min_text_input.bind(
            value=lambda _instance, _value: self._sync_range_from_children_to_shared_state(),
            is_valid=lambda _instance, _value: self._update_error_message(),
        )
        self.ids.y_max_text_input.bind(
            value=lambda _instance, _value: self._sync_range_from_children_to_shared_state(),
            is_valid=lambda _instance, _value: self._update_error_message(),
        )
        self.shared_state.bind(
            on_plot_range_changed=lambda _instance, _source, _value: self._sync_range_from_shared_state_to_children()
        )

    def _sync_range_from_shared_state_to_children(self) -> None:
        """Sync the range of the plot from the shared state to the child widgets."""
        if self._syncing:
            return

        self._syncing = True
        try:
            self.ids.x_min_text_input.value = self.shared_state.plot_range.x_range[0]
            self.ids.x_max_text_input.value = self.shared_state.plot_range.x_range[1]
            self.ids.y_min_text_input.value = self.shared_state.plot_range.y_range[0]
            self.ids.y_max_text_input.value = self.shared_state.plot_range.y_range[1]
        finally:
            self._syncing = False

    def _sync_range_from_children_to_shared_state(self) -> None:
        """Sync the range from the child widgets to the shared state."""
        if self._syncing:
            return

        try:
            plot_range = PlotRange(
                x_range=(
                    self.ids.x_min_text_input.value,
                    self.ids.x_max_text_input.value,
                ),
                y_range=(
                    self.ids.y_min_text_input.value,
                    self.ids.y_max_text_input.value,
                ),
            )
            self._range_error_message = ""
        except RuntimeError as e:
            self._range_error_message = str(e)
            return

        self._syncing = True
        try:
            self.shared_state.update_plot_range(self, plot_range)
        finally:
            self._syncing = False

    def _update_error_message(self) -> None:
        """Update the error message."""
        error_messages: list[str] = []
        if self._range_error_message:
            error_messages.append(self._range_error_message)
        if not self.ids.x_min_text_input.is_valid:
            error_messages.append("Minimum x is invalid.")
        if not self.ids.x_max_text_input.is_valid:
            error_messages.append("Maximum x is invalid.")
        if not self.ids.y_min_text_input.is_valid:
            error_messages.append("Minimum y is invalid.")
        if not self.ids.y_max_text_input.is_valid:
            error_messages.append("Maximum y is invalid.")

        self.error_message = "\n".join(error_messages)
