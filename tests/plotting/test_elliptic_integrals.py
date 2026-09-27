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

"""Test of plotting of elliptic integrals."""

from .plotting_util import plot_function


class TestEllipticIntegrals:
    """Test of plotting of elliptic integrals."""

    def test_plot_elliptic_f(self, image_approver) -> None:
        """Test of plotting elliptic_f(phi, k)."""
        image = plot_function(
            [
                "elliptic_f(0.5, x)",
                "elliptic_f(0.75, x)",
                "elliptic_f(1.25, x)",
                "elliptic_f(pi/2, x)",
                "elliptic_f(2, x)",
            ],
            (-3.0, 3.0),
            (0.0, 5.0),
        )
        image_approver.verify(image)

    def test_plot_comp_elliptic_k(self, image_approver) -> None:
        """Test of plotting comp_elliptic_k(k)."""
        image = plot_function(["comp_elliptic_k(x)"], (-1.5, 1.5), (0.0, 5.0))
        image_approver.verify(image)

    def test_plot_elliptic_e(self, image_approver) -> None:
        """Test of plotting elliptic_e(phi, k)."""
        image = plot_function(
            [
                "elliptic_e(0.5, x)",
                "elliptic_e(0.75, x)",
                "elliptic_e(1.25, x)",
                "elliptic_e(pi/2, x)",
                "elliptic_e(2, x)",
            ],
            (-3.0, 3.0),
            (0.0, 3.0),
        )
        image_approver.verify(image)

    def test_plot_comp_elliptic_e(self, image_approver) -> None:
        """Test of plotting comp_elliptic_e(k)."""
        image = plot_function(["comp_elliptic_e(x)"], (-1.5, 1.5), (0.0, 2.0))
        image_approver.verify(image)

    def test_plot_elliptic_pi(self, image_approver) -> None:
        """Test of plotting elliptic_pi(n, phi, k)."""
        image = plot_function(
            [
                "elliptic_pi(0, 1.25, x)",
                "elliptic_pi(0.5, 1.25, x)",
                "elliptic_pi(0.25, pi/2, x)",
                "elliptic_pi(0.75, pi/2, x)",
            ],
            (-1.5, 1.5),
            (0.0, 5.0),
        )
        image_approver.verify(image)

    def test_plot_comp_elliptic_pi(self, image_approver) -> None:
        """Test of plotting comp_elliptic_pi(n, k)."""
        image = plot_function(
            [
                "comp_elliptic_pi(-2, x)",
                "comp_elliptic_pi(0, x)",
                "comp_elliptic_pi(0.25, x)",
                "comp_elliptic_pi(0.75, x)",
            ],
            (-1.5, 1.5),
            (0.0, 5.0),
        )
        image_approver.verify(image)
