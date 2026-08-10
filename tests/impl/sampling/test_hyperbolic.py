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

"""Test of sampling of hyperbolic functions."""

import numpy

from .sampling_util import compare_vectors, sample_function


class TestHyperbolic:
    """Test of sampling of hyperbolic functions."""

    def test_sample_sinh(self) -> None:
        """Test of sampling sinh(x)."""
        x_values, y_values = sample_function("sinh(x)", (-2.0, 2.0), (-4.0, 4.0))
        compare_vectors(y_values, numpy.sinh(x_values))

    def test_sample_cosh(self) -> None:
        """Test of sampling cosh(x)."""
        x_values, y_values = sample_function("cosh(x)", (-2.0, 2.0), (-0.5, 4.5))
        compare_vectors(y_values, numpy.cosh(x_values))

    def test_sample_tanh(self) -> None:
        """Test of sampling tanh(x)."""
        x_values, y_values = sample_function("tanh(x)", (-3.0, 3.0), (-1.5, 1.5))
        compare_vectors(y_values, numpy.tanh(x_values))
