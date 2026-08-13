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

"""Test of plotting combined expressions."""

from .plotting_util import plot_function


class TestCombined:
    """Test of plotting combined expressions."""

    def test_plot_two_curves(self, image_approver) -> None:
        """Test of plotting two curves."""
        image = plot_function(["x * x", "-x"], (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_five_curves(self, image_approver) -> None:
        """Test of plotting five curves."""
        image = plot_function(
            ["x", "-x", "exp(x)", "gamma(x)", "log10(x)"],
            (-3.0, 3.0),
            (-3.0, 3.0),
        )
        image_approver.verify(image)

    def test_plot_five_sine_curves(self, image_approver) -> None:
        """Test of plotting five sine curves."""
        image = plot_function(
            ["sin(x)", "sin(x-0.4)", "sin(x-0.8)", "sin(x-1.2)", "sin(x-1.6)"],
            (-2.0, 4.0),
            (-2.0, 2.0),
        )
        image_approver.verify(image)
