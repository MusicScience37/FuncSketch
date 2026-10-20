/*
 * Copyright 2026 MusicScience37 (Kenta Kabashima)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*!
 * \file
 * \brief Test of GaussLegendreKronrodIntegrator class.
 */
#include "func_sketch/math/operations/gauss_legendre_kronrod_integrator.h"

#include <cmath>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("func_sketch::math::GaussLegendreKronrodIntegrator") {
    using func_sketch::Complex;
    using func_sketch::Real;
    using func_sketch::math::GaussLegendreKronrodIntegrator;

    constexpr double tol = 1e-4;

    SECTION("functions returning Real") {
        GaussLegendreKronrodIntegrator<Real> integrator;

        SECTION("simple integration of exp(x)") {
            const auto function = [](Real x) { return std::exp(x); };
            const Real actual = integrator(function, 0.0, 1.0);
            constexpr Real expected = std::numbers::e - 1.0;
            CHECK_THAT(actual, Catch::Matchers::WithinRel(expected, tol));
        }

        SECTION("slightly difficult integration of sqrt(1-x^2)") {
            const auto function = [](Real x) { return std::sqrt(1.0 - x * x); };
            const Real actual = integrator(function, 0.0, 1.0);
            constexpr Real expected = std::numbers::pi / 4.0;
            CHECK_THAT(actual, Catch::Matchers::WithinRel(expected, tol));
        }

        SECTION("integration of a oscillatory function 1 + sin(10x)") {
            const auto function = [](Real x) {
                return 1.0 + std::sin(10.0 * x);
            };
            const Real actual = integrator(function, 0.0, 1.0);
            const Real expected = 1.0 + std::pow(std::sin(5.0), 2) / 5.0;
            CHECK_THAT(actual, Catch::Matchers::WithinRel(expected, tol));
        }

        SECTION("integration of a more oscillatory function std::sin(x^2)") {
            const auto function = [](Real x) { return std::sin(x * x); };
            const Real actual = integrator(function, 0.0, 10.0);
            // Actual value computed numerically.
            const Real expected = 0.58367089992962334216;
            CHECK_THAT(actual, Catch::Matchers::WithinRel(expected, tol));
        }

        SECTION("integration of left == right") {
            const auto function = [](Real x) { return x * x; };
            const Real actual = integrator(function, 1.0, 1.0);
            constexpr Real expected = 0.0;
            // The result should be exactly zero in this case.
            CHECK(actual == expected);
        }

        SECTION("integration of left > right") {
            const auto function = [](Real x) { return std::exp(x); };
            const Real actual = integrator(function, 1.0, 0.0);
            constexpr Real expected = -std::numbers::e + 1.0;
            CHECK_THAT(actual, Catch::Matchers::WithinRel(expected, tol));
        }

        SECTION("integration of zero") {
            const auto function = [](Real x) { return 0.0; };
            const Real actual = integrator(function, 0.0, 1.0);
            constexpr Real expected = 0.0;
            CHECK_THAT(actual, Catch::Matchers::WithinAbs(expected, tol));
        }

        SECTION("improper integral of 1/sqrt(x)") {
            // TODO This case should be handled with another method.
            const auto function = [](Real x) { return 1.0 / std::sqrt(x); };
            const Real actual = integrator(function, 0.0, 1.0);
            constexpr Real expected = 2.0;
            constexpr Real tol = 0.1;  // Use a large tolerance here.
            CHECK_THAT(actual, Catch::Matchers::WithinRel(expected, tol));
        }
    }

    SECTION("functions returning Complex") {
        GaussLegendreKronrodIntegrator<Complex> integrator;

        SECTION("simple integration of exp(i x)") {
            const auto function = [](Complex x) {
                return std::exp(Complex(0.0, 1.0) * x);
            };
            const Complex actual =
                integrator(function, 0.0, std::numbers::pi / 4.0);
            const Complex expected =
                Complex(0.0, 1.0) + Complex(1.0, -1.0) * std::sqrt(0.5);
            CHECK_THAT(actual.real(),
                Catch::Matchers::WithinRel(expected.real(), tol));
            CHECK_THAT(actual.imag(),
                Catch::Matchers::WithinRel(expected.imag(), tol));
        }

        SECTION("integration of oscillatory function exp(i x^2)") {
            const auto function = [](Complex x) {
                return std::exp(Complex(0.0, 1.0) * x * x);
            };
            const Complex actual = integrator(function, 0.0, 10.0);
            // Actual value computed numerically.
            const Complex expected =
                Complex(0.60112518481344434813, 0.58367089992962334216);
            CHECK_THAT(actual.real(),
                Catch::Matchers::WithinRel(expected.real(), tol));
            CHECK_THAT(actual.imag(),
                Catch::Matchers::WithinRel(expected.imag(), tol));
        }
    }
}
