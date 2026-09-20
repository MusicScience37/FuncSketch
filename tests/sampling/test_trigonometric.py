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

"""Test of sampling of trigonometric functions."""

import numpy

from .sampling_util import compare_vectors, sample_function


class TestTrigonometric:
    """Test of sampling of trigonometric functions."""

    def test_sample_sin(self) -> None:
        """Test of sampling sin(x)."""
        x_values, y_values = sample_function(
            "sin(x)", (-2.0 * numpy.pi, 2.0 * numpy.pi), (-1.5, 1.5)
        )
        compare_vectors(y_values, numpy.sin(x_values))

    def test_sample_cos(self) -> None:
        """Test of sampling cos(x)."""
        x_values, y_values = sample_function(
            "cos(x)", (-2.0 * numpy.pi, 2.0 * numpy.pi), (-1.5, 1.5)
        )
        compare_vectors(y_values, numpy.cos(x_values))

    def test_sample_tan(self) -> None:
        """Test of sampling tan(x)."""
        x_values, y_values = sample_function("tan(x)", (-1.0, 1.0), (-2.0, 2.0))
        compare_vectors(y_values, numpy.tan(x_values))

    def test_sample_asin(self) -> None:
        """Test of sampling asin(x)."""
        x_values, y_values = sample_function("asin(x)", (-1.0, 1.0), (-2.0, 2.0))
        compare_vectors(y_values, numpy.arcsin(x_values))

    def test_sample_acos(self) -> None:
        """Test of sampling acos(x)."""
        x_values, y_values = sample_function("acos(x)", (-1.0, 1.0), (-0.5, 3.5))
        compare_vectors(y_values, numpy.arccos(x_values))

    def test_sample_atan(self) -> None:
        """Test of sampling atan(x)."""
        x_values, y_values = sample_function("atan(x)", (-5.0, 5.0), (-2.0, 2.0))
        compare_vectors(y_values, numpy.arctan(x_values))

    def test_sample_atan2_x_1(self) -> None:
        """Test of sampling atan2(x, 1)."""
        x_values, y_values = sample_function("atan2(x, 1)", (-5.0, 5.0), (-2.0, 2.0))
        compare_vectors(y_values, numpy.arctan2(x_values, 1))

    def test_sample_atan2_1_x(self) -> None:
        """Test of sampling atan2(1, x)."""
        x_values, y_values = sample_function("atan2(1, x)", (-5.0, 5.0), (-2.0, 2.0))
        compare_vectors(y_values, numpy.arctan2(1, x_values))
