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

"""Test of ParameterizedCurveSpecWidgetModel."""

from func_sketch._cpp import CurveSampler, ParameterizedCurveSpec, RGBColor
from func_sketch._gui.common.constants import (
    DEFAULT_PARAMETER_RANGE,
    DEFAULT_PLOT_CONFIG,
    DEFAULT_PLOT_RANGE,
)
from func_sketch._gui.plot_2d.parameterized_curve_spec_widget_model import (
    ParameterizedCurveSpecWidgetModel,
)


def _create_model(**kwargs) -> ParameterizedCurveSpecWidgetModel:
    curve_sampler = CurveSampler(DEFAULT_PLOT_RANGE, DEFAULT_PLOT_CONFIG.sampling)
    return ParameterizedCurveSpecWidgetModel(curve_sampler=curve_sampler, **kwargs)


class TestParameterizedCurveSpecWidgetModelExpressionTextSync:
    """Test of synchronization of the expression text properties."""

    def test_initial_expression_texts(self) -> None:
        """Test that the initial expression texts are set to the text input models."""
        model = _create_model(x_expression_text="cos(t)", y_expression_text="sin(t)")

        assert model.x_expression_text_input_model.expression_text == "cos(t)"
        assert model.y_expression_text_input_model.expression_text == "sin(t)"

    def test_expression_texts_to_text_input_models(self) -> None:
        """Test that changes of expression texts are reflected to the text input models."""
        model = _create_model()

        model.x_expression_text = "t"
        model.y_expression_text = "t**2"

        assert model.x_expression_text_input_model.expression_text == "t"
        assert model.y_expression_text_input_model.expression_text == "t**2"

    def test_text_input_models_to_expression_texts(self) -> None:
        """Test that changes in the text input models are reflected to expression texts."""
        model = _create_model()

        model.x_expression_text_input_model.expression_text = "cos(t)"
        model.y_expression_text_input_model.expression_text = "sin(t)"

        assert model.x_expression_text == "cos(t)"
        assert model.y_expression_text == "sin(t)"

    def test_parameter_name_in_token_candidates(self) -> None:
        """Test that the parameter "t" is a candidate of tokens."""
        model = _create_model()
        text_input_model = model.x_expression_text_input_model

        text_input_model.expression_text = "t"
        text_input_model.cursor_position = 1
        text_input_model.on_key_type("t")

        assert text_input_model.token_candidates is not None
        assert text_input_model.token_candidates[0].name == "t"


class TestParameterizedCurveSpecWidgetModelCurveSpecSync:
    """Test of synchronization of the curve_spec property."""

    def test_default_parameter_range(self) -> None:
        """Test that the default parameter range is used initially."""
        model = _create_model()

        assert model.curve_spec.parameter_range == DEFAULT_PARAMETER_RANGE

    def test_curve_spec_reflects_properties(self) -> None:
        """Test that curve_spec combines the properties."""
        model = _create_model()
        color = RGBColor(10, 20, 30)
        model.x_expression_text = "cos(t)"
        model.y_expression_text = "sin(t)"
        model.parameter_min = -1.0
        model.parameter_max = 2.0
        model.curve_color = color

        curve_spec = model.curve_spec

        assert curve_spec.x_expression_str == "cos(t)"
        assert curve_spec.y_expression_str == "sin(t)"
        assert curve_spec.parameter_range == (-1.0, 2.0)
        assert curve_spec.color == color

    def test_curve_spec_is_cached_between_reads(self) -> None:
        """Test that curve_spec returns the same object while unchanged."""
        model = _create_model(curve_color=RGBColor(0, 0, 0))

        assert model.curve_spec is model.curve_spec

    def test_set_curve_spec_updates_properties(self) -> None:
        """Test that setting curve_spec updates the properties."""
        model = _create_model()
        color = RGBColor(1, 2, 3)
        new_curve_spec = ParameterizedCurveSpec(
            name="Curve",
            x_expression_str="cos(t)",
            y_expression_str="sin(t)",
            parameter_range=(-1.0, 2.0),
            color=color,
        )

        model.curve_spec = new_curve_spec

        assert model.curve_name == "Curve"
        assert model.x_expression_text == "cos(t)"
        assert model.y_expression_text == "sin(t)"
        assert model.parameter_min == -1.0
        assert model.parameter_max == 2.0
        assert model.curve_color == color

    def test_curve_spec_changes_when_x_expression_text_changes(self) -> None:
        """Test that curve_spec is notified when x_expression_text changes."""
        model = _create_model(y_expression_text="sin(t)")
        on_curve_spec_changed = []
        model.bind(
            curve_spec=lambda _instance, value: on_curve_spec_changed.append(value)
        )

        model.x_expression_text = "cos(t)"

        assert len(on_curve_spec_changed) == 1
        assert on_curve_spec_changed[0].x_expression_str == "cos(t)"
        assert on_curve_spec_changed[0].y_expression_str == "sin(t)"

    def test_curve_spec_changes_when_y_expression_text_changes(self) -> None:
        """Test that curve_spec is notified when y_expression_text changes."""
        model = _create_model(x_expression_text="cos(t)")
        on_curve_spec_changed = []
        model.bind(
            curve_spec=lambda _instance, value: on_curve_spec_changed.append(value)
        )

        model.y_expression_text = "sin(t)"

        assert len(on_curve_spec_changed) == 1
        assert on_curve_spec_changed[0].x_expression_str == "cos(t)"
        assert on_curve_spec_changed[0].y_expression_str == "sin(t)"

    def test_curve_spec_changes_when_parameter_range_changes(self) -> None:
        """Test that curve_spec is notified when the parameter range changes."""
        model = _create_model()
        on_curve_spec_changed = []
        model.bind(
            curve_spec=lambda _instance, value: on_curve_spec_changed.append(value)
        )

        model.parameter_min = -1.0
        model.parameter_max = 2.0

        assert len(on_curve_spec_changed) == 2
        assert on_curve_spec_changed[0].parameter_range == (
            -1.0,
            DEFAULT_PARAMETER_RANGE[1],
        )
        assert on_curve_spec_changed[1].parameter_range == (-1.0, 2.0)

    def test_curve_spec_changes_when_curve_color_changes(self) -> None:
        """Test that curve_spec is notified when curve_color changes."""
        model = _create_model(x_expression_text="cos(t)")
        on_curve_spec_changed = []
        model.bind(
            curve_spec=lambda _instance, value: on_curve_spec_changed.append(value)
        )

        color = RGBColor(7, 8, 9)
        model.curve_color = color

        assert len(on_curve_spec_changed) == 1
        assert on_curve_spec_changed[0].x_expression_str == "cos(t)"
        assert on_curve_spec_changed[0].color == color

    def test_curve_spec_uses_default_curve_name_when_curve_name_is_empty(
        self,
    ) -> None:
        """Test that curve_spec uses default_curve_name when curve_name is empty."""
        model = _create_model(
            curve_color=RGBColor(0, 0, 0), default_curve_name="Default"
        )

        model.curve_name = "Curve"
        assert model.curve_spec.name == "Curve"

        model.curve_name = ""
        assert model.curve_spec.name == "Default"
