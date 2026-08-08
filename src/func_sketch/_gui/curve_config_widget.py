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

    expression_text = kivy.properties.StringProperty()
    """Text of the function expression."""

    expression_text_input = kivy.properties.ObjectProperty()
    """TextInput widget for the function expression."""

    def __init__(self, **kwargs: object) -> None:
        """Constructor."""
        self._syncing_expression_text = False
        super().__init__(**kwargs)

    def _sync_expression_text_from_parent_to_child(
        self, _instance: object, _value: object
    ) -> None:
        """Sync expression text from parent to child."""
        if self._syncing_expression_text:
            return
        self._syncing_expression_text = True
        try:
            if self.expression_text_input:
                self.expression_text_input.text = self.expression_text
        finally:
            self._syncing_expression_text = False

    def _sync_expression_text_from_child_to_parent(
        self, _instance: object, _value: object
    ) -> None:
        """Sync expression text from child to parent."""
        if self._syncing_expression_text:
            return
        self._syncing_expression_text = True
        try:
            self.expression_text = self.expression_text_input.text
        finally:
            self._syncing_expression_text = False

    def on_expression_text_input(
        self, _instance: object, value: kivy.uix.textinput.TextInput | None
    ) -> None:
        """Callback when the expression_text_input property is set."""
        if value:
            value.bind(text=self._sync_expression_text_from_child_to_parent)
            self.bind(expression_text=self._sync_expression_text_from_parent_to_child)
            self._sync_expression_text_from_parent_to_child(None, None)

    curve_name = kivy.properties.StringProperty()
    """Name of the curve."""

    curve_color = kivy.properties.ObjectProperty()
    """Color of the curve."""

    error_message = kivy.properties.StringProperty("")
    """Error message related to the curve configuration."""

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
    """Curve configuration."""
