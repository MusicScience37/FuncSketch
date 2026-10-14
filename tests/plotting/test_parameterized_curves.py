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

from func_sketch._cpp import (
    CurveSampler,
    ParameterizedCurveSpec,
    PlotConfig,
    PlotRange,
    Plotter,
    SampledParameterizedCurve,
)
from func_sketch._gui.common.constants import CURVE_COLORS, DEFAULT_PLOT_CONFIG


def plot_parameterized_curve(
    expression_str_list: list[tuple[str, str]],
    x_range: tuple[float, float],
    y_range: tuple[float, float],
    parameter_range: tuple[float, float],
    *,
    config: PlotConfig | None = None,
) -> numpy.ndarray:
    """Plot a parameterized curve.

    Args:
        expression_str_list (list[tuple[str, str]]): List of tuples of the function expressions for the x and y coordinates.
        x_range (tuple[float, float]): Range of the x coordinate.
        y_range (tuple[float, float]): Range of the y coordinate.
        parameter_range (tuple[float, float]): Range of the parameter.
        config (PlotConfig | None): Plot configuration object. If None, the default configuration is used.

    Returns:
        numpy.ndarray: Image of the plotted parameterized curve.
    """
    height = 600
    width = 800

    if config is None:
        config = DEFAULT_PLOT_CONFIG.copy()
        if len(expression_str_list) > 1:
            config.legend.visible = True
    range = PlotRange(x_range, y_range)
    sampler = CurveSampler(range, config.sampling)
    plotter = Plotter(range, config)

    sampled_curves: list[SampledParameterizedCurve] = []
    for i, expression_str_pair in enumerate(expression_str_list):
        x_expression_str, y_expression_str = expression_str_pair
        curve_spec = ParameterizedCurveSpec(
            name=f"x={x_expression_str}, y={y_expression_str}",
            x_expression_str=x_expression_str,
            y_expression_str=y_expression_str,
            parameter_range=parameter_range,
            color=CURVE_COLORS[i % len(CURVE_COLORS)],
        )
        sampled_curve = sampler(curve_spec)
        sampled_curves.append(sampled_curve)

    plotter.legend_entries = [
        (sampled_curve.name, sampled_curve.color) for sampled_curve in sampled_curves
    ]

    image = numpy.ndarray((height, width, 3), dtype=numpy.uint8)
    plotter.write(sampled_curves, image)

    return image


class TestParameterizedCurves:
    """Tests for parameterized curves."""

    def test_line(self, image_approver) -> None:
        """Test of sampling a line."""
        image = plot_parameterized_curve(
            [("t", "2 * t")], (-1.2, 1.2), (-2.5, 2.5), (-1.0, 1.0)
        )
        image_approver.verify(image)

    def test_circle(self, image_approver) -> None:
        """Test of sampling a circle."""
        image = plot_parameterized_curve(
            [("cos(t)", "sin(t)")], (-1.2, 1.2), (-1.2, 1.2), (0.0, 2.0 * numpy.pi)
        )
        image_approver.verify(image)
