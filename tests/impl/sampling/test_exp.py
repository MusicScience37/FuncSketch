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

"""Test of sampling of exponential functions."""

import numpy

from .sampling_util import compare_vectors, sample_function


class TestExponential:
    """Test of sampling of exponential functions."""

    def test_sample_exp(self) -> None:
        """Test of sampling exp(x)."""
        x_values, y_values = sample_function("exp(x)", (-3.0, 3.0), (-1.0, 5.0))
        compare_vectors(y_values, numpy.exp(x_values))

    def test_sample_exp_ix(self) -> None:
        """Test of sampling exp(i*x)."""
        x_values, y_values = sample_function("exp(i*x)", (-3.0, 3.0), (-2.0, 2.0))
        compare_vectors(y_values, numpy.cos(x_values))

    def test_sample_exp2(self) -> None:
        """Test of sampling exp2(x)."""
        x_values, y_values = sample_function("exp2(x)", (-3.0, 3.0), (-1.0, 5.0))
        compare_vectors(y_values, numpy.exp2(x_values))

    def test_sample_expm1(self) -> None:
        """Test of sampling expm1(x)."""
        x_values, y_values = sample_function("expm1(x)", (-3.0, 3.0), (-1.0, 5.0))
        compare_vectors(y_values, numpy.expm1(x_values))
