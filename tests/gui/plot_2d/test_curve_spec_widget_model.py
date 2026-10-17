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

from func_sketch._cpp import (
    CurveSampler,
    ExplicitCurveSpec,
    ParameterizedCurveSpec,
    RGBColor,
)
from func_sketch._gui.common.constants import (
    DEFAULT_PLOT_CONFIG,
    DEFAULT_PLOT_RANGE,
)
from func_sketch._gui.plot_2d.curve_spec_widget_model import CurveSpecWidgetModel
from func_sketch._impl.curve_type import CurveType

_INITIAL_COLOR = RGBColor(1, 2, 3)


def _create_model(**kwargs) -> CurveSpecWidgetModel:
    curve_sampler = CurveSampler(DEFAULT_PLOT_RANGE, DEFAULT_PLOT_CONFIG.sampling)
    initial_curve_spec = ExplicitCurveSpec(
        name="Default", function_expression_str="", color=_INITIAL_COLOR
    )
    return CurveSpecWidgetModel(
        curve_sampler=curve_sampler, initial_curve_spec=initial_curve_spec, **kwargs
    )


class TestCurveSpecWidgetModel:
    """Test of CurveSpecWidgetModel."""

    def test_initial_state(self) -> None:
        """Test that the initial curve specification is set to the child models."""
        model = _create_model()

        assert model.curve_type == CurveType.EXPLICIT
        assert isinstance(model.curve_spec, ExplicitCurveSpec)
        assert model.curve_name == "Default"
        for child_model in (
            model.explicit_curve_spec_widget_model,
            model.parameterized_curve_spec_widget_model,
        ):
            assert child_model.default_curve_name == "Default"
            assert child_model.curve_color == _INITIAL_COLOR

    def test_curve_spec_from_child_of_current_type(self) -> None:
        """Test that curve_spec is notified only for changes in the child of the current type."""
        model = _create_model()
        on_curve_spec_changed = []
        model.bind(
            curve_spec=lambda _instance, value: on_curve_spec_changed.append(value)
        )

        model.parameterized_curve_spec_widget_model.x_expression_text = "cos(t)"
        assert not on_curve_spec_changed

        model.explicit_curve_spec_widget_model.expression_text = "x**2"
        assert len(on_curve_spec_changed) == 1
        assert isinstance(on_curve_spec_changed[0], ExplicitCurveSpec)
        assert on_curve_spec_changed[0].function_expression_str == "x**2"

    def test_switch_curve_type(self) -> None:
        """Test that switching curve_type switches curve_spec."""
        model = _create_model()
        model.explicit_curve_spec_widget_model.expression_text = "x**2"
        model.parameterized_curve_spec_widget_model.x_expression_text = "cos(t)"
        on_curve_spec_changed = []
        model.bind(
            curve_spec=lambda _instance, value: on_curve_spec_changed.append(value)
        )

        model.curve_type = CurveType.PARAMETERIZED

        assert len(on_curve_spec_changed) == 1
        assert isinstance(model.curve_spec, ParameterizedCurveSpec)
        assert model.curve_spec.x_expression_str == "cos(t)"

        model.curve_type = CurveType.EXPLICIT

        assert len(on_curve_spec_changed) == 2
        assert isinstance(model.curve_spec, ExplicitCurveSpec)
        assert model.curve_spec.function_expression_str == "x**2"

    def test_set_explicit_curve_spec(self) -> None:
        """Test that setting an explicit curve specification updates the child model."""
        model = _create_model()
        model.curve_type = CurveType.PARAMETERIZED

        model.curve_spec = ExplicitCurveSpec(
            name="Curve", function_expression_str="sin(x)", color=_INITIAL_COLOR
        )

        assert model.curve_type == CurveType.EXPLICIT
        child_model = model.explicit_curve_spec_widget_model
        assert child_model.curve_name == "Curve"
        assert child_model.expression_text == "sin(x)"

    def test_set_parameterized_curve_spec(self) -> None:
        """Test that setting a parameterized curve specification updates the child model."""
        model = _create_model()

        model.curve_spec = ParameterizedCurveSpec(
            name="Curve",
            x_expression_str="cos(t)",
            y_expression_str="sin(t)",
            parameter_range=(-1.0, 2.0),
            color=_INITIAL_COLOR,
        )

        assert model.curve_type == CurveType.PARAMETERIZED
        child_model = model.parameterized_curve_spec_widget_model
        assert child_model.curve_name == "Curve"
        assert child_model.x_expression_text == "cos(t)"
        assert child_model.y_expression_text == "sin(t)"
        assert child_model.parameter_min == -1.0
        assert child_model.parameter_max == 2.0

    def test_curve_name(self) -> None:
        """Test that curve_name reflects the name in curve_spec."""
        model = _create_model()

        model.explicit_curve_spec_widget_model.curve_name = "Curve"
        assert model.curve_name == "Curve"

        model.curve_type = CurveType.PARAMETERIZED
        assert model.curve_name == "Default"

    def test_curve_color_as_rgba(self) -> None:
        """Test that curve_color_as_rgba reflects the color in curve_spec."""
        model = _create_model()

        model.explicit_curve_spec_widget_model.curve_color = RGBColor(255, 0, 51)

        assert model.curve_color_as_rgba == (1.0, 0.0, 0.2, 1.0)
