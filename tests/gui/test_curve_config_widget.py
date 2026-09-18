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

"""Test of CurveConfigWidget."""

import pathlib

import kivy.lang

import func_sketch._gui.curve_config_widget as curve_config_widget_module
from func_sketch._cpp import RGBColor
from func_sketch._gui.curve_config_widget import CurveConfigWidget
from func_sketch._impl.curve_config import CurveConfig

_KV_FILE = pathlib.Path(curve_config_widget_module.__file__).with_name(
    "curve_config_widget.kv"
)
kivy.lang.Builder.load_file(str(_KV_FILE))


class TestCurveConfigWidgetCurveConfigSync:
    """Test of synchronization of the curve_config property."""

    def test_curve_config_reflects_expression_text_and_curve_color(self) -> None:
        """Test that curve_config combines expression_text and curve_color."""
        widget = CurveConfigWidget()
        color = RGBColor(10, 20, 30)
        widget.expression_text = "x**2"
        widget.curve_color = color

        curve_config = widget.curve_config

        assert curve_config.function_expression_str == "x**2"
        assert curve_config.color is color

    def test_curve_config_is_cached_between_reads(self) -> None:
        """Test that curve_config returns the same object while unchanged."""
        widget = CurveConfigWidget(curve_color=RGBColor(0, 0, 0))

        assert widget.curve_config is widget.curve_config

    def test_set_curve_config_updates_expression_text_and_curve_color(self) -> None:
        """Test that setting curve_config updates expression_text and curve_color."""
        widget = CurveConfigWidget()
        color = RGBColor(1, 2, 3)
        new_curve_config = CurveConfig(function_expression_str="sin(x)", color=color)

        widget.curve_config = new_curve_config

        assert widget.expression_text == "sin(x)"
        assert widget.curve_color is color

    def test_set_curve_config_updates_expression_text_input(self) -> None:
        """Test that setting curve_config propagates down to expression_text_input."""
        widget = CurveConfigWidget()
        new_curve_config = CurveConfig(
            function_expression_str="cos(x)", color=RGBColor(4, 5, 6)
        )

        widget.curve_config = new_curve_config

        assert widget.ids.expression_text_input.text == "cos(x)"

    def test_curve_config_changes_when_expression_text_changes(self) -> None:
        """Test that curve_config is notified when expression_text changes."""
        color = RGBColor(0, 0, 0)
        widget = CurveConfigWidget(curve_color=color)
        on_curve_config_changed = []
        widget.bind(
            curve_config=lambda _instance, value: on_curve_config_changed.append(value)
        )

        widget.expression_text = "tan(x)"

        assert len(on_curve_config_changed) == 1
        assert on_curve_config_changed[0].function_expression_str == "tan(x)"
        assert on_curve_config_changed[0].color is color

    def test_curve_config_changes_when_curve_color_changes(self) -> None:
        """Test that curve_config is notified when curve_color changes."""
        widget = CurveConfigWidget(expression_text="x")
        on_curve_config_changed = []
        widget.bind(
            curve_config=lambda _instance, value: on_curve_config_changed.append(value)
        )

        color = RGBColor(7, 8, 9)
        widget.curve_color = color

        assert len(on_curve_config_changed) == 1
        assert on_curve_config_changed[0].function_expression_str == "x"
        assert on_curve_config_changed[0].color is color

    def test_curve_config_changes_when_input_text_changes(self) -> None:
        """Test that curve_config is notified when expression_text_input.text changes."""
        color = RGBColor(1, 1, 1)
        widget = CurveConfigWidget(curve_color=color)
        on_curve_config_changed = []
        widget.bind(
            curve_config=lambda _instance, value: on_curve_config_changed.append(value)
        )

        widget.ids.expression_text_input.text = "log(x)"

        assert len(on_curve_config_changed) == 1
        assert on_curve_config_changed[0].function_expression_str == "log(x)"
        assert on_curve_config_changed[0].color is color
