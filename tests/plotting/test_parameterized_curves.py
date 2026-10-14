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

"""Tests of plotting of parameterized curves."""

import numpy

from .plotting_util import plot_parameterized_curves


class TestParameterizedCurves:
    """Tests of plotting of parameterized curves."""

    def test_line(self, image_approver) -> None:
        """Test of plotting a line."""
        image = plot_parameterized_curves(
            [("t", "2 * t")], (-1.2, 1.2), (-2.5, 2.5), (-1.0, 1.0)
        )
        image_approver.verify(image)

    def test_circle(self, image_approver) -> None:
        """Test of plotting a circle."""
        image = plot_parameterized_curves(
            [("cos(t)", "sin(t)")], (-1.2, 1.2), (-1.2, 1.2), (0.0, 2.0 * numpy.pi)
        )
        image_approver.verify(image)

    def test_lissajous_curve(self, image_approver) -> None:
        """Test of plotting a Lissajous curve."""
        image = plot_parameterized_curves(
            [("sin(3 * t)", "sin(4 * t)")],
            (-1.2, 1.2),
            (-1.2, 1.2),
            (0.0, 2.0 * numpy.pi),
        )
        image_approver.verify(image)

    def test_lissajous_curve_zoomed(self, image_approver) -> None:
        """Test of plotting a Lissajous curve zoomed."""
        image = plot_parameterized_curves(
            [("sin(3 * t)", "sin(4 * t)")],
            (-0.8, 0.8),
            (-0.8, 0.8),
            (0.0, 2.0 * numpy.pi),
        )
        image_approver.verify(image)

    def test_astroid(self, image_approver) -> None:
        """Test of plotting an astroid."""
        image = plot_parameterized_curves(
            [("cos(t)**3", "sin(t)**3")],
            (-1.2, 1.2),
            (-1.2, 1.2),
            (0.0, 2.0 * numpy.pi),
        )
        image_approver.verify(image)

    def test_logarithmic_spiral(self, image_approver) -> None:
        """Test of plotting a logarithmic spiral."""
        image = plot_parameterized_curves(
            [("exp(0.1 * t) * cos(t)", "exp(0.1 * t) * sin(t)")],
            (-3.0, 3.0),
            (-3.0, 3.0),
            (-20.0 * numpy.pi, 6.0 * numpy.pi),
        )
        image_approver.verify(image)

    def test_inverse(self, image_approver) -> None:
        """Test of plotting a curve (1/t, t)."""
        image = plot_parameterized_curves(
            [("1 / t", "t")],
            (-3.0, 3.0),
            (-3.0, 3.0),
            (-2.0, 2.0),
        )
        image_approver.verify(image)

    def test_sqrt(self, image_approver) -> None:
        """Test of plotting a curve (sqrt(t), t)."""
        image = plot_parameterized_curves(
            [("sqrt(t)", "t")],
            (-3.0, 3.0),
            (-3.0, 3.0),
            (-3.0, 3.0),
        )
        image_approver.verify(image)
