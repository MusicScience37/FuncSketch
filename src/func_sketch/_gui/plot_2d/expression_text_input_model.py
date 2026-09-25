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

"""Class of the view model of the text input of function expressions."""

import re

import kivy.event
import kivy.properties

from func_sketch._cpp import CurveSampler
from func_sketch._gui.common.constants import NUM_EXPRESSION_TOKEN_CANDIDATES
from func_sketch._impl.token_candidate_finder import TokenCandidateFinder

_EXPRESSION_TOKEN_PATTERN = re.compile(r"[a-zA-Z_][a-zA-Z0-9_]*")


def _is_identifier_char(char: str) -> bool:
    """Check if the character is valid in an identifier.

    Args:
        char: Character to check.

    Returns:
        True if the character is valid in an identifier, False otherwise.

    Note:
        This function returns True for numeric characters,
        which can't be the first character of an identifier.
        So the overall token must be checked after it is extracted.
    """
    return char.isascii() and (char.isalnum() or char == "_")


class ExpressionTextInputModel(kivy.event.EventDispatcher):
    """Class of the view model of the text input of function expressions."""

    expression_text = kivy.properties.StringProperty()
    """Text of the function expression."""

    cursor_position = kivy.properties.NumericProperty()
    """Position of the cursor in the text input.
    Implementation assumes an integer value and call int() without notifying type errors."""

    current_token_range = kivy.properties.ObjectProperty(None, allownone=True)
    """Range of the current token in the text input. A pair of (start, end) indices."""

    current_token_text = kivy.properties.StringProperty(None, allownone=True)
    """Text of the current token in the text input."""

    token_candidates = kivy.properties.ObjectProperty(None, allownone=True)
    """List of token candidates based on the current token."""

    def __init__(self, curve_sampler: CurveSampler, **kwargs) -> None:
        super().__init__(**kwargs)

        self._curve_sampler = curve_sampler
        self._token_candidate_finder = TokenCandidateFinder(
            math_function_list=self._curve_sampler.math_function_list(),
            constant_list=self._curve_sampler.constant_list(),
            # Currently, "x" is the only parameter name.
            parameter_names=["x"],
            limit=NUM_EXPRESSION_TOKEN_CANDIDATES,
        )

    def on_key_type(self, key: str) -> None:
        """Callback when a key is typed in the text input.

        Args:
            key: The character that was typed.

        Note:
            Call this method after setting expression_text and cursor_position.
        """
        if not _is_identifier_char(key):
            self.current_token_range = None
            self.current_token_text = None
            self.token_candidates = None
            return

        self._update_current_token()
        self._update_token_candidates()

    def _update_current_token(self) -> None:
        """Update the current token at the current cursor position."""
        text = self.expression_text
        cursor = int(self.cursor_position)

        start = cursor
        while start > 0 and _is_identifier_char(text[start - 1]):
            start -= 1

        # The end position is fixed to cursor position to prevent overwriting existing text.
        end = cursor
        cursor_text_candidate = text[start:end]
        if not _EXPRESSION_TOKEN_PATTERN.fullmatch(cursor_text_candidate):
            self.current_token_range = None
            self.current_token_text = None
            return

        self.current_token_range = (start, end)
        self.current_token_text = cursor_text_candidate

    def _update_token_candidates(self) -> None:
        """Update the list of token candidates based on the current token."""
        current_token = self.current_token_text
        if current_token is None:
            self.token_candidates = None
            return

        candidate_info_list = self._token_candidate_finder.find(current_token)
        self.token_candidates = [info.name for info in candidate_info_list]
