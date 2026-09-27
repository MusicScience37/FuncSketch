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

"""Test of plotting of beta functions."""

from .plotting_util import plot_function


class TestBeta:
    """Test of plotting of beta functions."""

    def test_plot_beta(self, image_approver) -> None:
        """Test of plotting beta(x, y)."""
        image = plot_function(
            ["beta(x, 0.5)", "beta(x, 1)", "beta(x, 2)"],
            (-1.0, 3.0),
            (-1.0, 5.0),
        )
        image_approver.verify(image)

    def test_plot_lbeta(self, image_approver) -> None:
        """Test of plotting lbeta(x, y)."""
        image = plot_function(
            ["lbeta(x, 0.5)", "lbeta(x, 1)", "lbeta(x, 2)"],
            (-3.0, 3.0),
            (-3.0, 5.0),
        )
        image_approver.verify(image)

    def test_plot_ibeta(self, image_approver) -> None:
        """Test of plotting ibeta(a, b, x)."""
        image = plot_function(
            ["ibeta(0.5, 0.5, x)", "ibeta(2, 2, x)", "ibeta(2, 5, x)"],
            (-0.5, 1.5),
            (-0.5, 1.5),
        )
        image_approver.verify(image)

    def test_plot_ibetac(self, image_approver) -> None:
        """Test of plotting ibetac(a, b, x)."""
        image = plot_function(
            ["ibetac(0.5, 0.5, x)", "ibetac(2, 2, x)", "ibetac(2, 5, x)"],
            (-0.5, 1.5),
            (-0.5, 1.5),
        )
        image_approver.verify(image)

    def test_plot_ibeta_inv(self, image_approver) -> None:
        """Test of plotting ibeta_inv(a, b, p)."""
        image = plot_function(
            ["ibeta_inv(0.5, 0.5, x)", "ibeta_inv(2, 2, x)", "ibeta_inv(2, 5, x)"],
            (-0.5, 1.5),
            (-0.5, 1.5),
        )
        image_approver.verify(image)
