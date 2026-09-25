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

"""Tests of ExpressionTextInputModel."""

from func_sketch._cpp import CurveSampler
from func_sketch._gui.common.constants import (
    DEFAULT_PLOT_CONFIG,
    DEFAULT_PLOT_RANGE,
)
from func_sketch._gui.plot_2d.expression_text_input_model import (
    ExpressionTextInputModel,
)


def _create_model() -> ExpressionTextInputModel:
    curve_sampler = CurveSampler(DEFAULT_PLOT_RANGE, DEFAULT_PLOT_CONFIG.sampling)
    return ExpressionTextInputModel(curve_sampler=curve_sampler)


class TestExpressionTextInputModel:
    """Tests of ExpressionTextInputModel."""

    def test_init(self) -> None:
        """Test initialization."""
        model = _create_model()

        # expression_text and cursor_position are set from the view class.
        # So check other attributes.
        assert model.current_token_range is None
        assert model.current_token_text is None
        assert model.token_candidates is None

    def test_key_type_in_identifier(self) -> None:
        """Test key typing in an identifier."""
        model = _create_model()

        model.expression_text = " +exa "
        model.cursor_position = 4
        model.on_key_type("x")

        # Characters after the cursor are ignored.
        assert model.current_token_range == (2, 4)
        assert model.current_token_text == "ex"
        assert model.token_candidates is not None
        assert len(model.token_candidates) > 0
        assert model.token_candidates[0] == "exp"

        # Inputs are not changed here.
        assert model.expression_text == " +exa "
        assert model.cursor_position == 4

    def test_key_type_in_identifier_at_beginning(self) -> None:
        """Test key typing in an identifier at the beginning of the text."""
        model = _create_model()

        model.expression_text = "ex"
        model.cursor_position = 2
        model.on_key_type("x")

        assert model.current_token_range == (0, 2)
        assert model.current_token_text == "ex"
        assert model.token_candidates is not None
        assert len(model.token_candidates) > 0
        assert model.token_candidates[0] == "exp"

        # Inputs are not changed here.
        assert model.expression_text == "ex"
        assert model.cursor_position == 2

    def test_key_type_outside_identifier(self) -> None:
        """Test key typing outside an identifier."""
        model = _create_model()

        model.expression_text = " +ex "
        model.cursor_position = 2
        model.on_key_type("+")

        assert model.current_token_range is None
        assert model.current_token_text is None
        assert model.token_candidates is None

        # Inputs are not changed here.
        assert model.expression_text == " +ex "
        assert model.cursor_position == 2

    def test_key_type_start_from_numeric(self) -> None:
        """Test key typing starting from a numeric character."""
        model = _create_model()

        model.expression_text = " +1ex "
        model.cursor_position = 5
        model.on_key_type("x")

        assert model.current_token_range is None
        assert model.current_token_text is None
        assert model.token_candidates is None

        # Inputs are not changed here.
        assert model.expression_text == " +1ex "
        assert model.cursor_position == 5

    def test_key_type_different_from_identifier_characters(self) -> None:
        """Test key typing with a character different from identifier characters."""
        model = _create_model()

        model.expression_text = " +e! "
        model.cursor_position = 4
        model.on_key_type("!")

        assert model.current_token_range is None
        assert model.current_token_text is None
        assert model.token_candidates is None

        # Inputs are not changed here.
        assert model.expression_text == " +e! "
        assert model.cursor_position == 4

    def test_key_type_at_beginning(self) -> None:
        """Test key typing at the beginning of the text."""
        model = _create_model()

        model.expression_text = ""
        model.cursor_position = 0
        model.on_key_type("escape")

        assert model.current_token_range is None
        assert model.current_token_text is None
        assert model.token_candidates is None

        # Inputs are not changed here.
        assert model.expression_text == ""  # ruff: ignore[compare-to-empty-string]
        assert model.cursor_position == 0

    def test_key_type_with_nonascii_character(self) -> None:
        """Test key typing with a non-ASCII character."""
        model = _create_model()

        model.expression_text = " あ"
        model.cursor_position = 2
        model.on_key_type("あ")

        assert model.current_token_range is None
        assert model.current_token_text is None
        assert model.token_candidates is None

        # Inputs are not changed here.
        assert model.expression_text == " あ"
        assert model.cursor_position == 2

    def test_backspace_in_identifier(self) -> None:
        """Test backspace in an identifier."""
        model = _create_model()

        model.expression_text = " +ex "
        model.cursor_position = 4
        model.on_backspace()

        assert model.current_token_range == (2, 4)
        assert model.current_token_text == "ex"
        assert model.token_candidates is not None
        assert len(model.token_candidates) > 0
        assert model.token_candidates[0] == "exp"

        # Inputs are not changed here.
        assert model.expression_text == " +ex "
        assert model.cursor_position == 4

    def test_backspace_removing_whole_identifier(self) -> None:
        """Test backspace removing the whole identifier."""
        model = _create_model()

        model.expression_text = " +e "
        model.cursor_position = 3
        model.on_key_type("e")
        assert model.current_token_text == "e"

        model.expression_text = " + "
        model.cursor_position = 2
        model.on_backspace()

        assert model.current_token_range is None
        assert model.current_token_text is None
        assert model.token_candidates is None

        # Inputs are not changed here.
        assert model.expression_text == " + "
        assert model.cursor_position == 2

    def test_backspace_leaving_numeric_character(self) -> None:
        """Test backspace leaving only a numeric character before the cursor."""
        model = _create_model()

        model.expression_text = " +2e "
        model.cursor_position = 4
        model.on_key_type("e")
        assert model.current_token_text is None

        model.expression_text = " +2 "
        model.cursor_position = 3
        model.on_backspace()

        assert model.current_token_range is None
        assert model.current_token_text is None
        assert model.token_candidates is None

        # Inputs are not changed here.
        assert model.expression_text == " +2 "
        assert model.cursor_position == 3

    def test_clear_current_token(self) -> None:
        """Test clearing the current token."""
        model = _create_model()

        model.expression_text = " +ex "
        model.cursor_position = 4
        model.on_key_type("x")
        assert model.current_token_text == "ex"

        model.clear_current_token()

        assert model.current_token_range is None
        assert model.current_token_text is None
        assert model.token_candidates is None

        # Inputs are not changed here.
        assert model.expression_text == " +ex "
        assert model.cursor_position == 4

    def test_select_token_candidate(self) -> None:
        """Test selecting a token candidate."""
        model = _create_model()

        model.expression_text = " +exa "
        model.cursor_position = 4
        model.on_key_type("x")
        assert model.current_token_range == (2, 4)

        model.select_token_candidate("exp")

        # Characters after the cursor are kept.
        assert model.expression_text == " +expa "  # cspell: ignore expa
        assert model.cursor_position == 5
        assert model.current_token_range is None
        assert model.current_token_text is None
        assert model.token_candidates is None

    def test_select_token_candidate_without_current_token(self) -> None:
        """Test selecting a token candidate without the current token."""
        model = _create_model()

        model.expression_text = " +ex "
        model.cursor_position = 2
        model.on_key_type("+")
        assert model.current_token_range is None

        model.select_token_candidate("exp")

        # Inputs are not changed here.
        assert model.expression_text == " +ex "
        assert model.cursor_position == 2
        assert model.current_token_range is None
        assert model.current_token_text is None
        assert model.token_candidates is None
