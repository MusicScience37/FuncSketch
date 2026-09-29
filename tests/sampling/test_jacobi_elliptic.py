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

"""Test of sampling of Jacobi elliptic functions."""

import mpmath
import numpy

from .sampling_util import compare_vectors, sample_function


@numpy.vectorize
def _jacobi_sn(u: float, k: float) -> float:
    """Calculate the Jacobi elliptic function sn.

    Args:
        u (float): Argument.
        k (float): Modulus.

    Returns:
        float: Value of the Jacobi elliptic function sn.
    """
    return float(mpmath.re(mpmath.ellipfun("sn", u, m=k**2)))


class TestJacobiElliptic:
    """Test of sampling of Jacobi elliptic functions."""

    def test_sample_jacobi_sn_first_arg(self) -> None:
        """Test of sampling jacobi_sn(x, 0.8)."""
        x_values, y_values = sample_function(
            "jacobi_sn(x, 0.8)", (-8.0, 8.0), (-1.5, 1.5)
        )
        compare_vectors(y_values, _jacobi_sn(x_values, 0.8))

    def test_sample_jacobi_sn_second_arg(self) -> None:
        """Test of sampling jacobi_sn(1.5, x)."""
        x_values, y_values = sample_function(
            "jacobi_sn(1.5, x)", (-3.0, 3.0), (-1.5, 1.5)
        )
        compare_vectors(y_values, _jacobi_sn(1.5, x_values))
