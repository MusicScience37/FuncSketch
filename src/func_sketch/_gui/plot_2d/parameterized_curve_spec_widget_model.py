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

"""Class of the view model of a specification of a parameterized curve."""

import kivy.event
import kivy.properties

from func_sketch._cpp import CurveSampler, ParameterizedCurveSpec, RGBColor
from func_sketch._gui.common.constants import DEFAULT_PARAMETER_RANGE
from func_sketch._gui.common.sync_properties import sync_properties
from func_sketch._gui.plot_2d.expression_text_input_model import (
    ExpressionTextInputModel,
)


class ParameterizedCurveSpecWidgetModel(kivy.event.EventDispatcher):
    """Class of the view model of a specification of a parameterized curve."""

    x_expression_text = kivy.properties.StringProperty()
    """Text of the function expression for the x coordinate."""

    y_expression_text = kivy.properties.StringProperty()
    """Text of the function expression for the y coordinate."""

    parameter_min = kivy.properties.NumericProperty(DEFAULT_PARAMETER_RANGE[0])
    """Minimum value of the parameter."""

    parameter_max = kivy.properties.NumericProperty(DEFAULT_PARAMETER_RANGE[1])
    """Maximum value of the parameter."""

    curve_name = kivy.properties.StringProperty()
    """Name of the curve."""

    default_curve_name = kivy.properties.StringProperty()
    """Default name of the curve used when the name is empty."""

    curve_color = kivy.properties.ObjectProperty(RGBColor(0, 0, 0))
    """Color of the curve."""

    def __init__(self, curve_sampler: CurveSampler, **kwargs) -> None:
        """Constructor."""
        self.x_expression_text_input_model = ExpressionTextInputModel(
            curve_sampler=curve_sampler, parameter_names=["t"]
        )
        self.y_expression_text_input_model = ExpressionTextInputModel(
            curve_sampler=curve_sampler, parameter_names=["t"]
        )
        super().__init__(**kwargs)
        sync_properties(
            self,
            "x_expression_text",
            self.x_expression_text_input_model,
            "expression_text",
        )
        sync_properties(
            self,
            "y_expression_text",
            self.y_expression_text_input_model,
            "expression_text",
        )

    def _get_curve_spec(self) -> ParameterizedCurveSpec:
        """Get the curve specification.

        Returns:
            Curve specification.
        """
        return ParameterizedCurveSpec(
            name=self.curve_name or self.default_curve_name,
            x_expression_str=self.x_expression_text,
            y_expression_str=self.y_expression_text,
            parameter_range=(self.parameter_min, self.parameter_max),
            color=self.curve_color,
        )

    def _set_curve_spec(self, curve_spec: ParameterizedCurveSpec) -> None:
        """Set the curve specification.

        Args:
            curve_spec: Curve specification.
        """
        self.curve_name = (
            "" if curve_spec.name == self.default_curve_name else curve_spec.name
        )
        self.x_expression_text = curve_spec.x_expression_str
        self.y_expression_text = curve_spec.y_expression_str
        self.parameter_min, self.parameter_max = curve_spec.parameter_range
        self.curve_color = curve_spec.color

    curve_spec = kivy.properties.AliasProperty(
        _get_curve_spec,
        _set_curve_spec,
        bind=(
            "curve_name",
            "default_curve_name",
            "x_expression_text",
            "y_expression_text",
            "parameter_min",
            "parameter_max",
            "curve_color",
        ),
        cache=True,
    )
    """Curve specification."""
