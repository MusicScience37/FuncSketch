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

"""Test of plotting of Jacobi elliptic functions."""

from .plotting_util import plot_function


class TestJacobiElliptic:
    """Test of plotting of Jacobi elliptic functions."""

    def test_plot_jacobi_sn(self, image_approver) -> None:
        """Test of plotting jacobi_sn(u, k)."""
        image = plot_function(
            [
                "jacobi_sn(x, 0)",
                "jacobi_sn(x, 0.5)",
                "jacobi_sn(x, 0.9)",
                "jacobi_sn(x, 1)",
                "jacobi_sn(x, 2)",
            ],
            (-8.0, 8.0),
            (-1.5, 1.5),
        )
        image_approver.verify(image)

    def test_plot_jacobi_cn(self, image_approver) -> None:
        """Test of plotting jacobi_cn(u, k)."""
        image = plot_function(
            [
                "jacobi_cn(x, 0)",
                "jacobi_cn(x, 0.5)",
                "jacobi_cn(x, 0.9)",
                "jacobi_cn(x, 1)",
                "jacobi_cn(x, 2)",
            ],
            (-8.0, 8.0),
            (-1.5, 1.5),
        )
        image_approver.verify(image)
