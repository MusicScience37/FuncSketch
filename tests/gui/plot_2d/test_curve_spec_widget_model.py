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

"""Test of CurveSpecWidgetModel."""

from func_sketch._cpp import ExplicitCurveSpec, RGBColor
from func_sketch._gui.plot_2d.curve_spec_widget_model import CurveSpecWidgetModel


class TestCurveSpecWidgetModelCurveSpecSync:
    """Test of synchronization of the curve_spec property."""

    def test_curve_spec_reflects_expression_text_and_curve_color(self) -> None:
        """Test that curve_spec combines expression_text and curve_color."""
        model = CurveSpecWidgetModel()
        color = RGBColor(10, 20, 30)
        model.expression_text = "x**2"
        model.curve_color = color

        curve_spec = model.curve_spec

        assert curve_spec.function_expression_str == "x**2"
        assert curve_spec.color == color

    def test_curve_spec_is_cached_between_reads(self) -> None:
        """Test that curve_spec returns the same object while unchanged."""
        model = CurveSpecWidgetModel(curve_color=RGBColor(0, 0, 0))

        assert model.curve_spec is model.curve_spec

    def test_set_curve_spec_updates_curve_name_expression_text_and_curve_color(
        self,
    ) -> None:
        """Test that setting curve_spec updates curve_name, expression_text and curve_color."""
        model = CurveSpecWidgetModel()
        color = RGBColor(1, 2, 3)
        new_curve_spec = ExplicitCurveSpec(
            name="Curve", function_expression_str="sin(x)", color=color
        )

        model.curve_spec = new_curve_spec

        assert model.curve_name == "Curve"
        assert model.expression_text == "sin(x)"
        assert model.curve_color == color

    def test_curve_spec_changes_when_expression_text_changes(self) -> None:
        """Test that curve_spec is notified when expression_text changes."""
        color = RGBColor(0, 0, 0)
        model = CurveSpecWidgetModel(curve_color=color)
        on_curve_spec_changed = []
        model.bind(
            curve_spec=lambda _instance, value: on_curve_spec_changed.append(value)
        )

        model.expression_text = "tan(x)"

        assert len(on_curve_spec_changed) == 1
        assert on_curve_spec_changed[0].function_expression_str == "tan(x)"
        assert on_curve_spec_changed[0].color == color

    def test_curve_spec_changes_when_curve_color_changes(self) -> None:
        """Test that curve_spec is notified when curve_color changes."""
        model = CurveSpecWidgetModel(expression_text="x")
        on_curve_spec_changed = []
        model.bind(
            curve_spec=lambda _instance, value: on_curve_spec_changed.append(value)
        )

        color = RGBColor(7, 8, 9)
        model.curve_color = color

        assert len(on_curve_spec_changed) == 1
        assert on_curve_spec_changed[0].function_expression_str == "x"
        assert on_curve_spec_changed[0].color == color
