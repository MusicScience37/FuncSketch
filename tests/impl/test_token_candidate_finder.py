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

"""Tests of TokenCandidateFinder."""

import pytest

from func_sketch._cpp import ExpressionParser
from func_sketch._impl.token_candidate_finder import TokenCandidateFinder


def _create_finder(limit: int = 10) -> TokenCandidateFinder:
    """Create a TokenCandidateFinder for testing.

    Args:
        limit (int, optional): Maximum number of search results. Defaults to 10.

    Returns:
        TokenCandidateFinder: Created TokenCandidateFinder instance.
    """
    parser = ExpressionParser()
    math_function_list = parser.math_function_list()
    constant_list = parser.constant_list()
    parameter_names = ["x"]
    finder = TokenCandidateFinder(
        math_function_list=math_function_list,
        constant_list=constant_list,
        parameter_names=parameter_names,
        limit=limit,
    )
    return finder


def _find_names(finder: TokenCandidateFinder, query: str) -> list[str]:
    """Find names of token candidates for the given query.

    Args:
        finder (TokenCandidateFinder): Finder instance.
        query (str): Query string.

    Returns:
        list[str]: List of names of token candidates.
    """
    return [candidate.name for candidate in finder.find(query=query)]


class TestTokenCandidateFinder:
    """Tests of TokenCandidateFinder."""

    def test_empty_query(self) -> None:
        """Test with an empty query string."""
        finder = _create_finder()

        result = finder.find(query="")

        assert result == []

    @pytest.mark.parametrize(
        ("query", "expected"),
        [
            # Full match.
            ("e", "e"),
            ("exp", "exp"),
            ("x", "x"),
            # Case-insensitive match.
            ("EXP", "exp"),
            # Partial match including the query string as a substring.
            ("bei", "kelvin_bei"),
            # Partial match with ordering.
            ("bes", "bessel_i"),
        ],
    )
    def test_first_candidate(self, query: str, expected: str) -> None:
        """Test that the first candidate is selected as expected."""
        finder = _create_finder()

        result = _find_names(finder=finder, query=query)

        assert result
        assert result[0] == expected

    def test_limit(self) -> None:
        """Test that the number of candidates is limited."""
        limit = 2
        finder = _create_finder(limit=limit)

        result = finder.find(query="b")

        assert len(result) == limit

    def test_duplicate_names(self) -> None:
        """Test that duplicate token names are rejected."""
        parser = ExpressionParser()

        with pytest.raises(ValueError, match="Duplicate token names"):
            TokenCandidateFinder(
                math_function_list=parser.math_function_list(),
                constant_list=parser.constant_list(),
                parameter_names=["e"],
                limit=10,
            )
