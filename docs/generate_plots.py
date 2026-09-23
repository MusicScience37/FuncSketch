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

# ruff: noqa: E402

import dataclasses
import pathlib

import cv2
import numpy

from func_sketch._cpp import (
    CurveSampler,
    ExplicitCurveSpec,
    PlotRange,
    Plotter,
    RGBColor,
)
from func_sketch._gui.common.constants import (
    CURVE_COLORS,
    DEFAULT_PLOT_CONFIG,
    DEFAULT_PLOT_RANGE,
)

THIS_DIR = pathlib.Path(__file__).absolute().parent


@dataclasses.dataclass
class PlotInfo:
    """Class to store information of a plot."""

    file_path: str
    """File path of the plot relative to this directory."""

    expression_strs: list[str]
    """List of strings of the function expressions."""

    title: str
    """Title of the plot."""

    x_range: tuple[float, float]
    """Range of x-axis."""

    y_range: tuple[float, float]
    """Range of y-axis."""


PLOT_LIST = [
    # For bessel.rst.
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/bessel_j.webp",
        expression_strs=[
            "bessel_j(0, x)",
            "bessel_j(1, x)",
            "bessel_j(2, x)",
            "bessel_j(3, x)",
        ],
        title="Bessel Functions of the first kind",
        x_range=(-10.0, 10.0),
        y_range=(-0.8, 1.2),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/bessel_y.webp",
        expression_strs=[
            "bessel_y(0, x)",
            "bessel_y(1, x)",
            "bessel_y(2, x)",
            "bessel_y(3, x)",
        ],
        title="Bessel Functions of the second kind",
        x_range=(0.0, 10.0),
        y_range=(-1.0, 0.8),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/bessel_i.webp",
        expression_strs=[
            "bessel_i(0, x)",
            "bessel_i(1, x)",
            "bessel_i(2, x)",
            "bessel_i(3, x)",
        ],
        title="Modified Bessel Functions of the first kind",
        x_range=(-3.0, 3.0),
        y_range=(-3.0, 5.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/bessel_k.webp",
        expression_strs=[
            "bessel_k(0, x)",
            "bessel_k(1, x)",
            "bessel_k(2, x)",
            "bessel_k(3, x)",
        ],
        title="Modified Bessel Functions of the second kind",
        x_range=(0.0, 3.0),
        y_range=(0.0, 3.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/spherical_bessel_j.webp",
        expression_strs=[
            "spherical_bessel_j(0, x)",
            "spherical_bessel_j(1, x)",
            "spherical_bessel_j(2, x)",
            "spherical_bessel_j(3, x)",
        ],
        title="Spherical Bessel Functions of the first kind",
        x_range=(-0.5, 10.0),
        y_range=(-0.4, 1.18),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/spherical_bessel_y.webp",
        expression_strs=[
            "spherical_bessel_y(0, x)",
            "spherical_bessel_y(1, x)",
            "spherical_bessel_y(2, x)",
            "spherical_bessel_y(3, x)",
        ],
        title="Spherical Bessel Functions of the second kind",
        x_range=(-0.5, 10.0),
        y_range=(-3.0, 1.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/kelvin_ber.webp",
        expression_strs=[
            "kelvin_ber(0, x)",
            "kelvin_ber(1, x)",
            "kelvin_ber(2, x)",
            "kelvin_ber(3, x)",
        ],
        title="Kelvin Functions ber",
        x_range=(0.0, 10.0),
        y_range=(-40.0, 40.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/kelvin_bei.webp",
        expression_strs=[
            "kelvin_bei(0, x)",
            "kelvin_bei(1, x)",
            "kelvin_bei(2, x)",
            "kelvin_bei(3, x)",
        ],
        title="Kelvin Functions bei",
        x_range=(0.0, 10.0),
        y_range=(-40.0, 40.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/kelvin_ker.webp",
        expression_strs=[
            "kelvin_ker(0, x)",
            "kelvin_ker(1, x)",
            "kelvin_ker(2, x)",
            "kelvin_ker(3, x)",
        ],
        title="Kelvin Functions ker",
        x_range=(0.0, 10.0),
        y_range=(-3.0, 3.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/kelvin_kei.webp",
        expression_strs=[
            "kelvin_kei(0, x)",
            "kelvin_kei(1, x)",
            "kelvin_kei(2, x)",
            "kelvin_kei(3, x)",
        ],
        title="Kelvin Functions kei",
        x_range=(0.0, 10.0),
        y_range=(-1.0, 1.0),
    ),
    # For error.rst.
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/erf.webp",
        expression_strs=["erf(x)"],
        title="Error Function",
        x_range=(-3.0, 3.0),
        y_range=(-1.2, 1.2),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/erfc.webp",
        expression_strs=["erfc(x)"],
        title="Complementary Error Function",
        x_range=(-3.0, 3.0),
        y_range=(-0.2, 2.2),
    ),
    # For gamma.rst.
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/gamma.webp",
        expression_strs=["gamma(x)"],
        title="Gamma Function",
        x_range=(-3.0, 5.0),
        y_range=(-10.0, 10.0),
    ),
    PlotInfo(
        file_path="sphinx/expression_reference/builtin_functions/plots/lgamma.webp",
        expression_strs=["lgamma(x)"],
        title="Log Gamma Function",
        x_range=(-3.0, 5.0),
        y_range=(-0.5, 3.0),
    ),
]


def generate_plots() -> None:
    """Generate plots."""
    height = 600
    width = 800
    config = DEFAULT_PLOT_CONFIG.copy()
    config.background_color = RGBColor(0xFF, 0xFF, 0xFF)
    config.legend.visible = True
    config.legend.title = "Expression"
    range = DEFAULT_PLOT_RANGE

    sampler = CurveSampler(range, config.sampling)
    plotter = Plotter(range, config)
    plotter.desired_size(height, width)

    for plot_info in PLOT_LIST:
        curve_specs = [
            ExplicitCurveSpec(
                name=expression_str,
                function_expression_str=expression_str,
                color=CURVE_COLORS[i],
            )
            for i, expression_str in enumerate(plot_info.expression_strs)
        ]

        range = PlotRange(plot_info.x_range, plot_info.y_range)
        sampler.range = range
        plotter.range = range

        config.plot_title = plot_info.title
        plotter.config = config

        plotter.legend_entries = [
            (curve_spec.name, curve_spec.color) for curve_spec in curve_specs
        ]

        actual_height, actual_width = plotter.actual_size
        image = numpy.ndarray((actual_height, actual_width, 3), dtype=numpy.uint8)

        sampled_curves = [sampler(curve_spec) for curve_spec in curve_specs]
        plotter.write(sampled_curves, image)

        cv2.cvtColor(image, cv2.COLOR_RGB2BGR, dst=image)

        cv2.imwrite(
            str(THIS_DIR / plot_info.file_path), image, [cv2.IMWRITE_WEBP_QUALITY, 101]
        )


if __name__ == "__main__":
    generate_plots()
