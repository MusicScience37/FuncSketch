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

import rapidfuzz

from func_sketch._cpp import MathFunctionInfo, MathFunctionList

RATE_OF_PARTIAL_MATCH = 0.6
RATE_OF_FULL_MATCH = 0.2
RATE_OF_MATCH_OF_BEGINNING = 0.2
SCORE_FOR_MATCH_OF_BEGINNING = 100.0 * RATE_OF_MATCH_OF_BEGINNING


def _custom_scorer(s1: str, s2: str, *, score_cutoff: float = 0.0) -> float:
    score = rapidfuzz.fuzz.partial_ratio(s1, s2) * RATE_OF_PARTIAL_MATCH
    score += rapidfuzz.fuzz.ratio(s1, s2) * RATE_OF_FULL_MATCH
    if s2.startswith(s1):
        score += SCORE_FOR_MATCH_OF_BEGINNING
    if score < score_cutoff:
        return 0.0
    return score


class TokenCandidateFinder:
    """Class to find candidates of tokens in function expressions."""

    # TODO Include other token types.

    def __init__(
        self, math_function_list: MathFunctionList, score_threshold: float, limit: int
    ) -> None:
        """Constructor.

        Args:
            math_function_list (MathFunctionList): List of mathematical functions.
            score_threshold (float): Minimum score to consider a match.
            limit (int): Maximum number of search results.
        """
        self._math_function_dict = {
            info.name: info
            for info in sorted(
                math_function_list.create_function_info_list(),
                key=lambda info: info.name,
            )
        }
        self._score_threshold = score_threshold
        self._limit = limit

    def find(self, query: str) -> list[MathFunctionInfo]:
        """Find candidates of tokens matching the query string.

        Args:
            query (str): Query string.

        Returns:
            list[MathFunctionInfo]: List of candidates of tokens.
        """
        if not query:
            return []
        results = rapidfuzz.process.extract(
            query=query,
            choices=self._math_function_dict.keys(),
            # The custom scorer accepts narrower argument types
            # than rapidfuzz expects, for simplicity.
            scorer=_custom_scorer,  # type: ignore[arg-type]
            processor=str.lower,
            score_cutoff=self._score_threshold,
            limit=self._limit,
        )
        return [self._math_function_dict[result[0]] for result in results]
