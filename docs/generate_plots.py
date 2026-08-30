#!/usr/bin/env python3

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

"""Script to generate plots for documents."""

import os

# This must be set before importing Kivy.
os.environ["KIVY_NO_ARGS"] = "1"

# flake8: noqa: E402
# pylint: disable=wrong-import-position

import dataclasses
import pathlib

import cv2
import numpy

from func_sketch._cpp import (
    PlotRange,
    RGBColor,
)
from func_sketch._gui.constants import (
    CURVE_COLORS,
    DEFAULT_PLOT_CONFIG,
    DEFAULT_PLOT_RANGE,
)
from func_sketch._impl.curve_config import CurveConfig
from func_sketch._impl.curve_sampler import CurveSampler
from func_sketch._impl.plotter import Plotter

THIS_DIR = pathlib.Path(__file__).absolute().parent


@dataclasses.dataclass
class PlotInfo:
    """Class to store information of a plot."""

    file_path: str
    """File path of the plot relative to this directory."""

    expression_str: str
    """String of the function expression."""

    x_range: tuple[float, float]
    """Range of x-axis."""

    y_range: tuple[float, float]
    """Range of y-axis."""


PLOT_LIST = [
    # For bessel.rst.
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/bessel_j0.png",
        expression_str="bessel_j(0, x)",
        x_range=(-10.0, 10.0),
        y_range=(-0.5, 1.2),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/bessel_j1.png",
        expression_str="bessel_j(1, x)",
        x_range=(-10.0, 10.0),
        y_range=(-1.0, 1.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/bessel_y0.png",
        expression_str="bessel_y(0, x)",
        x_range=(0.0, 10.0),
        y_range=(-1.0, 1.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/bessel_y1.png",
        expression_str="bessel_y(1, x)",
        x_range=(0.0, 10.0),
        y_range=(-1.0, 1.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/bessel_i0.png",
        expression_str="bessel_i(0, x)",
        x_range=(-3.0, 3.0),
        y_range=(-3.0, 3.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/bessel_i1.png",
        expression_str="bessel_i(1, x)",
        x_range=(-3.0, 3.0),
        y_range=(-3.0, 3.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/bessel_k0.png",
        expression_str="bessel_k(0, x)",
        x_range=(0.0, 3.0),
        y_range=(0.0, 3.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/bessel_k1.png",
        expression_str="bessel_k(1, x)",
        x_range=(0.0, 3.0),
        y_range=(0.0, 3.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/spherical_bessel_j0.png",
        expression_str="spherical_bessel_j(0, x)",
        x_range=(-1.0, 10.0),
        y_range=(-0.5, 1.2),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/spherical_bessel_j1.png",
        expression_str="spherical_bessel_j(1, x)",
        x_range=(-1.0, 10.0),
        y_range=(-0.5, 0.5),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/spherical_bessel_y0.png",
        expression_str="spherical_bessel_y(0, x)",
        x_range=(-1.0, 10.0),
        y_range=(-3.0, 1.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/spherical_bessel_y1.png",
        expression_str="spherical_bessel_y(1, x)",
        x_range=(-1.0, 10.0),
        y_range=(-3.0, 1.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/kelvin_ber.png",
        expression_str="kelvin_ber(0, x)",
        x_range=(0.0, 10.0),
        y_range=(-10.0, 10.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/kelvin_bei.png",
        expression_str="kelvin_bei(0, x)",
        x_range=(0.0, 10.0),
        y_range=(-40.0, 20.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/kelvin_ker.png",
        expression_str="kelvin_ker(0, x)",
        x_range=(0.0, 10.0),
        y_range=(-1.0, 5.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/kelvin_kei.png",
        expression_str="kelvin_kei(0, x)",
        x_range=(0.0, 10.0),
        y_range=(-1.0, 0.2),
    ),
    # For error.rst.
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/erf.png",
        expression_str="erf(x)",
        x_range=(-3.0, 3.0),
        y_range=(-1.5, 1.5),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/erfc.png",
        expression_str="erfc(x)",
        x_range=(-3.0, 3.0),
        y_range=(-0.5, 2.5),
    ),
    # For gamma.rst.
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/gamma.png",
        expression_str="gamma(x)",
        x_range=(-3.0, 5.0),
        y_range=(-10.0, 10.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/lgamma.png",
        expression_str="lgamma(x)",
        x_range=(-3.0, 5.0),
        y_range=(-1.0, 3.0),
    ),
]


def generate_plots() -> None:
    """Generate plots."""
    height = 480
    width = 640
    config = DEFAULT_PLOT_CONFIG
    config.min_plot_margin.top = 70
    config.background_color = RGBColor(0xFF, 0xFF, 0xFF)
    range = DEFAULT_PLOT_RANGE

    sampler = CurveSampler(range, config.sampling)
    plotter = Plotter(range, config)
    plotter.desired_size(height, width)

    for plot_info in PLOT_LIST:
        curve_config = CurveConfig(
            function_expression_str=plot_info.expression_str, color=CURVE_COLORS[0]
        )
        range = PlotRange(plot_info.x_range, plot_info.y_range)
        sampler.plot_range = range
        plotter.plot_range = range
        actual_height, actual_width = plotter.actual_size
        image = numpy.ndarray((actual_height, actual_width, 3), dtype=numpy.uint8)
        sampled_curve = sampler(curve_config)
        plotter([sampled_curve], image)

        cv2.cvtColor(image, cv2.COLOR_RGB2BGR, dst=image)

        text_font_face = cv2.FONT_HERSHEY_SIMPLEX
        text_thickness = 1
        text_font_size = 22
        text_font_scale = cv2.getFontScaleFromHeight(
            text_font_face, text_font_size, text_thickness
        )
        cv2.putText(
            image,
            f"Plot of {plot_info.expression_str}",
            (60, 45),
            text_font_face,
            text_font_scale,
            (0x2A, 0x2D, 0x31),
            text_thickness,
            cv2.LINE_AA,
        )

        cv2.imwrite(str(THIS_DIR / plot_info.file_path), image)


if __name__ == "__main__":
    generate_plots()
