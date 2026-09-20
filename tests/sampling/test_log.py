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

"""Test of sampling of logarithmic functions."""

import numpy

from .sampling_util import compare_vectors, sample_function


class TestLogarithm:
    """Test of sampling of logarithmic functions."""

    def test_sample_log(self) -> None:
        """Test of sampling log(x)."""
        x_values, y_values = sample_function("log(x)", (0.1, 10.0), (-3.0, 3.0))
        compare_vectors(y_values, numpy.log(x_values))

    def test_sample_log1p(self) -> None:
        """Test of sampling log1p(x)."""
        x_values, y_values = sample_function("log1p(x)", (0.1, 10.0), (-3.0, 3.0))
        compare_vectors(y_values, numpy.log1p(x_values))

    def test_sample_log10(self) -> None:
        """Test of sampling log10(x)."""
        x_values, y_values = sample_function("log10(x)", (0.1, 10.0), (-3.0, 3.0))
        compare_vectors(y_values, numpy.log10(x_values))

    def test_sample_log2(self) -> None:
        """Test of sampling log2(x)."""
        x_values, y_values = sample_function("log2(x)", (0.1, 10.0), (-3.0, 3.0))
        compare_vectors(y_values, numpy.log2(x_values))
