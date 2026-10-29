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

"""Test of plotting of expressions with numerical integration."""

from .plotting_util import plot_function


class TestIntegration:
    """Test of plotting of expressions with numerical integration."""

    def test_plot_integrate_s(self, image_approver) -> None:
        """Test of plotting integrate(s, 0, x)."""
        image = plot_function(["integrate(s, 0, x)"], (-2.0, 2.0), (-2.0, 2.0))
        image_approver.verify(image)

    def test_plot_integrate_cos(self, image_approver) -> None:
        """Test of plotting integrate(cos(s), 0, x)."""
        image = plot_function(["integrate(cos(s), 0, x)"], (-5.0, 5.0), (-2.0, 2.0))
        image_approver.verify(image)

    def test_plot_integrate_exp(self, image_approver) -> None:
        """Test of plotting integrate(exp(s), 0, x)."""
        image = plot_function(["integrate(exp(s), 0, x)"], (-2.0, 2.0), (-1.0, 7.0))
        image_approver.verify(image)

    def test_plot_integrate_constant(self, image_approver) -> None:
        """Test of plotting integrate(1, 0, x)."""
        image = plot_function(["integrate(1, 0, x)"], (-2.0, 2.0), (-2.0, 2.0))
        image_approver.verify(image)

    def test_plot_integrate_with_variable_left(self, image_approver) -> None:
        """Test of plotting integrate(s, x, 1)."""
        image = plot_function(["integrate(s, x, 1)"], (-2.0, 2.0), (-2.0, 2.0))
        image_approver.verify(image)

    def test_plot_integrate_with_x_in_integrand(self, image_approver) -> None:
        """Test of plotting integrate(x * s, 0, x)."""
        image = plot_function(["integrate(x * s, 0, x)"], (-2.0, 2.0), (-4.0, 4.0))
        image_approver.verify(image)

    def test_plot_integrate_complex(self, image_approver) -> None:
        """Test of plotting integration of exp(1i * s)."""
        image = plot_function(
            [
                "real(integrate(exp(1i * s), 0, x))",
                "imag(integrate(exp(1i * s), 0, x))",
            ],
            (-5.0, 5.0),
            (-2.0, 3.0),
        )
        image_approver.verify(image)
