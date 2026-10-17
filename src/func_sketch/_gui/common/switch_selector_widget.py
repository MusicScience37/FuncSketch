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

"""Class of widgets to select one of the options using switches."""

import kivy.properties
import kivy.uix.boxlayout

from func_sketch._gui.common.switch_widget import SwitchBaseWidget


class SwitchSelectorWidget(kivy.uix.boxlayout.BoxLayout):
    """Class of widgets to select one of the options using switches.

    Switches are placed in a row, and only the switch of the selected option is active.
    """

    options = kivy.properties.ListProperty()
    """Options as a list of pairs of a value and the text shown on its switch."""

    selected = kivy.properties.ObjectProperty(None, allownone=True)
    """Value of the selected option."""

    def __init__(self, **kwargs) -> None:
        """Constructor."""
        self._switches: list[tuple[object, SwitchBaseWidget]] = []
        super().__init__(**kwargs)
        # Bind after the constructor of the base class,
        # because switches can't be added before the canvas is created.
        self.bind(
            options=lambda *_: self._update_switches(),
            selected=lambda *_: self._update_active_states(),
        )
        self._update_switches()

    def _update_switches(self) -> None:
        """Recreate switches according to the options."""
        self.clear_widgets()
        self._switches = []
        for value, text in self.options:
            switch = SwitchBaseWidget(text=text, size_hint_y=None)
            switch.bind(
                texture_size=lambda instance, size: setattr(instance, "height", size[1])
            )
            switch.bind(
                on_release=lambda _instance, value=value: setattr(
                    self, "selected", value
                )
            )
            self.add_widget(switch)
            self._switches.append((value, switch))
        self._update_active_states()

    def _update_active_states(self) -> None:
        """Update active states of switches according to the selected option."""
        for value, switch in self._switches:
            switch.active = value == self.selected
