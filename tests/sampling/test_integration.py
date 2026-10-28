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

"""Test of sampling of expressions with numerical integration."""

from .sampling_util import compare_vectors, sample_function


class TestIntegration:
    """Test of sampling of expressions with numerical integration."""

    def test_integrate_s(self) -> None:
        """Test of integration of s."""
        x_values, y_values = sample_function(
            "integrate(s, 0, x)", (-2.0, 2.0), (-2.0, 2.0)
        )
        compare_vectors(y_values, x_values**2 / 2)

    # TODO More tests.
