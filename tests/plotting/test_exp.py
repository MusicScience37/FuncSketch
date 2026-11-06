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

"""Test of plotting of exponential functions."""

import math

from .plotting_util import plot_function


class TestExponential:
    """Test of plotting of exponential functions."""

    def test_plot_exp_functions(self, image_approver) -> None:
        """Test of plotting exponential functions."""
        image = plot_function(
            ["exp(x)", "exp2(x)", "expm1(x)"], (-3.0, 3.0), (-1.0, 5.0)
        )
        image_approver.verify(image)

    def test_plot_exp_ix(self, image_approver) -> None:
        """Test of plotting exp(i*x)."""
        image = plot_function(
            ["real(exp(i*x))", "imag(exp(i*x))"],
            (-2.0 * math.pi, 2.0 * math.pi),
            (-1.5, 1.5),
        )
        image_approver.verify(image)
