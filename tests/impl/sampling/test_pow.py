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

"""Test of sampling of power functions."""

import numpy

from .sampling_util import compare_vectors, sample_function


class TestPower:
    """Test of sampling of power functions."""

    def test_sample_pow_x_3(self) -> None:
        """Test of sampling pow(x, 3)."""
        x_values, y_values = sample_function("pow(x, 3)", (-3.0, 3.0), (-1.0, 5.0))
        compare_vectors(y_values, numpy.power(x_values, 3))

    def test_sample_pow_2_x(self) -> None:
        """Test of sampling pow(2, x)."""
        x_values, y_values = sample_function("pow(2, x)", (-3.0, 3.0), (-1.0, 5.0))
        compare_vectors(y_values, numpy.power(2, x_values))
