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

"""Test of sampling of Bessel functions."""

import numpy
import scipy.special

from .sampling_util import compare_vectors, sample_function


class TestBessel:
    """Test of sampling of Bessel functions."""

    def test_sample_bessel_j0(self) -> None:
        """Test of sampling bessel_j(0, x)."""
        x_values, y_values = sample_function(
            "bessel_j(0, x)", (-10.0, 10.0), (-1.0, 1.2)
        )
        compare_vectors(y_values, scipy.special.jv(0, x_values))

    def test_sample_bessel_j0p5(self) -> None:
        """Test of sampling bessel_j(0.5, x)."""
        x_values, y_values = sample_function(
            "bessel_j(0.5, x)", (0.0, 10.0), (-1.0, 1.2)
        )
        compare_vectors(y_values, scipy.special.jv(0.5, x_values))

    def test_sample_bessel_y0(self) -> None:
        """Test of sampling bessel_y(0, x)."""
        x_values, y_values = sample_function("bessel_y(0, x)", (0.1, 10.0), (-1.0, 1.2))
        compare_vectors(y_values, scipy.special.yv(0, x_values))

    def test_sample_bessel_y0p5(self) -> None:
        """Test of sampling bessel_y(0.5, x)."""
        x_values, y_values = sample_function(
            "bessel_y(0.5, x)", (0.1, 10.0), (-1.0, 1.2)
        )
        compare_vectors(y_values, scipy.special.yv(0.5, x_values))

    def test_sample_bessel_i0(self) -> None:
        """Test of sampling bessel_i(0, x)."""
        x_values, y_values = sample_function(
            "bessel_i(0, x)", (-10.0, 10.0), (-1.0, 1.2)
        )
        compare_vectors(y_values, scipy.special.iv(0, x_values))

    def test_sample_bessel_i0p5(self) -> None:
        """Test of sampling bessel_i(0.5, x)."""
        x_values, y_values = sample_function(
            "bessel_i(0.5, x)", (0.0, 10.0), (-1.0, 1.2)
        )
        compare_vectors(y_values, scipy.special.iv(0.5, x_values))

    def test_sample_bessel_k0(self) -> None:
        """Test of sampling bessel_k(0, x)."""
        x_values, y_values = sample_function("bessel_k(0, x)", (0.1, 10.0), (-1.0, 1.2))
        compare_vectors(y_values, scipy.special.kv(0, x_values))

    def test_sample_bessel_k0p5(self) -> None:
        """Test of sampling bessel_k(0.5, x)."""
        x_values, y_values = sample_function(
            "bessel_k(0.5, x)", (0.1, 10.0), (-1.0, 1.2)
        )
        compare_vectors(y_values, scipy.special.kv(0.5, x_values))

    def test_sample_hankel1_real(self) -> None:
        """Test of sampling real(hankel1(0, x))."""
        x_values, y_values = sample_function(
            "real(hankel1(0, x))", (0.1, 10.0), (-1.0, 1.2)
        )
        compare_vectors(y_values, numpy.real(scipy.special.hankel1(0, x_values)))

    def test_sample_hankel1_imag(self) -> None:
        """Test of sampling imag(hankel1(0, x))."""
        x_values, y_values = sample_function(
            "imag(hankel1(0, x))", (0.1, 10.0), (-1.0, 1.2)
        )
        compare_vectors(y_values, numpy.imag(scipy.special.hankel1(0, x_values)))

    def test_sample_hankel2_real(self) -> None:
        """Test of sampling real(hankel2(0, x))."""
        x_values, y_values = sample_function(
            "real(hankel2(0, x))", (0.1, 10.0), (-1.0, 1.2)
        )
        compare_vectors(y_values, numpy.real(scipy.special.hankel2(0, x_values)))

    def test_sample_hankel2_imag(self) -> None:
        """Test of sampling imag(hankel2(0, x))."""
        x_values, y_values = sample_function(
            "imag(hankel2(0, x))", (0.1, 10.0), (-1.0, 1.2)
        )
        compare_vectors(y_values, numpy.imag(scipy.special.hankel2(0, x_values)))

    def test_sample_spherical_bessel_j0(self) -> None:
        """Test of sampling spherical_bessel_j(0, x)."""
        x_values, y_values = sample_function(
            "spherical_bessel_j(0, x)", (0.1, 10.0), (-1.0, 1.2)
        )
        compare_vectors(y_values, scipy.special.spherical_jn(0, x_values))

    def test_sample_spherical_bessel_y0(self) -> None:
        """Test of sampling spherical_bessel_y(0, x)."""
        x_values, y_values = sample_function(
            "spherical_bessel_y(0, x)", (0.1, 10.0), (-1.0, 1.2)
        )
        compare_vectors(y_values, scipy.special.spherical_yn(0, x_values))

    def test_sample_spherical_hankel1_0_real(self) -> None:
        """Test of sampling real(spherical_hankel1(0, x))."""
        x_values, y_values = sample_function(
            "real(spherical_hankel1(0, x))", (0.1, 10.0), (-1.0, 1.2)
        )
        compare_vectors(y_values, scipy.special.spherical_jn(0, x_values))

    def test_sample_spherical_hankel1_0_imag(self) -> None:
        """Test of sampling imag(spherical_hankel1(0, x))."""
        x_values, y_values = sample_function(
            "imag(spherical_hankel1(0, x))", (0.1, 10.0), (-1.0, 1.2)
        )
        compare_vectors(y_values, scipy.special.spherical_yn(0, x_values))

    def test_sample_spherical_hankel2_0_real(self) -> None:
        """Test of sampling real(spherical_hankel2(0, x))."""
        x_values, y_values = sample_function(
            "real(spherical_hankel2(0, x))", (0.1, 10.0), (-1.0, 1.2)
        )
        compare_vectors(y_values, scipy.special.spherical_jn(0, x_values))

    def test_sample_spherical_hankel2_0_imag(self) -> None:
        """Test of sampling imag(spherical_hankel2(0, x))."""
        x_values, y_values = sample_function(
            "imag(spherical_hankel2(0, x))", (0.1, 10.0), (-1.0, 1.2)
        )
        compare_vectors(y_values, -scipy.special.spherical_yn(0, x_values))
