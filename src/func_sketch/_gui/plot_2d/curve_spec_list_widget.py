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

"""Class of the widget for a list of curve specification widgets."""

import logging

import kivy.properties
import kivy.uix.boxlayout

from func_sketch._gui.plot_2d.curve_spec_list_widget_model import (
    CurveSpecListWidgetModel,
)
from func_sketch._gui.plot_2d.curve_spec_widget import CurveSpecWidget

LOGGER = logging.getLogger(__name__)


class CurveSpecListWidget(kivy.uix.boxlayout.BoxLayout):
    """Class of the widget for a list of curve specification widgets."""

    shared_state = kivy.properties.ObjectProperty()
    """Shared state object."""

    def __init__(self, **kwargs) -> None:
        """Constructor."""
        self._model = CurveSpecListWidgetModel()
        super().__init__(**kwargs)

    def on_kv_post(self, base_widget: object) -> None:
        """Callback after the kv rules of this widget are applied."""
        super().on_kv_post(base_widget)

        self._model.shared_state = self.shared_state
        self._model.init()

        for model in self._model.curve_models:
            curve_spec_widget = CurveSpecWidget(model=model)
            self.ids.curve_spec_list_layout.add_widget(curve_spec_widget)
