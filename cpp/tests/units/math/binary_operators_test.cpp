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
 * \brief Test of binary operators.
 */
#include "func_sketch/math/binary_operators.h"

#include <catch2/catch_test_macros.hpp>

#include "func_sketch/math/binary_operator_type.h"

TEST_CASE("func_sketch::math::AdditionOperator") {
    using func_sketch::Scalar;
    using func_sketch::math::AdditionOperator;

    SECTION("check concept") {
        STATIC_REQUIRE(func_sketch::math::BinaryOperatorType<AdditionOperator>);
    }

    SECTION("operate on a pair of scalars") {
        constexpr Scalar left = 1.0;
        constexpr Scalar right = 2.0;
        Scalar result = 0.0;

        AdditionOperator operator_object;
        operator_object(left, right, result);

        constexpr Scalar expected_result = left + right;
        CHECK(result == expected_result);
    }
}

TEST_CASE("func_sketch::math::SubtractionOperator") {
    using func_sketch::Scalar;
    using func_sketch::math::SubtractionOperator;

    SECTION("check concept") {
        STATIC_REQUIRE(
            func_sketch::math::BinaryOperatorType<SubtractionOperator>);
    }

    SECTION("operate on a pair of scalars") {
        constexpr Scalar left = 1.0;
        constexpr Scalar right = 2.0;
        Scalar result = 0.0;

        SubtractionOperator operator_object;
        operator_object(left, right, result);

        constexpr Scalar expected_result = left - right;
        CHECK(result == expected_result);
    }
}

TEST_CASE("func_sketch::math::MultiplicationOperator") {
    using func_sketch::Scalar;
    using func_sketch::math::MultiplicationOperator;

    SECTION("check concept") {
        STATIC_REQUIRE(
            func_sketch::math::BinaryOperatorType<MultiplicationOperator>);
    }

    SECTION("operate on a pair of scalars") {
        constexpr Scalar left = 1.0;
        constexpr Scalar right = 2.0;
        Scalar result = 0.0;

        MultiplicationOperator operator_object;
        operator_object(left, right, result);

        constexpr Scalar expected_result = left * right;
        CHECK(result == expected_result);
    }
}

TEST_CASE("func_sketch::math::DivisionOperator") {
    using func_sketch::Scalar;
    using func_sketch::math::DivisionOperator;

    SECTION("check concept") {
        STATIC_REQUIRE(func_sketch::math::BinaryOperatorType<DivisionOperator>);
    }

    SECTION("operate on a pair of scalars") {
        constexpr Scalar left = 1.0;
        constexpr Scalar right = 2.0;
        Scalar result = 0.0;

        DivisionOperator operator_object;
        operator_object(left, right, result);

        constexpr Scalar expected_result = left / right;
        CHECK(result == expected_result);
    }
}
