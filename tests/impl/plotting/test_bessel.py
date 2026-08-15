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

"""Test of plotting of Bessel functions."""

from .plotting_util import plot_function


class TestBessel:
    """Test of plotting of Bessel functions."""

    def test_plot_bessel_j(self, image_approver) -> None:
        """Test of plotting bessel_j(n, x)."""
        image = plot_function(
            ["bessel_j(0, x)", "bessel_j(1, x)", "bessel_j(2, x)"],
            (-10.0, 10.0),
            (-1.0, 1.2),
        )
        image_approver.verify(image)

    def test_plot_bessel_j_float_order(self, image_approver) -> None:
        """Test of plotting bessel_j(n, x) with float orders."""
        image = plot_function(
            ["bessel_j(0.5, x)", "bessel_j(1.5, x)", "bessel_j(2.5, x)"],
            (-1.0, 10.0),
            (-1.0, 1.2),
        )
        image_approver.verify(image)

    def test_plot_bessel_y(self, image_approver) -> None:
        """Test of plotting bessel_y(n, x)."""
        image = plot_function(
            ["bessel_y(0, x)", "bessel_y(1, x)", "bessel_y(2, x)"],
            (-1.0, 10.0),
            (-3.0, 1.0),
        )
        image_approver.verify(image)

    def test_plot_bessel_y_float_order(self, image_approver) -> None:
        """Test of plotting bessel_y(n, x) with float orders."""
        image = plot_function(
            ["bessel_y(0.5, x)", "bessel_y(1.5, x)", "bessel_y(2.5, x)"],
            (-1.0, 10.0),
            (-3.0, 1.0),
        )
        image_approver.verify(image)

    def test_plot_bessel_i(self, image_approver) -> None:
        """Test of plotting bessel_i(n, x)."""
        image = plot_function(
            ["bessel_i(0, x)", "bessel_i(1, x)", "bessel_i(2, x)"],
            (-1.0, 4.0),
            (-1.0, 4.0),
        )
        image_approver.verify(image)

    def test_plot_bessel_i_float_order(self, image_approver) -> None:
        """Test of plotting bessel_i(n, x) with float orders."""
        image = plot_function(
            ["bessel_i(0.5, x)", "bessel_i(1.5, x)", "bessel_i(2.5, x)"],
            (-1.0, 4.0),
            (-1.0, 4.0),
        )
        image_approver.verify(image)

    def test_plot_bessel_k(self, image_approver) -> None:
        """Test of plotting bessel_k(n, x)."""
        image = plot_function(
            ["bessel_k(0, x)", "bessel_k(1, x)", "bessel_k(2, x)"],
            (-1.0, 4.0),
            (-1.0, 4.0),
        )
        image_approver.verify(image)

    def test_plot_bessel_k_float_order(self, image_approver) -> None:
        """Test of plotting bessel_k(n, x) with float orders."""
        image = plot_function(
            ["bessel_k(0.5, x)", "bessel_k(1.5, x)", "bessel_k(2.5, x)"],
            (-1.0, 4.0),
            (-1.0, 4.0),
        )
        image_approver.verify(image)

    def test_plot_hankel1(self, image_approver) -> None:
        """Test of plotting real and imaginary parts of hankel1(n, x)."""
        image = plot_function(
            ["real(hankel1(0, x))", "imag(hankel1(0, x))"],
            (0.0, 10.0),
            (-3.0, 3.0),
        )
        image_approver.verify(image)

    def test_plot_hankel2(self, image_approver) -> None:
        """Test of plotting real and imaginary parts of hankel2(n, x)."""
        image = plot_function(
            ["real(hankel2(0, x))", "imag(hankel2(0, x))"],
            (0.0, 10.0),
            (-3.0, 3.0),
        )
        image_approver.verify(image)
