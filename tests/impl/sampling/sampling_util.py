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

"""Utility functions for testing sampling."""

import numpy

from func_sketch._cpp import PlotRange, RGBColor, SamplingConfig
from func_sketch._impl.curve_config import CurveConfig
from func_sketch._impl.curve_sampler import CurveSampler


def sample_function(
    expression_str: str, x_range: tuple[float, float], y_range: tuple[float, float]
) -> tuple[numpy.ndarray, numpy.ndarray]:
    """Sample points of a function.

    Args:
        expression_str (str): String of the function expression.
        x_range (tuple[float, float]): Range of x coordinate.
        y_range (tuple[float, float]): Range of y coordinate.

    Returns:
        tuple[numpy.ndarray, numpy.ndarray]: Tuple of x and y values of points.
    """
    line_color = RGBColor(0, 0, 0)  # Not used in this test.

    config = SamplingConfig()
    range = PlotRange(x_range, y_range)
    sampler = CurveSampler(range, config)

    sampled_curve = sampler(CurveConfig(expression_str, line_color))

    x_values = numpy.array([point.x for point in sampled_curve.samples.points])
    y_values = numpy.array([point.y for point in sampled_curve.samples.points])

    return x_values, y_values


def compare_vectors(
    vector1: numpy.ndarray,
    vector2: numpy.ndarray,
    rtol: float = 1e-6,
    atol: float = 1e-6,
) -> None:
    """Compare two vectors for approximate equality.

    Args:
        vector1 (numpy.ndarray): First vector.
        vector2 (numpy.ndarray): Second vector.
        rtol (float): Relative tolerance.
        atol (float): Absolute tolerance.
    """
    assert numpy.allclose(
        vector1, vector2, rtol=rtol, atol=atol
    ), f"Vectors are not approximately equal:\n{vector1}\n{vector2}"
