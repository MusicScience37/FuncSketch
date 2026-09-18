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

"""Class of the widget of image sizes."""

import kivy.properties
import kivy.uix.boxlayout


class ImageSizeWidget(kivy.uix.boxlayout.BoxLayout):
    """Class of the widget of image sizes."""

    shared_state = kivy.properties.ObjectProperty()
    """Shared state object."""

    error_message = kivy.properties.StringProperty("")
    """Error message to show in the GUI."""

    def on_kv_post(self, base_widget: object) -> None:
        """Callback after the kv rules of this widget are applied."""
        super().on_kv_post(base_widget)
        self.ids.fix_size_switch.bind(active=self._on_fix_size_switch_active)
        self.ids.fixed_height_input.bind(text=self._on_fixed_size_changed)
        self.ids.fixed_width_input.bind(text=self._on_fixed_size_changed)

    def on_shared_state(self, _instance: object, _value: object) -> None:
        """Callback when the shared state changes."""
        self._update_current_size()
        self.shared_state.bind(image_buffer=lambda *_: self._update_current_size())

    def _update_current_size(self) -> None:
        """Update the current size labels."""
        if self.shared_state is None:
            return

        image_buffer = self.shared_state.image_buffer
        if image_buffer is None:
            return

        self.ids.current_height_label.text = str(image_buffer.shape[0])
        self.ids.current_width_label.text = str(image_buffer.shape[1])

        if self.shared_state.fixed_desired_size is not None:
            fixed_height, fixed_width = self.shared_state.fixed_desired_size
            if (
                fixed_height == image_buffer.shape[0]
                and fixed_width == image_buffer.shape[1]
            ):
                self.error_message = ""
            else:
                self.error_message = "Too small fixed size was overridden."

    def _on_fix_size_switch_active(self, _instance: object, _value: object) -> None:
        """Callback when the fix size switch is toggled."""
        active = self.ids.fix_size_switch.active
        self.ids.fixed_height_input.disabled = not active
        self.ids.fixed_width_input.disabled = not active

        self._on_fixed_size_changed(None, None)

    def _on_fixed_size_changed(self, _instance: object, _value: object) -> None:
        """Callback when the fixed size is changed."""
        if self.shared_state is None:
            return

        if not self.ids.fix_size_switch.active:
            self.shared_state.update_fixed_desired_size(self, None)
            return

        try:
            fixed_height = int(self.ids.fixed_height_input.text)
            fixed_width = int(self.ids.fixed_width_input.text)
            self.shared_state.update_fixed_desired_size(
                self, (fixed_height, fixed_width)
            )
            # Error message in this case will be updated in _update_current_size function.
        except ValueError:
            self.shared_state.update_fixed_desired_size(self, None)
            self.error_message = "Invalid fixed size."
