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

"""Test of sampling of error functions."""

import math

import numpy

from .sampling_util import compare_vectors, sample_function


class TestErf:
    """Test of sampling of error functions."""

    def test_sample_erf(self) -> None:
        """Test of sampling erf(x)."""
        x_values, y_values = sample_function("erf(x)", (-3.0, 3.0), (-1.5, 1.5))
        compare_vectors(y_values, numpy.array([math.erf(x) for x in x_values]))
