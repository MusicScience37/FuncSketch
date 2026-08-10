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

"""Test of sampling of miscellaneous floating-point operations."""

import numpy

from .sampling_util import compare_vectors, sample_function


class TestMiscFloatOperations:
    """Test of sampling of miscellaneous floating-point operations."""

    def test_sample_abs(self) -> None:
        """Test of sampling abs(x)."""
        x_values, y_values = sample_function("abs(x)", (-3.0, 3.0), (-1.0, 5.0))
        compare_vectors(y_values, numpy.abs(x_values))
