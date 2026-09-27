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

"""Test of plotting of gamma functions."""

from .plotting_util import plot_function


class TestGamma:
    """Test of plotting of gamma functions."""

    def test_plot_gamma(self, image_approver) -> None:
        """Test of plotting gamma(x)."""
        image = plot_function(["gamma(x)"], (-3.0, 5.0), (-10.0, 25.0))
        image_approver.verify(image)

    def test_plot_gamma_on_imag(self, image_approver) -> None:
        """Test of plotting abs(gamma(i * x))."""
        image = plot_function(["abs(gamma(i * x))"], (-3.0, 3.0), (-1.0, 5.0))
        image_approver.verify(image)

    def test_plot_lgamma(self, image_approver) -> None:
        """Test of plotting lgamma(x)."""
        image = plot_function(["lgamma(x)"], (-3.0, 5.0), (-1.0, 4.0))
        image_approver.verify(image)

    def test_plot_digamma(self, image_approver) -> None:
        """Test of plotting digamma(x)."""
        image = plot_function(["digamma(x)"], (-3.0, 5.0), (-5.0, 5.0))
        image_approver.verify(image)

    def test_plot_trigamma(self, image_approver) -> None:
        """Test of plotting trigamma(x)."""
        image = plot_function(["trigamma(x)"], (-3.0, 5.0), (-1.0, 20.0))
        image_approver.verify(image)

    def test_plot_polygamma(self, image_approver) -> None:
        """Test of plotting polygamma(n, x)."""
        image = plot_function(
            [
                "polygamma(0, x)",
                "polygamma(1, x)",
                "polygamma(2, x)",
                "polygamma(3, x)",
            ],
            (-3.0, 5.0),
            (-20.0, 20.0),
        )
        image_approver.verify(image)

    def test_plot_igamma(self, image_approver) -> None:
        """Test of plotting igamma(a, x)."""
        image = plot_function(
            ["igamma(0.5, x)", "igamma(1, x)", "igamma(3, x)"],
            (-1.0, 8.0),
            (-0.5, 1.5),
        )
        image_approver.verify(image)

    def test_plot_igammac(self, image_approver) -> None:
        """Test of plotting igammac(a, x)."""
        image = plot_function(
            ["igammac(0.5, x)", "igammac(1, x)", "igammac(3, x)"],
            (-1.0, 8.0),
            (-0.5, 1.5),
        )
        image_approver.verify(image)

    def test_plot_igamma_inv(self, image_approver) -> None:
        """Test of plotting igamma_inv(a, p)."""
        image = plot_function(
            ["igamma_inv(0.5, x)", "igamma_inv(1, x)", "igamma_inv(3, x)"],
            (-0.5, 1.5),
            (-1.0, 8.0),
        )
        image_approver.verify(image)

    def test_plot_igammac_inv(self, image_approver) -> None:
        """Test of plotting igammac_inv(a, q)."""
        image = plot_function(
            ["igammac_inv(0.5, x)", "igammac_inv(1, x)", "igammac_inv(3, x)"],
            (-0.5, 1.5),
            (-1.0, 8.0),
        )
        image_approver.verify(image)
