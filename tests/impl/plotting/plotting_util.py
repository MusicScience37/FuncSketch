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

"""Utility for testing plotting."""

import numpy

from func_sketch._cpp import (
    PlotRange,
)
from func_sketch._gui.constants import CURVE_COLORS, DEFAULT_PLOT_CONFIG
from func_sketch._impl.curve_config import CurveConfig
from func_sketch._impl.curve_sampler import CurveSampler
from func_sketch._impl.plotter import Plotter


def plot_function(
    expression_str_list: list[str],
    x_range: tuple[float, float],
    y_range: tuple[float, float],
) -> numpy.ndarray:
    """Plot functions.

    Args:
        expression_str_list (list[str]): List of expressions of functions to plot.
        x_range (tuple[float, float]): Range of x-axis.
        y_range (tuple[float, float]): Range of y-axis.

    Returns:
        numpy.ndarray: Image of the plotted functions.
    """
    height = 600
    width = 800

    config = DEFAULT_PLOT_CONFIG
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
