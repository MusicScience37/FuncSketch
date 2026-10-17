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

"""Class of widgets of specifications of parameterized curves."""

import kivy.uix.gridlayout

from func_sketch._gui.common.sync_properties import sync_properties
from func_sketch._gui.plot_2d.parameterized_curve_spec_widget_model import (
    ParameterizedCurveSpecWidgetModel,
)


class ParameterizedCurveSpecWidget(kivy.uix.gridlayout.GridLayout):
    """Class of widgets of specifications of parameterized curves."""

    def __init__(self, model: ParameterizedCurveSpecWidgetModel, **kwargs) -> None:
        """Constructor."""
        self._model = model
        super().__init__(**kwargs)

    def on_kv_post(self, base_widget: object) -> None:
        """Callback after the kv rules of this widget are applied."""
        super().on_kv_post(base_widget)
        sync_properties(
            self._model, "parameter_min", self.ids.parameter_min_text_input, "value"
        )
        sync_properties(
            self._model, "parameter_max", self.ids.parameter_max_text_input, "value"
        )
        sync_properties(self._model, "curve_name", self.ids.name_text_input, "text")
