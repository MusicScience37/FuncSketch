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

"""Test of sampling of elliptic integrals."""

import mpmath
import numpy
import scipy.special

from .sampling_util import compare_vectors, sample_function


@numpy.vectorize
def _elliptic_pi(n: float, phi: float, k: float) -> float:
    """Calculate the incomplete elliptic integral of the third kind.

    Args:
        n (float): Characteristic.
        phi (float): Amplitude.
        k (float): Modulus.

    Returns:
        float: Value of the elliptic integral.
    """
    return float(mpmath.ellippi(n, phi, k**2))


class TestEllipticIntegrals:
    """Test of sampling of elliptic integrals."""

    def test_sample_elliptic_f_first_arg(self) -> None:
        """Test of sampling elliptic_f(x, 0.8)."""
        x_values, y_values = sample_function(
            "elliptic_f(x, 0.8)", (-5.0, 5.0), (-5.0, 5.0)
        )
        compare_vectors(y_values, scipy.special.ellipkinc(x_values, 0.8**2))

    def test_sample_elliptic_f_second_arg(self) -> None:
        """Test of sampling elliptic_f(1.2, x)."""
        x_values, y_values = sample_function(
            "elliptic_f(1.2, x)", (-1.0, 1.0), (-5.0, 5.0)
        )
        compare_vectors(y_values, scipy.special.ellipkinc(1.2, x_values**2))

    def test_sample_comp_elliptic_k(self) -> None:
        """Test of sampling comp_elliptic_k(x)."""
        x_values, y_values = sample_function(
            "comp_elliptic_k(x)", (-1.0, 1.0), (-1.0, 5.0)
        )
        compare_vectors(y_values, scipy.special.ellipk(x_values**2))

    def test_sample_elliptic_e_first_arg(self) -> None:
        """Test of sampling elliptic_e(x, 0.8)."""
        x_values, y_values = sample_function(
            "elliptic_e(x, 0.8)", (-5.0, 5.0), (-5.0, 5.0)
        )
        compare_vectors(y_values, scipy.special.ellipeinc(x_values, 0.8**2))

    def test_sample_elliptic_e_second_arg(self) -> None:
        """Test of sampling elliptic_e(1.2, x)."""
        x_values, y_values = sample_function(
            "elliptic_e(1.2, x)", (-1.0, 1.0), (-5.0, 5.0)
        )
        compare_vectors(y_values, scipy.special.ellipeinc(1.2, x_values**2))

    def test_sample_comp_elliptic_e(self) -> None:
        """Test of sampling comp_elliptic_e(x)."""
        x_values, y_values = sample_function(
            "comp_elliptic_e(x)", (-1.0, 1.0), (-0.5, 2.0)
        )
        compare_vectors(y_values, scipy.special.ellipe(x_values**2))

    def test_sample_elliptic_pi_first_arg(self) -> None:
        """Test of sampling elliptic_pi(x, 0.8, 0.5)."""
        x_values, y_values = sample_function(
            "elliptic_pi(x, 0.8, 0.5)", (-3.0, 1.5), (-5.0, 5.0)
        )
        compare_vectors(y_values, _elliptic_pi(x_values, 0.8, 0.5))

    def test_sample_elliptic_pi_second_arg(self) -> None:
        """Test of sampling elliptic_pi(0.5, x, 0.5)."""
        x_values, y_values = sample_function(
            "elliptic_pi(0.5, x, 0.5)", (-5.0, 5.0), (-5.0, 5.0)
        )
        compare_vectors(y_values, _elliptic_pi(0.5, x_values, 0.5))

    def test_sample_elliptic_pi_third_arg(self) -> None:
        """Test of sampling elliptic_pi(0.5, 0.8, x)."""
        x_values, y_values = sample_function(
            "elliptic_pi(0.5, 0.8, x)", (-1.0, 1.0), (-5.0, 5.0)
        )
        compare_vectors(y_values, _elliptic_pi(0.5, 0.8, x_values))
