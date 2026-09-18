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

from func_sketch._gui.sync_properties import sync_properties
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

    curve_name = kivy.properties.StringProperty()
    """Name of the curve."""

    curve_color = kivy.properties.ObjectProperty()
    """Color of the curve."""

    error_message = kivy.properties.StringProperty("")
    """Error message related to the curve configuration."""

    def on_kv_post(self, base_widget: object) -> None:
        """Callback after the kv rules of this widget are applied."""
        super().on_kv_post(base_widget)
        sync_properties(self, "expression_text", self.ids.expression_text_input, "text")

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
