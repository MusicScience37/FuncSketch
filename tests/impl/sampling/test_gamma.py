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

"""Test of sampling of gamma functions."""

import math

import numpy

from .sampling_util import compare_vectors, sample_function


class TestGamma:
    """Test of sampling of gamma functions."""

    def test_sample_gamma(self) -> None:
        """Test of sampling gamma(x)."""
        x_values, y_values = sample_function("gamma(x)", (0.2, 5.0), (-2.0, 25.0))
        compare_vectors(y_values, numpy.array([math.gamma(x) for x in x_values]))

    def test_sample_lgamma(self) -> None:
        """Test of sampling lgamma(x)."""
        x_values, y_values = sample_function("lgamma(x)", (0.1, 5.0), (-1.0, 4.0))
        compare_vectors(y_values, numpy.array([math.lgamma(x) for x in x_values]))
