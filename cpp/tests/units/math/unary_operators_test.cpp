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
 * \brief Test of unary operators.
 */
#include "func_sketch/math/unary_operators.h"

#include <catch2/catch_test_macros.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/math/unary_operator_type.h"

TEST_CASE("func_sketch::math::UnaryPlusOperator") {
    using func_sketch::Complex;
    using func_sketch::Number;
    using func_sketch::math::UnaryPlusOperator;

    SECTION("check concept") {
        STATIC_REQUIRE(func_sketch::math::UnaryOperatorType<UnaryPlusOperator>);
    }

    SECTION("operate on an integer") {
        constexpr Number arg = 1;
        Number result = 0.0;

        UnaryPlusOperator operator_object;
        operator_object(arg, result);

        constexpr Number expected_result = arg;
        CHECK(result == expected_result);
    }

    SECTION("operate on a real number") {
        constexpr Number arg = 1.0;
        Number result = 0.0;

        UnaryPlusOperator operator_object;
        operator_object(arg, result);

        constexpr Number expected_result = arg;
        CHECK(result == expected_result);
    }

    SECTION("operate on a complex number") {
        constexpr Number arg = Complex(1.0, 2.0);
        Number result = 0.0;

        UnaryPlusOperator operator_object;
        operator_object(arg, result);

        constexpr Number expected_result = arg;
        CHECK(result == expected_result);
    }
}

TEST_CASE("func_sketch::math::UnaryMinusOperator") {
    using func_sketch::Number;
    using func_sketch::math::UnaryMinusOperator;

    SECTION("check concept") {
        STATIC_REQUIRE(
            func_sketch::math::UnaryOperatorType<UnaryMinusOperator>);
    }

    SECTION("operate on an integer") {
        constexpr Number arg = 1;
        Number result = 0.0;

        UnaryMinusOperator operator_object;
        operator_object(arg, result);

        constexpr Number expected_result = -std::get<int>(arg);
        CHECK(result == expected_result);
    }

    SECTION("operate on a real number") {
        constexpr Number arg = 1.0;
        Number result = 0.0;

        UnaryMinusOperator operator_object;
        operator_object(arg, result);

        constexpr Number expected_result = -std::get<double>(arg);
        CHECK(result == expected_result);
    }

    SECTION("operate on a complex number") {
        constexpr Number arg = func_sketch::Complex(1.0, 2.0);
        Number result = 0.0;

        UnaryMinusOperator operator_object;
        operator_object(arg, result);

        constexpr Number expected_result = -std::get<func_sketch::Complex>(arg);
        CHECK(result == expected_result);
    }
}
