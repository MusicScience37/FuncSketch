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

"""Test of CurveSpecWidget."""

import kivy.lang

from func_sketch._cpp import ExplicitCurveSpec, RGBColor
from func_sketch._gui.plot_2d.curve_spec_widget import CurveSpecWidget

kivy.lang.Builder.load_file("plot_2d/curve_spec_widget.kv")


def _colors_equal(lhs: RGBColor, rhs: RGBColor) -> bool:
    """Check whether two colors have the same components.

    Args:
        lhs: First color.
        rhs: Second color.

    Returns:
        True if the colors have the same components.
    """
    return (lhs.r, lhs.g, lhs.b) == (rhs.r, rhs.g, rhs.b)


class TestCurveSpecWidgetCurveSpecSync:
    """Test of synchronization of the curve_spec property."""

    def test_curve_spec_reflects_expression_text_and_curve_color(self) -> None:
        """Test that curve_spec combines expression_text and curve_color."""
        widget = CurveSpecWidget()
        color = RGBColor(10, 20, 30)
        widget.expression_text = "x**2"
        widget.curve_color = color

        curve_spec = widget.curve_spec

        assert curve_spec.function_expression_str == "x**2"
        assert _colors_equal(curve_spec.color, color)

    def test_curve_spec_is_cached_between_reads(self) -> None:
        """Test that curve_spec returns the same object while unchanged."""
        widget = CurveSpecWidget(curve_color=RGBColor(0, 0, 0))

        assert widget.curve_spec is widget.curve_spec

    def test_set_curve_spec_updates_expression_text_and_curve_color(self) -> None:
        """Test that setting curve_spec updates expression_text and curve_color."""
        widget = CurveSpecWidget()
        color = RGBColor(1, 2, 3)
        new_curve_spec = ExplicitCurveSpec(
            name="Curve", function_expression_str="sin(x)", color=color
        )

        widget.curve_spec = new_curve_spec

        assert widget.expression_text == "sin(x)"
        assert _colors_equal(widget.curve_color, color)

    def test_set_curve_spec_updates_expression_text_input(self) -> None:
        """Test that setting curve_spec propagates down to expression_text_input."""
        widget = CurveSpecWidget()
        new_curve_spec = ExplicitCurveSpec(
            name="Curve", function_expression_str="cos(x)", color=RGBColor(4, 5, 6)
        )

        widget.curve_spec = new_curve_spec

        assert widget.ids.expression_text_input.text == "cos(x)"

    def test_curve_spec_changes_when_expression_text_changes(self) -> None:
        """Test that curve_spec is notified when expression_text changes."""
        color = RGBColor(0, 0, 0)
        widget = CurveSpecWidget(curve_color=color)
        on_curve_spec_changed = []
        widget.bind(
            curve_spec=lambda _instance, value: on_curve_spec_changed.append(value)
        )

        widget.expression_text = "tan(x)"

        assert len(on_curve_spec_changed) == 1
        assert on_curve_spec_changed[0].function_expression_str == "tan(x)"
        assert _colors_equal(on_curve_spec_changed[0].color, color)

    def test_curve_spec_changes_when_curve_color_changes(self) -> None:
        """Test that curve_spec is notified when curve_color changes."""
        widget = CurveSpecWidget(expression_text="x")
        on_curve_spec_changed = []
        widget.bind(
            curve_spec=lambda _instance, value: on_curve_spec_changed.append(value)
        )

        color = RGBColor(7, 8, 9)
        widget.curve_color = color

        assert len(on_curve_spec_changed) == 1
        assert on_curve_spec_changed[0].function_expression_str == "x"
        assert _colors_equal(on_curve_spec_changed[0].color, color)

    def test_curve_spec_changes_when_input_text_changes(self) -> None:
        """Test that curve_spec is notified when expression_text_input.text changes."""
        color = RGBColor(1, 1, 1)
        widget = CurveSpecWidget(curve_color=color)
        on_curve_spec_changed = []
        widget.bind(
            curve_spec=lambda _instance, value: on_curve_spec_changed.append(value)
        )

        widget.ids.expression_text_input.text = "log(x)"

        assert len(on_curve_spec_changed) == 1
        assert on_curve_spec_changed[0].function_expression_str == "log(x)"
        assert _colors_equal(on_curve_spec_changed[0].color, color)
