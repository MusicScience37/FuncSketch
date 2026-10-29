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

"""Test of sampling of expressions with numerical integration."""

import numpy

from .sampling_util import compare_vectors, sample_function

RTOL = 1e-4
ATOL = 1e-4


class TestIntegration:
    """Test of sampling of expressions with numerical integration."""

    def test_integrate_s(self) -> None:
        """Test of integration of s."""
        x_values, y_values = sample_function(
            "integrate(s, 0, x)", (-2.0, 2.0), (-2.0, 2.0)
        )
        compare_vectors(y_values, x_values**2 / 2)

    def test_integrate_cos(self) -> None:
        """Test of integration of cos(s)."""
        x_values, y_values = sample_function(
            "integrate(cos(s), 0, x)", (-5.0, 5.0), (-2.0, 2.0)
        )
        compare_vectors(y_values, numpy.sin(x_values), rtol=RTOL, atol=ATOL)

    def test_integrate_exp(self) -> None:
        """Test of integration of exp(s)."""
        x_values, y_values = sample_function(
            "integrate(exp(s), 0, x)", (-2.0, 2.0), (-1.0, 7.0)
        )
        compare_vectors(y_values, numpy.exp(x_values) - 1, rtol=RTOL, atol=ATOL)

    def test_integrate_constant(self) -> None:
        """Test of integration of a constant."""
        x_values, y_values = sample_function(
            "integrate(1, 0, x)", (-2.0, 2.0), (-2.0, 2.0)
        )
        compare_vectors(y_values, x_values)

    def test_integrate_with_variable_left(self) -> None:
        """Test of integration with a variable left endpoint."""
        x_values, y_values = sample_function(
            "integrate(s, x, 1)", (-2.0, 2.0), (-2.0, 2.0)
        )
        compare_vectors(y_values, (1 - x_values**2) / 2)

    def test_integrate_with_x_in_integrand(self) -> None:
        """Test of integration of x * s."""
        x_values, y_values = sample_function(
            "integrate(x * s, 0, x)", (-2.0, 2.0), (-4.0, 4.0)
        )
        compare_vectors(y_values, x_values**3 / 2)

    def test_integrate_complex_real(self) -> None:
        """Test of the real part of integration of exp(1i * s)."""
        x_values, y_values = sample_function(
            "real(integrate(exp(1i * s), 0, x))", (-5.0, 5.0), (-2.0, 2.0)
        )
        compare_vectors(y_values, numpy.sin(x_values), rtol=RTOL, atol=ATOL)

    def test_integrate_complex_imag(self) -> None:
        """Test of the imaginary part of integration of exp(1i * s)."""
        x_values, y_values = sample_function(
            "imag(integrate(exp(1i * s), 0, x))", (-5.0, 5.0), (-1.0, 3.0)
        )
        compare_vectors(y_values, 1 - numpy.cos(x_values), rtol=RTOL, atol=ATOL)
