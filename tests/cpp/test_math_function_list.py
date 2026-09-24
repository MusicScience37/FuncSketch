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

"""Test of MathFunctionList."""

from func_sketch._cpp import (
    CurveSampler,
    ExpressionParser,
    PlotRange,
    SamplingConfig,
)


class TestMathFunctionList:
    """Test of MathFunctionList."""

    def test_from_expression_parser(self) -> None:
        """Test to get the list from ExpressionParser."""
        parser = ExpressionParser()

        function_list = parser.math_function_list()
        names = [info.name for info in function_list.create_function_info_list()]

        assert "sin" in names
        assert "gamma" in names
        assert "bessel_j" in names

    def test_from_curve_sampler(self) -> None:
        """Test to get the list from CurveSampler."""
        sampler = CurveSampler(PlotRange((-1.0, 1.0), (-1.0, 1.0)), SamplingConfig())

        function_list = sampler.math_function_list()
        names = [info.name for info in function_list.create_function_info_list()]

        assert "sin" in names
        assert "gamma" in names
        assert "bessel_j" in names

    def test_lifetime(self) -> None:
        """Test that the list is usable after the owner is deleted."""
        parser = ExpressionParser()
        function_list = parser.math_function_list()
        del parser

        names = [info.name for info in function_list.create_function_info_list()]

        assert "sin" in names
