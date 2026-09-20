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

    def test_plot_x(self, image_approver) -> None:
        """Test of plotting x."""
        image = plot_function(["x"], (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_negation(self, image_approver) -> None:
        """Test of plotting -x."""
        image = plot_function(["-x"], (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_x_plus_1(self, image_approver) -> None:
        """Test of plotting x + 1."""
        image = plot_function(["x + 1"], (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_x_minus_1(self, image_approver) -> None:
        """Test of plotting x - 1."""
        image = plot_function(["x - 1"], (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_x_times_2(self, image_approver) -> None:
        """Test of plotting x * 2."""
        image = plot_function(["x * 2"], (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_x_times_x(self, image_approver) -> None:
        """Test of plotting x * x."""
        image = plot_function(["x * x"], (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_x_div_2(self, image_approver) -> None:
        """Test of plotting x / 2."""
        image = plot_function(["x / 2"], (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_1_div_x(self, image_approver) -> None:
        """Test of plotting 1 / x."""
        image = plot_function(["1 / x"], (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_x_pow_2(self, image_approver) -> None:
        """Test of plotting x ** 2."""
        image = plot_function(["x ** 2"], (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_2_pow_x(self, image_approver) -> None:
        """Test of plotting 2 ** x."""
        image = plot_function(["2 ** x"], (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_x_pow_x(self, image_approver) -> None:
        """Test of plotting x ** x."""
        image = plot_function(["x ** x"], (-1.0, 5.0), (-1.0, 5.0))
        image_approver.verify(image)

    def test_plot_minus_x_times_2(self, image_approver) -> None:
        """Test of plotting -x * 2."""
        image = plot_function(["-x * 2"], (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_e_pow_1ix(self, image_approver) -> None:
        """Test of plotting e ** (1i * x)."""
        image = plot_function(
            ["e ** (1i * x)"], (-2.0 * math.pi, 2.0 * math.pi), (-1.5, 1.5)
        )
        image_approver.verify(image)
