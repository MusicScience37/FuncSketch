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

"""Test of plotting."""

import numpy

from func_sketch._cpp import (
    PlotConfig,
    PlotRange,
)
from func_sketch._gui.constants import CURVE_COLORS
from func_sketch._impl.curve_config import CurveConfig
from func_sketch._impl.curve_sampler import CurveSampler
from func_sketch._impl.plotter import Plotter


def _plot_function(
    expression_str_list: list[str],
    x_range: tuple[float, float],
    y_range: tuple[float, float],
) -> numpy.ndarray:
    height = 600
    width = 800

    config = PlotConfig()
    range = PlotRange(x_range, y_range)
    sampler = CurveSampler(range, config)
    plotter = Plotter(range, config)

    sampled_curves = []
    for i, expression_str in enumerate(expression_str_list):
        curve_config = CurveConfig(expression_str, CURVE_COLORS[i % len(CURVE_COLORS)])
        sampled_curve = sampler(curve_config)
        sampled_curves.append(sampled_curve)

    image = numpy.ndarray((height, width, 3), dtype=numpy.uint8)
    plotter(sampled_curves, image)

    return image


class TestPlotting:
    """Test of plotting."""

    def test_plot_x(self, image_approver) -> None:
        """Test of plotting x."""
        image = _plot_function(["x"], (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_minus_x_times_2(self, image_approver) -> None:
        """Test of plotting -x * 2."""
        image = _plot_function(["-x * 2"], (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_exp(self, image_approver) -> None:
        """Test of plotting exp(x)."""
        image = _plot_function(["exp(x)"], (-3.0, 3.0), (-1.0, 5.0))
        image_approver.verify(image)

    def test_plot_multi(self, image_approver) -> None:
        """Test of plotting multiple curves."""
        image = _plot_function(["x * x", "-x"], (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)
