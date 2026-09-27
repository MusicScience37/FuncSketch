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
import scipy.special

from .sampling_util import compare_vectors, sample_function


class TestGamma:
    """Test of sampling of gamma functions."""

    def test_sample_gamma(self) -> None:
        """Test of sampling gamma(x)."""
        x_values, y_values = sample_function("gamma(x)", (0.2, 5.0), (-2.0, 25.0))
        compare_vectors(y_values, numpy.array([math.gamma(x) for x in x_values]))

    def test_sample_gamma_on_imag(self) -> None:
        """Test of sampling abs(gamma(i * x))."""
        x_values, y_values = sample_function(
            "abs(gamma(i * x))", (0.1, 3.0), (-1.0, 5.0)
        )
        compare_vectors(
            y_values,
            numpy.sqrt(numpy.pi / (x_values * numpy.sinh(numpy.pi * x_values))),
        )

    def test_sample_lgamma(self) -> None:
        """Test of sampling lgamma(x)."""
        x_values, y_values = sample_function("lgamma(x)", (0.1, 5.0), (-1.0, 4.0))
        compare_vectors(y_values, numpy.array([math.lgamma(x) for x in x_values]))

    def test_sample_digamma(self) -> None:
        """Test of sampling digamma(x)."""
        x_values, y_values = sample_function("digamma(x)", (0.1, 5.0), (-5.0, 5.0))
        compare_vectors(y_values, scipy.special.digamma(x_values))

    def test_sample_trigamma(self) -> None:
        """Test of sampling trigamma(x)."""
        x_values, y_values = sample_function("trigamma(x)", (0.1, 5.0), (-1.0, 20.0))
        compare_vectors(y_values, scipy.special.polygamma(1, x_values))

    def test_sample_polygamma0(self) -> None:
        """Test of sampling polygamma(0, x)."""
        x_values, y_values = sample_function(
            "polygamma(0, x)", (0.1, 5.0), (-20.0, 20.0)
        )
        compare_vectors(y_values, scipy.special.digamma(x_values))

    def test_sample_polygamma(self) -> None:
        """Test of sampling polygamma(2, x)."""
        x_values, y_values = sample_function(
            "polygamma(2, x)", (0.1, 5.0), (-20.0, 20.0)
        )
        compare_vectors(y_values, scipy.special.polygamma(2, x_values))

    def test_sample_igamma_first_arg(self) -> None:
        """Test of sampling igamma(x, 2.0)."""
        x_values, y_values = sample_function("igamma(x, 2.0)", (0.1, 5.0), (-0.5, 1.5))
        compare_vectors(y_values, scipy.special.gammainc(x_values, 2.0))

    def test_sample_igamma_second_arg(self) -> None:
        """Test of sampling igamma(1.5, x)."""
        x_values, y_values = sample_function("igamma(1.5, x)", (0.0, 8.0), (-0.5, 1.5))
        compare_vectors(y_values, scipy.special.gammainc(1.5, x_values))

    def test_sample_igammac_first_arg(self) -> None:
        """Test of sampling igammac(x, 2.0)."""
        x_values, y_values = sample_function("igammac(x, 2.0)", (0.1, 5.0), (-0.5, 1.5))
        compare_vectors(y_values, scipy.special.gammaincc(x_values, 2.0))

    def test_sample_igammac_second_arg(self) -> None:
        """Test of sampling igammac(1.5, x)."""
        x_values, y_values = sample_function("igammac(1.5, x)", (0.0, 8.0), (-0.5, 1.5))
        compare_vectors(y_values, scipy.special.gammaincc(1.5, x_values))
