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

"""Test of plotting of logarithmic functions."""

from .plotting_util import plot_function


class TestLogarithm:
    """Test of plotting of logarithmic functions."""

    def test_plot_log(self, image_approver) -> None:
        """Test of plotting log(x)."""
        image = plot_function(["log(x)"], (-2.0, 10.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_log1p(self, image_approver) -> None:
        """Test of plotting log1p(x)."""
        image = plot_function(["log1p(x)"], (-2.0, 10.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_log10(self, image_approver) -> None:
        """Test of plotting log10(x)."""
        image = plot_function(["log10(x)"], (-2.0, 10.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_log2(self, image_approver) -> None:
        """Test of plotting log2(x)."""
        image = plot_function(["log2(x)"], (-2.0, 10.0), (-3.0, 3.0))
        image_approver.verify(image)
