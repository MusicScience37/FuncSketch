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

"""Benchmark of plotting."""

import typing

import numpy
import pytest

from func_sketch._cpp import (
    PlotRange,
)
from func_sketch._gui.constants import CURVE_COLORS, DEFAULT_PLOT_CONFIG
from func_sketch._impl.curve_config import CurveConfig
from func_sketch._impl.curve_sampler import CurveSampler
from func_sketch._impl.plotter import Plotter

EXPRESSION_STR_LIST = [
    "x",
    "x * x",
    "x ** 3",
    "exp(x)",
    "log10(x)",
    "acosh(x)",
    "gamma(x)",
]


@pytest.mark.parametrize("expression_str", EXPRESSION_STR_LIST)
def test_plot_function(benchmark: typing.Callable, expression_str: str) -> None:
    """Benchmark of plotting functions."""
    height = 600
    width = 800
    range = PlotRange((-3.0, 3.0), (-3.0, 3.0))
    config = DEFAULT_PLOT_CONFIG

    sampler = CurveSampler(range, config)
    plotter = Plotter(range, config)

    curve_config = CurveConfig(expression_str, CURVE_COLORS[0])
    image = numpy.ndarray((height, width, 3), dtype=numpy.uint8)

    def plot_function() -> None:
        sampled_curve = sampler(curve_config)
        plotter([sampled_curve], image)

    benchmark.extra_info["num_points"] = len(sampler(curve_config).samples.points)  # type: ignore[attr-defined]
    benchmark(plot_function)


@pytest.mark.parametrize("expression_str", EXPRESSION_STR_LIST)
def test_sample_function(benchmark: typing.Callable, expression_str: str) -> None:
    """Benchmark of sampling functions."""
    range = PlotRange((-3.0, 3.0), (-3.0, 3.0))
    config = DEFAULT_PLOT_CONFIG

    sampler = CurveSampler(range, config)

    curve_config = CurveConfig(expression_str, CURVE_COLORS[0])

    def sample_function() -> None:
        sampler(curve_config)

    benchmark.extra_info["num_points"] = len(sampler(curve_config).samples.points)  # type: ignore[attr-defined]
    benchmark(sample_function)
