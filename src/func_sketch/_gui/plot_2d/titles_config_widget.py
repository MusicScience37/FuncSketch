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

"""Class of the widget to configure titles of the plot."""

import kivy.properties
import kivy.uix.boxlayout

from func_sketch._gui.common.sync_properties import sync_properties
from func_sketch._gui.plot_2d.titles_config_widget_model import TitlesConfigWidgetModel


class TitlesConfigWidget(kivy.uix.boxlayout.BoxLayout):
    """Class of the widget to configure titles of the plot."""

    shared_state = kivy.properties.ObjectProperty()
    """Shared state object."""

    def __init__(self, **kwargs) -> None:
        """Constructor."""
        self._model = TitlesConfigWidgetModel()
        super().__init__(**kwargs)

    def on_kv_post(self, base_widget: object) -> None:
        """Callback after the kv rules of this widget are applied."""
        super().on_kv_post(base_widget)

        self._model.shared_state = self.shared_state
        self._model.init()

        sync_properties(
            self._model, "plot_title", self.ids.plot_title_text_input, "text"
        )
        sync_properties(
            self._model, "x_axis_title", self.ids.x_axis_title_text_input, "text"
        )
        sync_properties(
            self._model, "y_axis_title", self.ids.y_axis_title_text_input, "text"
        )
