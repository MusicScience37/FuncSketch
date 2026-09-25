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

"""Class to find candidates of tokens in function expressions."""

import dataclasses

import rapidfuzz

from func_sketch._cpp import (
    ConstantInfo,
    ConstantList,
    MathFunctionInfo,
    MathFunctionList,
)

# These parameters were determined empirically based on tests in
# tests/impl/test_token_candidate_finder_manual.ipynb.
RATE_OF_PARTIAL_MATCH = 0.6
RATE_OF_FULL_MATCH = 0.2
RATE_OF_MATCH_OF_BEGINNING = 0.2
SCORE_FOR_MATCH_OF_BEGINNING = 100.0 * RATE_OF_MATCH_OF_BEGINNING
SCORE_THRESHOLD = 50.0


def _calculate_custom_score(
    query: str, candidate: str, *, score_cutoff: float = 0.0
) -> float:
    """Calculate a custom score.

    Args:
        query (str): Query string.
        candidate (str): Candidate string.
        score_cutoff (float, optional): Minimum score to consider a match. Defaults to 0.0.

    Returns:
        float: Calculated score.
    """
    score = 0.0
    if len(query) <= len(candidate):
        # Skip partial matching when the query is longer than the candidate.
        # This prevents, for example, the query `bei` from matching the candidate `e`.
        score += rapidfuzz.fuzz.partial_ratio(query, candidate) * RATE_OF_PARTIAL_MATCH
    score += rapidfuzz.fuzz.ratio(query, candidate) * RATE_OF_FULL_MATCH
    if candidate.startswith(query):
        score += SCORE_FOR_MATCH_OF_BEGINNING
    if score < score_cutoff:
        return 0.0
    return score


@dataclasses.dataclass(frozen=True)
class ParameterInfo:
    """Class to store information about a parameter."""

    name: str
    """Name of the parameter."""


class TokenCandidateFinder:
    """Class to find candidates of tokens in function expressions."""

    def __init__(
        self,
        math_function_list: MathFunctionList,
        constant_list: ConstantList,
        parameter_names: list[str],
        limit: int,
    ) -> None:
        """Constructor.

        Args:
            math_function_list (MathFunctionList): List of mathematical functions.
            constant_list (ConstantList): List of constants.
            parameter_names (list[str]): List of parameter names.
            limit (int): Maximum number of search results.
        """
        token_list = (
            math_function_list.create_function_info_list()
            + constant_list.create_constant_info_list()
            + [ParameterInfo(name=name) for name in parameter_names]
        )
        token_list.sort(key=lambda info: info.name)
        if len(token_list) != len({info.name for info in token_list}):
            raise ValueError("Duplicate token names are not allowed.")
        self._token_dict: dict[str, MathFunctionInfo | ConstantInfo | ParameterInfo] = {
            info.name: info for info in token_list
        }
        self._limit = limit

    def find(self, query: str) -> list[MathFunctionInfo | ConstantInfo | ParameterInfo]:
        """Find candidates of tokens matching the query string.

        Args:
            query (str): Query string.

        Returns:
            list[MathFunctionInfo | ConstantInfo | ParameterInfo]: List of candidates of tokens.
        """
        if not query:
            return []
        results = rapidfuzz.process.extract(
            query=query,
            choices=self._token_dict.keys(),
            # The custom scorer accepts narrower argument types
            # than rapidfuzz expects, for simplicity.
            scorer=_calculate_custom_score,  # type: ignore[arg-type]
            processor=str.lower,
            score_cutoff=SCORE_THRESHOLD,
            limit=self._limit,
        )
        return [self._token_dict[result[0]] for result in results]
