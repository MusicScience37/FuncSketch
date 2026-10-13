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

"""Tests for parameterized curves."""

import numpy

from func_sketch._cpp import (
    CurveSampler,
    ParameterizedCurveSpec,
    PlotRange,
    RGBColor,
    SamplingConfig,
)

from .sampling_util import compare_vectors


def sample_parameterized_curve(
    x_expression_str: str,
    y_expression_str: str,
    x_range: tuple[float, float],
    y_range: tuple[float, float],
    parameter_range: tuple[float, float],
) -> tuple[numpy.ndarray, numpy.ndarray, numpy.ndarray]:
    """Sample points of a parameterized curve.

    Args:
        x_expression_str (str): String of the function expression for the x coordinate.
        y_expression_str (str): String of the function expression for the y coordinate.
        x_range (tuple[float, float]): Range of the x coordinate.
        y_range (tuple[float, float]): Range of the y coordinate.
        parameter_range (tuple[float, float]): Range of the parameter.

    Returns:
        tuple[numpy.ndarray, numpy.ndarray, numpy.ndarray]:
            Arrays of the parameter values, x coordinates, and y coordinates.
    """
    line_color = RGBColor(0, 0, 0)  # Not used in this test.

    config = SamplingConfig()
    range = PlotRange(x_range, y_range)
    sampler = CurveSampler(range, config)

    curve_spec = ParameterizedCurveSpec(
        name="Curve",
        x_expression_str=x_expression_str,
        y_expression_str=y_expression_str,
        parameter_range=parameter_range,
        color=line_color,
    )
    sampled_curve = sampler(curve_spec)

    parameter_values = numpy.array([point.t for point in sampled_curve.points])
    x_values = numpy.array([point.x for point in sampled_curve.points])
    y_values = numpy.array([point.y for point in sampled_curve.points])

    return parameter_values, x_values, y_values


class TestParameterizedCurves:
    """Tests for parameterized curves."""

    def test_circle(self) -> None:
        """Test of sampling a circle."""
        parameter_values, x_values, y_values = sample_parameterized_curve(
            x_expression_str="cos(t)",
            y_expression_str="sin(t)",
            x_range=(-1.0, 1.0),
            y_range=(-1.0, 1.0),
            parameter_range=(0.0, 2.0 * numpy.pi),
        )

        expected_x_values = numpy.cos(parameter_values)
        expected_y_values = numpy.sin(parameter_values)

        compare_vectors(x_values, expected_x_values)
        compare_vectors(y_values, expected_y_values)
