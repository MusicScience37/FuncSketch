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

"""Test of functions using Python functions internally."""

import pytest

from func_sketch._cpp import (
    ExpressionEvaluator,
    ExpressionParser,
)


class TestPythonFunctions:
    """Test of functions using Python functions internally."""

    def test_complex_gamma(self) -> None:
        """Test of Gamma function for complex numbers."""
        parser = ExpressionParser()
        evaluator = ExpressionEvaluator()

        expression = parser("real(gamma(0.5 + 0.5i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(0.8181639995, abs=1e-8)

        expression = parser("imag(gamma(0.5 + 0.5i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(-0.7633138287, abs=1e-8)

    def test_complex_bessel_j(self) -> None:
        """Test of Bessel function of the first kind for complex numbers."""
        parser = ExpressionParser()
        evaluator = ExpressionEvaluator()

        expression = parser("real(bessel_j(1.23, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(0.126243584981202, abs=1e-10)

        expression = parser("imag(bessel_j(1.23, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(0.272957360460756, abs=1e-10)

    def test_complex_bessel_y(self) -> None:
        """Test of Bessel function of the second kind for complex numbers."""
        parser = ExpressionParser()
        evaluator = ExpressionEvaluator()

        expression = parser("real(bessel_y(1.23, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(-0.690684625336248, abs=1e-10)

        expression = parser("imag(bessel_y(1.23, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(0.736574842122034, abs=1e-10)
