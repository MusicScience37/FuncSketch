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

    def test_complex_bessel_i(self) -> None:
        """Test of modified Bessel function of the first kind for complex numbers."""
        parser = ExpressionParser()
        evaluator = ExpressionEvaluator()

        expression = parser("real(bessel_i(1.23, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(0.08356057467441566, abs=1e-10)

        expression = parser("imag(bessel_i(1.23, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(0.2720393265407485, abs=1e-10)

    def test_complex_bessel_k(self) -> None:
        """Test of modified Bessel function of the second kind for complex numbers."""
        parser = ExpressionParser()
        evaluator = ExpressionEvaluator()

        expression = parser("real(bessel_k(1.23, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(0.07353396460130068, abs=1e-10)

        expression = parser("imag(bessel_k(1.23, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(-1.3660736982459514, abs=1e-10)

    def test_complex_hankel1(self) -> None:
        """Test of Hankel function of the first kind for complex numbers."""
        parser = ExpressionParser()
        evaluator = ExpressionEvaluator()

        expression = parser("real(hankel1(1.23, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(-0.6103312571408326, abs=1e-10)

        expression = parser("imag(hankel1(1.23, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(-0.4177272648754929, abs=1e-10)

    def test_complex_hankel2(self) -> None:
        """Test of Hankel function of the second kind for complex numbers."""
        parser = ExpressionParser()
        evaluator = ExpressionEvaluator()

        expression = parser("real(hankel2(1.23, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(0.862818427103236, abs=1e-10)

        expression = parser("imag(hankel2(1.23, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(0.9636419857970038, abs=1e-10)

    def test_complex_spherical_bessel_j(self) -> None:
        """Test of spherical Bessel function of the first kind for complex numbers."""
        parser = ExpressionParser()
        evaluator = ExpressionEvaluator()

        expression = parser("real(spherical_bessel_j(1, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(0.16723358931297416, abs=1e-10)

        expression = parser("imag(spherical_bessel_j(1, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(0.2193878365394319, abs=1e-10)

    def test_complex_spherical_bessel_y(self) -> None:
        """Test of spherical Bessel function of the second kind for complex numbers."""
        parser = ExpressionParser()
        evaluator = ExpressionEvaluator()

        expression = parser("real(spherical_bessel_y(1, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(0.052038633338083784, abs=1e-10)

        expression = parser("imag(spherical_bessel_y(1, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(1.4985098757444921, abs=1e-10)

    def test_complex_spherical_hankel1(self) -> None:
        """Test of spherical Hankel function of the first kind for complex numbers."""
        parser = ExpressionParser()
        evaluator = ExpressionEvaluator()

        expression = parser("real(spherical_hankel1(1, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(-1.331276286431518, abs=1e-10)

        expression = parser("imag(spherical_hankel1(1, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(0.2714264698775157, abs=1e-10)

    def test_complex_spherical_hankel2(self) -> None:
        """Test of spherical Hankel function of the second kind for complex numbers."""
        parser = ExpressionParser()
        evaluator = ExpressionEvaluator()

        expression = parser("real(spherical_hankel2(1, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(1.6657434650574663, abs=1e-10)

        expression = parser("imag(spherical_hankel2(1, 0.45 + 0.67i))")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(0.1673492032013481, abs=1e-10)

    def test_kelvin_ber(self) -> None:
        """Test of Kelvin function ber."""
        parser = ExpressionParser()
        evaluator = ExpressionEvaluator()

        expression = parser("kelvin_ber(1.23, 0.45)")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(-0.13907260455217346, abs=1e-10)

    def test_kelvin_bei(self) -> None:
        """Test of Kelvin function bei."""
        parser = ExpressionParser()
        evaluator = ExpressionEvaluator()

        expression = parser("kelvin_bei(1.23, 0.45)")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(0.031212118075843828, abs=1e-10)

    def test_kelvin_ker(self) -> None:
        """Test of Kelvin function ker."""
        parser = ExpressionParser()
        evaluator = ExpressionEvaluator()

        expression = parser("kelvin_ker(1.23, 0.45)")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(-2.7406919539931502, abs=1e-10)

    def test_kelvin_kei(self) -> None:
        """Test of Kelvin function kei."""
        parser = ExpressionParser()
        evaluator = ExpressionEvaluator()

        expression = parser("kelvin_kei(1.23, 0.45)")
        result = evaluator(expression, 0.0)
        assert result == pytest.approx(-0.3575494005555532, abs=1e-10)
