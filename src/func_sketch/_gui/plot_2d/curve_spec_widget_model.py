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

"""Class of the view model of a curve specification."""

import kivy.event
import kivy.properties

from func_sketch._cpp import ExplicitCurveSpec, RGBColor


class CurveSpecWidgetModel(kivy.event.EventDispatcher):
    """Class of the view model of a curve specification."""

    expression_text = kivy.properties.StringProperty()
    """Text of the function expression."""

    curve_name = kivy.properties.StringProperty()
    """Name of the curve."""

    curve_color = kivy.properties.ObjectProperty(RGBColor(0, 0, 0))
    """Color of the curve."""

    error_message = kivy.properties.StringProperty("")
    """Error message related to the curve specification."""

    def _get_curve_spec(self) -> ExplicitCurveSpec:
        """Get the curve specification.

        Returns:
            Curve specification.
        """
        return ExplicitCurveSpec(
            name=self.curve_name,
            function_expression_str=self.expression_text,
            color=self.curve_color,
        )

    def _set_curve_spec(self, curve_spec: ExplicitCurveSpec) -> None:
        """Set the curve specification.

        Args:
            curve_spec: Curve specification.
        """
        self.curve_name = curve_spec.name
        self.expression_text = curve_spec.function_expression_str
        self.curve_color = curve_spec.color

    curve_spec = kivy.properties.AliasProperty(
        _get_curve_spec,
        _set_curve_spec,
        bind=("curve_name", "expression_text", "curve_color"),
        cache=True,
    )
    """Curve specification."""
