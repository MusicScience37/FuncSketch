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

"""Class of widgets of curve specifications."""

import kivy.uix.boxlayout
import kivy.uix.widget

from func_sketch._gui.common.sync_properties import sync_properties
from func_sketch._gui.plot_2d.curve_spec_widget_model import CurveSpecWidgetModel
from func_sketch._gui.plot_2d.explicit_curve_spec_widget import (
    ExplicitCurveSpecWidget,
)
from func_sketch._gui.plot_2d.parameterized_curve_spec_widget import (
    ParameterizedCurveSpecWidget,
)
from func_sketch._impl.curve_type import CurveType


class CurveSpecWidget(kivy.uix.boxlayout.BoxLayout):
    """Class of widgets of curve specifications."""

    def __init__(self, model: CurveSpecWidgetModel, **kwargs) -> None:
        """Constructor."""
        self._model = model
        self._explicit_curve_spec_widget = ExplicitCurveSpecWidget(
            model=model.explicit_curve_spec_widget_model
        )
        self._parameterized_curve_spec_widget = ParameterizedCurveSpecWidget(
            model=model.parameterized_curve_spec_widget_model
        )
        super().__init__(**kwargs)

    @property
    def explicit_curve_spec_widget(self) -> ExplicitCurveSpecWidget:
        """Widget of the specification of the explicit curve."""
        return self._explicit_curve_spec_widget

    @property
    def parameterized_curve_spec_widget(self) -> ParameterizedCurveSpecWidget:
        """Widget of the specification of the parameterized curve."""
        return self._parameterized_curve_spec_widget

    def on_kv_post(self, base_widget: object) -> None:
        """Callback after the kv rules of this widget are applied."""
        super().on_kv_post(base_widget)
        sync_properties(
            self._model, "curve_type", self.ids.curve_type_selector, "selected"
        )
        self._model.bind(curve_type=lambda *_: self._update_curve_spec_details())
        self._update_curve_spec_details()

    def _update_curve_spec_details(self) -> None:
        """Show the widget of the specification of the current type of the curve."""
        widget: kivy.uix.widget.Widget
        if self._model.curve_type == CurveType.EXPLICIT:
            widget = self._explicit_curve_spec_widget
        elif self._model.curve_type == CurveType.PARAMETERIZED:
            widget = self._parameterized_curve_spec_widget
        else:
            raise ValueError(f"Unsupported curve type: {self._model.curve_type}")
        layout = self.ids.curve_spec_details_layout
        layout.clear_widgets()
        layout.add_widget(widget)
