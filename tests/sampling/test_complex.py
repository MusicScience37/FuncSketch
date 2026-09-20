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

"""Test of sampling of functions for complex numbers."""

import numpy

from .sampling_util import compare_vectors, sample_function


class TestComplex:
    """Test of sampling of functions for complex numbers."""

    def test_sample_real(self) -> None:
        """Test of sampling real(x + 1i * x ** 2)."""
        x_values, y_values = sample_function(
            "real(x + 1i * x ** 2)", (-3.0, 3.0), (-1.0, 5.0)
        )
        compare_vectors(y_values, x_values)

    def test_sample_imag(self) -> None:
        """Test of sampling imag(x + 1i * x ** 2)."""
        x_values, y_values = sample_function(
            "imag(x + 1i * x ** 2)", (-3.0, 3.0), (-1.0, 5.0)
        )
        compare_vectors(y_values, x_values**2)

    def test_sample_arg(self) -> None:
        """Test of sampling arg(x + 1i * x ** 2)."""
        x_values, y_values = sample_function(
            "arg(x + 1i * x ** 2)", (-3.0, 3.0), (-1.0, 5.0)
        )
        compare_vectors(y_values, numpy.arctan2(x_values**2, x_values))

    def test_sample_conj(self) -> None:
        """Test of sampling imag(conj(x + 1i * x ** 2))."""
        x_values, y_values = sample_function(
            "imag(conj(x + 1i * x ** 2))", (-3.0, 3.0), (-1.0, 5.0)
        )
        compare_vectors(y_values, -(x_values**2))
