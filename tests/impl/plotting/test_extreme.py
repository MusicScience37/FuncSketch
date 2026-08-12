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

"""Test of plotting for extreme cases."""

from .plotting_util import plot_function


class TestExtreme:
    """Test of plotting for extreme cases."""

    def test_plot_large_range(self, image_approver) -> None:
        """Test of plotting with a large range."""
        image = plot_function(["x"], (-1e6, 1e6), (-1e6, 1e6))
        image_approver.verify(image)

    def test_plot_small_range(self, image_approver) -> None:
        """Test of plotting with a small range."""
        image = plot_function(["x"], (-1e-6, 1e-6), (-1e-6, 1e-6))
        image_approver.verify(image)

    def test_plot_x_pow_100(self, image_approver) -> None:
        """Test of plotting with x^100."""
        image = plot_function(["x**100"], (-2.0, 2.0), (-1.0, 10.0))
        image_approver.verify(image)

    def test_plot_tan_10x(self, image_approver) -> None:
        """Test of plotting with tan(10x)."""
        image = plot_function(["tan(10*x)"], (-1.0, 1.0), (-10.0, 10.0))
        image_approver.verify(image)

    def test_plot_exp_in_large_range(self, image_approver) -> None:
        """Test of plotting with exp(x) in a large range."""
        image = plot_function(["exp(x)"], (-1e6, 1e6), (-1e6, 1e6))
        image_approver.verify(image)
