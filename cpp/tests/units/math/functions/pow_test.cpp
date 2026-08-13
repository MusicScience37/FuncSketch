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
 * \brief Test of power functions.
 */
#include "func_sketch/math/functions/pow.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"
#include "single_variate_function_util.h"

TEST_CASE("func_sketch::math::pow_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::pow_function;

    const auto function_object = pow_function();

    SECTION("operate on an integer base and an integer exponent") {
        constexpr Integer base = 2;
        constexpr Integer exponent = 3;

        Number result;
        function_object(std::vector<Number>{base, exponent}, result);

        constexpr Real expected = 8.0;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on an integer base and a real exponent") {
        constexpr Integer base = 2;
        constexpr Real exponent = 3.5;

        Number result;
        function_object(std::vector<Number>{base, exponent}, result);

        constexpr Real expected = 11.313708498984761;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on a real base and an integer exponent") {
        constexpr Real base = 2.5;
        constexpr Integer exponent = 3;

        Number result;
        function_object(std::vector<Number>{base, exponent}, result);

        constexpr Real expected = 15.625;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on a real base and a real exponent") {
        constexpr Real base = 2.5;
        constexpr Real exponent = 3.5;

        Number result;
        function_object(std::vector<Number>{base, exponent}, result);

        constexpr Real expected = 24.705294220065465;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on a complex base and an integer exponent") {
        const Complex base{1.5, 2.0};
        constexpr Integer exponent = 3;

        Number result;
        function_object(std::vector<Number>{base, exponent}, result);

        const Complex expected{-14.625, 5.5};
        const auto& result_value = std::get<Complex>(result);
        CHECK_THAT(
            result_value.real(), Catch::Matchers::WithinRel(expected.real()));
        CHECK_THAT(
            result_value.imag(), Catch::Matchers::WithinRel(expected.imag()));
    }

    SECTION("operate on a complex base and a real exponent") {
        const Complex base{1.5, 2.0};
        constexpr Real exponent = 3.5;

        Number result;
        function_object(std::vector<Number>{base, exponent}, result);

        const Complex expected{-24.57196064623253, -2.5632620818012297};
        const auto& result_value = std::get<Complex>(result);
        CHECK_THAT(
            result_value.real(), Catch::Matchers::WithinRel(expected.real()));
        CHECK_THAT(
            result_value.imag(), Catch::Matchers::WithinRel(expected.imag()));
    }

    SECTION("operate on a complex base and a complex exponent") {
        const Complex base{1.5, 2.0};
        const Complex exponent{0.5, 1.2};

        Number result;
        function_object(std::vector<Number>{base, exponent}, result);

        const Complex expected{0.0039491825678131635, 0.5196302517132119};
        const auto& result_value = std::get<Complex>(result);
        CHECK_THAT(
            result_value.real(), Catch::Matchers::WithinRel(expected.real()));
        CHECK_THAT(
            result_value.imag(), Catch::Matchers::WithinRel(expected.imag()));
    }

    SECTION("operate on an integer base and a complex exponent") {
        constexpr Integer base = 2;
        const Complex exponent{0.5, 1.2};

        Number result;
        function_object(std::vector<Number>{base, exponent}, result);

        const Complex expected{0.9525628836094384, 1.0452865409875285};
        const auto& result_value = std::get<Complex>(result);
        CHECK_THAT(
            result_value.real(), Catch::Matchers::WithinRel(expected.real()));
        CHECK_THAT(
            result_value.imag(), Catch::Matchers::WithinRel(expected.imag()));
    }

    SECTION("operate on a real base and a complex exponent") {
        constexpr Real base = 2.5;
        const Complex exponent{0.5, 1.2};

        Number result;
        function_object(std::vector<Number>{base, exponent}, result);

        const Complex expected{0.7178340535990325, 1.408798875458659};
        const auto& result_value = std::get<Complex>(result);
        CHECK_THAT(
            result_value.real(), Catch::Matchers::WithinRel(expected.real()));
        CHECK_THAT(
            result_value.imag(), Catch::Matchers::WithinRel(expected.imag()));
    }

    SECTION("check the number of arguments") {
        Number result;
        const Number arg = 1;
        CHECK_THROWS(function_object(std::vector<Number>{}, result));
        CHECK_THROWS(function_object(std::vector<Number>{arg}, result));
        CHECK_THROWS(
            function_object(std::vector<Number>{arg, arg, arg}, result));
    }
}

TEST_CASE("func_sketch::math::sqrt_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::sqrt_function;

    const auto function_object = sqrt_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(function_object, 2,
            1.4142135623730951);  // NOLINT(modernize-use-std-numbers)

        test_single_variate_function<Real, Real>(
            function_object, 1.23, 1.1090536506409416);

        test_single_variate_function<Complex, Complex>(function_object,
            Complex(1.0, 2.0), Complex(1.272019649514069, 0.7861513777574233));
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::cbrt_function") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::cbrt_function;

    const auto function_object = cbrt_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, 1.2599210498948732);

        test_single_variate_function<Real, Real>(
            function_object, 1.23, 1.0714412696907731);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}
