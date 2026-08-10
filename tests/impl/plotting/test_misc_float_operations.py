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

"""Test of plotting of miscellaneous floating-point operations."""

from .plotting_util import plot_function


class TestMiscFloatOperations:
    """Test of plotting of miscellaneous floating-point operations."""

    def test_plot_abs(self, image_approver) -> None:
        """Test of plotting abs(x)."""
        image = plot_function(["abs(x)"], (-3.0, 3.0), (-1.0, 5.0))
        image_approver.verify(image)

    def test_plot_ceil(self, image_approver) -> None:
        """Test of plotting ceil(x)."""
        image = plot_function(["ceil(x)"], (-3.0, 3.0), (-4.0, 4.0))
        image_approver.verify(image)

    def test_plot_floor(self, image_approver) -> None:
        """Test of plotting floor(x)."""
        image = plot_function(["floor(x)"], (-3.0, 3.0), (-4.0, 4.0))
        image_approver.verify(image)

    def test_plot_trunc(self, image_approver) -> None:
        """Test of plotting trunc(x)."""
        image = plot_function(["trunc(x)"], (-3.0, 3.0), (-4.0, 4.0))
        image_approver.verify(image)

    def test_plot_round(self, image_approver) -> None:
        """Test of plotting round(x)."""
        image = plot_function(["round(x)"], (-3.0, 3.0), (-4.0, 4.0))
        image_approver.verify(image)
