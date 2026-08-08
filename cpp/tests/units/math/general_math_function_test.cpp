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
 * \brief Test of GeneralMathFunction class.
 */
#include "func_sketch/math/general_math_function.h"

#include <tuple>
#include <type_traits>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/math/math_function_type.h"

TEST_CASE("func_sketch::math::GeneralMathFunction") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::AcceptableTypes;
    using func_sketch::math::make_general_math_function;
    using func_sketch::math::MathFunctionType;

    SECTION("get the name") {
        const auto function =
            make_general_math_function<std::tuple<AcceptableTypes<Real>>>(
                "test_function", [](Real arg) { return arg * 2; });
        STATIC_REQUIRE(MathFunctionType<std::decay_t<decltype(function)>>);

        CHECK(function.name() == "test_function");
    }

    SECTION("call a function with one argument") {
        const auto function =
            make_general_math_function<std::tuple<AcceptableTypes<Real>>>(
                "test_function", [](Real arg) { return arg * 2; });
        STATIC_REQUIRE(MathFunctionType<std::decay_t<decltype(function)>>);

        constexpr Integer arg = 3;
        Number result;
        function(std::vector<Number>{arg}, result);

        REQUIRE(std::holds_alternative<Real>(result));
        const Real actual_result = std::get<Real>(result);
        CHECK_THAT(actual_result,
            Catch::Matchers::WithinRel(static_cast<Real>(arg * 2)));
    }

    SECTION("call a function with two arguments") {
        const auto function = make_general_math_function<
            std::tuple<AcceptableTypes<Real>, AcceptableTypes<Real>>>(
            "test_function", [](Real arg1, Real arg2) { return arg1 + arg2; });
        STATIC_REQUIRE(MathFunctionType<std::decay_t<decltype(function)>>);

        constexpr Integer arg1 = 3;
        constexpr Real arg2 = 5;
        Number result;
        function(std::vector<Number>{arg1, arg2}, result);

        REQUIRE(std::holds_alternative<Real>(result));
        const Real actual_result = std::get<Real>(result);
        CHECK_THAT(actual_result,
            Catch::Matchers::WithinRel(static_cast<Real>(arg1) + arg2));
    }

    SECTION("call a function with three arguments") {
        const auto function =
            make_general_math_function<std::tuple<AcceptableTypes<Integer>,
                AcceptableTypes<Integer, Real>, AcceptableTypes<Real>>>(
                "test_function", [](Integer arg1, auto arg2, Real arg3) {
                    return static_cast<Real>(arg1) + static_cast<Real>(arg2) +
                        arg3;
                });
        STATIC_REQUIRE(MathFunctionType<std::decay_t<decltype(function)>>);

        constexpr Integer arg1 = 3;
        constexpr Real arg2 = 5;
        constexpr Integer arg3 = 7;
        Number result;
        function(std::vector<Number>{arg1, arg2, arg3}, result);

        REQUIRE(std::holds_alternative<Real>(result));
        const Real actual_result = std::get<Real>(result);
        CHECK_THAT(actual_result,
            Catch::Matchers::WithinRel(
                static_cast<Real>(arg1) + arg2 + static_cast<Real>(arg3)));
    }

    SECTION("call a function with invalid number of arguments") {
        const auto function =
            make_general_math_function<std::tuple<AcceptableTypes<Integer>,
                AcceptableTypes<Integer, Real>, AcceptableTypes<Real>>>(
                "test_function", [](Integer arg1, auto arg2, Real arg3) {
                    return static_cast<Real>(arg1) + static_cast<Real>(arg2) +
                        arg3;
                });
        STATIC_REQUIRE(MathFunctionType<std::decay_t<decltype(function)>>);

        constexpr Integer arg1 = 3;
        constexpr Real arg2 = 5;
        constexpr Integer arg3 = 7;
        constexpr Real arg4 = 9;
        Number result;

        CHECK_THROWS(function(std::vector<Number>{}, result));
        CHECK_THROWS(function(std::vector<Number>{arg1}, result));
        CHECK_THROWS(function(std::vector<Number>{arg1, arg2}, result));
        CHECK_NOTHROW(function(std::vector<Number>{arg1, arg2, arg3}, result));
        CHECK_THROWS(
            function(std::vector<Number>{arg1, arg2, arg3, arg4}, result));
    }

    SECTION("call a function with an incompatible argument type") {
        const auto function =
            make_general_math_function<std::tuple<AcceptableTypes<Integer>,
                AcceptableTypes<Integer, Real>, AcceptableTypes<Real>>>(
                "test_function", [](Integer arg1, auto arg2, Real arg3) {
                    return static_cast<Real>(arg1) + static_cast<Real>(arg2) +
                        arg3;
                });
        STATIC_REQUIRE(MathFunctionType<std::decay_t<decltype(function)>>);

        constexpr Real arg1 = 3;
        constexpr Real arg2 = 5;
        constexpr Integer arg3 = 7;
        Number result;

        CHECK_THROWS(function(std::vector<Number>{arg1, arg2, arg3}, result));
    }
}
