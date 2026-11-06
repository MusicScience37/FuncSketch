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

"""Test of plotting of simple expressions like binary operators."""

import math

from .plotting_util import plot_function


class TestSimple:
    """Test of plotting of simple expressions like binary operators."""

    def test_plot_simple1(self, image_approver) -> None:
        """Test of plotting simple expressions."""
        image = plot_function(["x", "-x", "x + 1", "x - 1"], (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_simple2(self, image_approver) -> None:
        """Test of plotting simple expressions."""
        image = plot_function(
            ["x * 2", "x * x", "x / 2", "1 / x"], (-3.0, 3.0), (-3.0, 3.0)
        )
        image_approver.verify(image)

    def test_plot_simple3(self, image_approver) -> None:
        """Test of plotting simple expressions."""
        image = plot_function(
            ["x ** 2", "2 ** x", "x ** x", "-x * 2"], (-3.0, 3.0), (-3.0, 3.0)
        )
        image_approver.verify(image)

    def test_plot_e_pow_1ix(self, image_approver) -> None:
        """Test of plotting e ** (1i * x)."""
        image = plot_function(
            ["real(e ** (1i * x))", "imag(e ** (1i * x))"],
            (-2.0 * math.pi, 2.0 * math.pi),
            (-1.5, 1.5),
        )
        image_approver.verify(image)
