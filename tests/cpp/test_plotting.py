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
    ExpressionParser,
    FunctionSampler,
    PlotConfig,
    PlotRange,
    Plotter,
    RGBColor,
)


def _plot_function(
    expression_str: str, x_range: tuple[float, float], y_range: tuple[float, float]
) -> numpy.ndarray:
    height = 600
    width = 800
    line_color = RGBColor(0xCA, 0x76, 0x39)

    parser = ExpressionParser()
    config = PlotConfig()
    range = PlotRange(x_range, y_range)
    sampler = FunctionSampler(range, config.sampling)
    plotter = Plotter(range, config)

    expression = parser(expression_str)
    samples = sampler(expression)
    image = numpy.ndarray((height, width, 3), dtype=numpy.uint8)
    plotter.write_background(image)
    plotter.write_curve(samples, line_color, image)

    return image


class TestPlotting:
    """Test of plotting."""

    def test_plot_x(self, image_approver) -> None:
        """Test of plotting x."""
        image = _plot_function("x", (-3.0, 3.0), (-3.0, 3.0))
        image_approver.verify(image)

    def test_plot_exp(self, image_approver) -> None:
        """Test of plotting exp(x)."""
        image = _plot_function("exp(x)", (-3.0, 3.0), (-1.0, 5.0))
        image_approver.verify(image)
