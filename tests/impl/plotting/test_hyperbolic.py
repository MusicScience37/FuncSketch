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

"""Test of plotting of hyperbolic functions."""

from .plotting_util import plot_function


class TestHyperbolic:
    """Test of plotting of hyperbolic functions."""

    def test_plot_sinh(self, image_approver) -> None:
        """Test of plotting sinh(x)."""
        image = plot_function(["sinh(x)"], (-2.0, 2.0), (-4.0, 4.0))
        image_approver.verify(image)
