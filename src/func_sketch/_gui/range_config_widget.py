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

    x_min_text_input = kivy.properties.ObjectProperty()
    """Text input widget for the minimum x value."""

    x_max_text_input = kivy.properties.ObjectProperty()
    """Text input widget for the maximum x value."""

    y_min_text_input = kivy.properties.ObjectProperty()
    """Text input widget for the minimum y value."""

    y_max_text_input = kivy.properties.ObjectProperty()
    """Text input widget for the maximum y value."""

    shared_state = kivy.properties.ObjectProperty()
    """Shared state object."""

    error_message = kivy.properties.StringProperty("")
    """Error message to show in the GUI."""

    _range_error_message = kivy.properties.StringProperty("")
    """Error message for the range configuration."""

    def __init__(self, **kwargs: object) -> None:
        """Constructor."""
        super().__init__(**kwargs)

        self._syncing = False
        self._is_initialized = False

        self.bind(
            x_min_text_input=lambda _instance, _value: self._init_range(),
            x_max_text_input=lambda _instance, _value: self._init_range(),
            y_min_text_input=lambda _instance, _value: self._init_range(),
            y_max_text_input=lambda _instance, _value: self._init_range(),
            shared_state=lambda _instance, _value: self._init_range(),
            _range_error_message=lambda _instance, _value: self._update_error_message(),
        )
        self._init_range()

    def _init_range(self) -> None:
        """Initialize the range of the plot."""
        if (
            self.shared_state is None
            or self.x_min_text_input is None
            or self.x_max_text_input is None
            or self.y_min_text_input is None
            or self.y_max_text_input is None
        ):
            return

        if self._is_initialized:
            return

        self._is_initialized = True

        self._sync_range_from_shared_state_to_children()

        self.x_min_text_input.bind(
            value=lambda _instance, _value: self._sync_range_from_children_to_shared_state(),
            is_valid=lambda _instance, _value: self._update_error_message(),
        )
        self.x_max_text_input.bind(
            value=lambda _instance, _value: self._sync_range_from_children_to_shared_state(),
            is_valid=lambda _instance, _value: self._update_error_message(),
        )
        self.y_min_text_input.bind(
            value=lambda _instance, _value: self._sync_range_from_children_to_shared_state(),
            is_valid=lambda _instance, _value: self._update_error_message(),
        )
        self.y_max_text_input.bind(
            value=lambda _instance, _value: self._sync_range_from_children_to_shared_state(),
            is_valid=lambda _instance, _value: self._update_error_message(),
        )
        self.shared_state.bind(
            plot_range=lambda _instance, _value: self._sync_range_from_shared_state_to_children()
        )

    def _sync_range_from_shared_state_to_children(self) -> None:
        """Sync the range of the plot from the shared state to the child widgets."""
        if not self._is_initialized:
            return

        if self._syncing:
            return

        self._syncing = True
        try:
            self.x_min_text_input.value = self.shared_state.plot_range.x_range[0]
            self.x_max_text_input.value = self.shared_state.plot_range.x_range[1]
            self.y_min_text_input.value = self.shared_state.plot_range.y_range[0]
            self.y_max_text_input.value = self.shared_state.plot_range.y_range[1]
        finally:
            self._syncing = False

    def _sync_range_from_children_to_shared_state(self) -> None:
        """Sync the range from the child widgets to the shared state."""
        if not self._is_initialized:
            return

        if self._syncing:
            return

        try:
            plot_range = PlotRange(
                x_range=(self.x_min_text_input.value, self.x_max_text_input.value),
                y_range=(self.y_min_text_input.value, self.y_max_text_input.value),
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
        if self.x_min_text_input is not None and not self.x_min_text_input.is_valid:
            error_messages.append("Minimum x is invalid.")
        if self.x_max_text_input is not None and not self.x_max_text_input.is_valid:
            error_messages.append("Maximum x is invalid.")
        if self.y_min_text_input is not None and not self.y_min_text_input.is_valid:
            error_messages.append("Minimum y is invalid.")
        if self.y_max_text_input is not None and not self.y_max_text_input.is_valid:
            error_messages.append("Maximum y is invalid.")

        self.error_message = "\n".join(error_messages)
