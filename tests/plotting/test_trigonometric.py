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

"""Test of plotting of trigonometric functions."""

import numpy

from .plotting_util import plot_function


class TestTrigonometric:
    """Test of plotting of trigonometric functions."""

    def test_plot_trigonometric(self, image_approver) -> None:
        """Test of plotting trigonometric functions."""
        image = plot_function(
            ["sin(x)", "cos(x)", "tan(x)"],
            (-2.0 * numpy.pi, 2.0 * numpy.pi),
            (-5.0, 5.0),
        )
        image_approver.verify(image)

    def test_plot_inverse_trigonometric(self, image_approver) -> None:
        """Test of plotting inverse trigonometric functions."""
        image = plot_function(
            ["asin(x)", "acos(x)", "atan(x)"],
            (-5.0, 5.0),
            (-2.0 * numpy.pi, 2.0 * numpy.pi),
        )
        image_approver.verify(image)

    def test_plot_atan2(self, image_approver) -> None:
        """Test of plotting atan2 function."""
        image = plot_function(["atan2(x, 1)", "atan2(1, x)"], (-5.0, 5.0), (-4.0, 4.0))
        image_approver.verify(image)
