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

#include <cmath>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"
#include "single_variate_function_util.h"

TEST_CASE("func_sketch::math::pow_function") {
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

        const Real expected = std::pow(base, exponent);
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on an integer base and a real exponent") {
        constexpr Integer base = 2;
        constexpr Real exponent = 3.5;

        Number result;
        function_object(std::vector<Number>{base, exponent}, result);

        const Real expected = std::pow(base, exponent);
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on a real base and an integer exponent") {
        constexpr Real base = 2.5;
        constexpr Integer exponent = 3;

        Number result;
        function_object(std::vector<Number>{base, exponent}, result);

        const Real expected = std::pow(base, exponent);
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on a real base and a real exponent") {
        constexpr Real base = 2.5;
        constexpr Real exponent = 3.5;

        Number result;
        function_object(std::vector<Number>{base, exponent}, result);

        const Real expected = std::pow(base, exponent);
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
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
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::sqrt_function;

    const auto function_object = sqrt_function();
    const auto reference_function = [](Real arg) { return std::sqrt(arg); };

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, reference_function);

        test_single_variate_function<Real, Real>(
            function_object, 1.23, reference_function);
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
    const auto reference_function = [](Real arg) { return std::cbrt(arg); };

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, reference_function);

        test_single_variate_function<Real, Real>(
            function_object, 1.23, reference_function);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}
