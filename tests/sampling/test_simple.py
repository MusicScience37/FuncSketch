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

"""Test of sampling of simple expressions like binary operators."""

import numpy

from .sampling_util import compare_vectors, sample_function


class TestSimple:
    """Test of sampling of simple expressions like binary operators."""

    def test_sample_x(self) -> None:
        """Test of sampling x."""
        x_values, y_values = sample_function("x", (-3.0, 3.0), (-3.0, 3.0))
        compare_vectors(y_values, x_values)

    def test_negation(self) -> None:
        """Test of sampling -x."""
        x_values, y_values = sample_function("-x", (-3.0, 3.0), (-3.0, 3.0))
        compare_vectors(y_values, -x_values)

    def test_sample_x_plus_1(self) -> None:
        """Test of sampling x + 1."""
        x_values, y_values = sample_function("x + 1", (-3.0, 3.0), (-3.0, 3.0))
        compare_vectors(y_values, x_values + 1)

    def test_sample_x_minus_1(self) -> None:
        """Test of sampling x - 1."""
        x_values, y_values = sample_function("x - 1", (-3.0, 3.0), (-3.0, 3.0))
        compare_vectors(y_values, x_values - 1)

    def test_sample_x_times_2(self) -> None:
        """Test of sampling x * 2."""
        x_values, y_values = sample_function("x * 2", (-3.0, 3.0), (-3.0, 3.0))
        compare_vectors(y_values, x_values * 2)

    def test_sample_x_times_x(self) -> None:
        """Test of sampling x * x."""
        x_values, y_values = sample_function("x * x", (-3.0, 3.0), (-3.0, 3.0))
        compare_vectors(y_values, x_values * x_values)

    def test_sample_x_div_2(self) -> None:
        """Test of sampling x / 2."""
        x_values, y_values = sample_function("x / 2", (-3.0, 3.0), (-3.0, 3.0))
        compare_vectors(y_values, x_values / 2)

    def test_sample_1_div_x(self) -> None:
        """Test of sampling 1 / x."""
        x_values, y_values = sample_function("1 / x", (-3.0, 3.0), (-3.0, 3.0))
        compare_vectors(y_values, 1 / x_values)

    def test_sample_x_pow_2(self) -> None:
        """Test of sampling x ** 2."""
        x_values, y_values = sample_function("x ** 2", (-3.0, 3.0), (-3.0, 3.0))
        compare_vectors(y_values, numpy.power(x_values, 2))

    def test_sample_2_pow_x(self) -> None:
        """Test of sampling 2 ** x."""
        x_values, y_values = sample_function("2 ** x", (-3.0, 3.0), (-3.0, 3.0))
        compare_vectors(y_values, numpy.power(2, x_values))

    def test_sample_x_pow_x(self) -> None:
        """Test of sampling x ** x."""
        x_values, y_values = sample_function("x ** x", (0.1, 5.0), (-1.0, 5.0))
        compare_vectors(y_values, numpy.power(x_values, x_values))

    def test_sample_x_pow_2_pow_3(self) -> None:
        """Test of sampling x ** 2 ** 3."""
        x_values, y_values = sample_function("x ** 2 ** 3", (0.1, 5.0), (-1.0, 5.0))
        compare_vectors(y_values, numpy.power(x_values, numpy.power(2, 3)))

    def test_sample_minus_x_times_2(self) -> None:
        """Test of sampling -x * 2."""
        x_values, y_values = sample_function("-x * 2", (-3.0, 3.0), (-3.0, 3.0))
        compare_vectors(y_values, -x_values * 2)
