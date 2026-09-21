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

from func_sketch._gui.common.status_bar import StatusBar
from func_sketch._gui.plot_2d.status_bar_widget_model import StatusBarWidgetModel


class StatusBarWidget(StatusBar):
    """Widget to show status bar."""

    shared_state = kivy.properties.ObjectProperty()
    """Shared state object."""

    def __init__(self, **kwargs) -> None:
        """Constructor."""
        super().__init__(**kwargs)

        self._model = StatusBarWidgetModel()
        self.bind(shared_state=self._model.setter("shared_state"))
        self._model.bind(status_text=self.setter("text"))
