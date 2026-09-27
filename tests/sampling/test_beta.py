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

"""Test of sampling of beta functions."""

import scipy.special

from .sampling_util import compare_vectors, sample_function


class TestBeta:
    """Test of sampling of beta functions."""

    def test_sample_beta_first_arg(self) -> None:
        """Test of sampling beta(x, 2.5)."""
        x_values, y_values = sample_function("beta(x, 2.5)", (0.1, 3.0), (-1.0, 5.0))
        compare_vectors(y_values, scipy.special.beta(x_values, 2.5))

    def test_sample_beta_second_arg(self) -> None:
        """Test of sampling beta(1.5, y)."""
        x_values, y_values = sample_function("beta(1.5, x)", (0.1, 3.0), (-1.0, 5.0))
        compare_vectors(y_values, scipy.special.beta(1.5, x_values))
