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

"""Class of widgets to configure curves."""

import kivy.properties
import kivy.uix.boxlayout
import kivy.uix.textinput

from func_sketch._impl.curve_config import CurveConfig


class CurveConfigWidget(kivy.uix.boxlayout.BoxLayout):
    """Class of widgets to configure curves.

    Note:
        Following properties can be used:
        - expression_text (writable)
        - curve_name (writable)
        - curve_color (writable)
        - error_message (writable)
        - curve_config (writable)
    """

    expression_text_input = kivy.properties.ObjectProperty()

    def _get_expression_text(self) -> str:
        """Get the expression text.

        Returns:
            Expression text.
        """
        return self.expression_text_input.text if self.expression_text_input else ""

    def _set_expression_text(self, expression_text: str) -> None:
        """Set the expression text.

        Args:
            expression_text: Expression text.
        """
        if self.expression_text_input:
            self.expression_text_input.text = expression_text

    expression_text = kivy.properties.AliasProperty(
        _get_expression_text,
        _set_expression_text,
        bind=("expression_text_input",),
        cache=False,
    )

    def on_expression_text_input(
        self, _instance: object, value: kivy.uix.textinput.TextInput | None
    ) -> None:
        """Callback when the expression_text_input property is set."""
        if value:
            value.bind(text=self._trigger_expression_text)

    def _trigger_expression_text(self, _instance: object, _value: object) -> None:
        """Trigger the expression text property to update."""
        self.property("expression_text").dispatch(self)

    curve_name = kivy.properties.StringProperty()
    curve_color = kivy.properties.ObjectProperty()
    error_message = kivy.properties.StringProperty("")

    def _get_curve_config(self) -> CurveConfig:
        """Get the curve configuration.

        Returns:
            Curve configuration.
        """
        return CurveConfig(
            function_expression_str=self.expression_text,
            color=self.curve_color,
        )

    def _set_curve_config(self, curve_config: CurveConfig) -> None:
        """Set the curve configuration.

        Args:
            curve_config: Curve configuration.
        """
        self.expression_text = curve_config.function_expression_str
        self.curve_color = curve_config.color

    curve_config = kivy.properties.AliasProperty(
        _get_curve_config,
        _set_curve_config,
        bind=("expression_text", "curve_color"),
        cache=True,
    )
