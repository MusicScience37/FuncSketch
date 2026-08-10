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
