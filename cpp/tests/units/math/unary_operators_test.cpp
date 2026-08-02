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

#include "func_sketch/math/unary_operator_type.h"

TEST_CASE("func_sketch::math::UnaryPlusOperator") {
    using func_sketch::Scalar;
    using func_sketch::math::UnaryPlusOperator;

    SECTION("check concept") {
        STATIC_REQUIRE(func_sketch::math::UnaryOperatorType<UnaryPlusOperator>);
    }

    SECTION("operate on a scalar") {
        constexpr Scalar arg = 1.0;
        Scalar result = 0.0;

        UnaryPlusOperator operator_object;
        operator_object(arg, result);

        constexpr Scalar expected_result = arg;
        CHECK(result == expected_result);
    }
}

TEST_CASE("func_sketch::math::UnaryMinusOperator") {
    using func_sketch::Scalar;
    using func_sketch::math::UnaryMinusOperator;

    SECTION("check concept") {
        STATIC_REQUIRE(
            func_sketch::math::UnaryOperatorType<UnaryMinusOperator>);
    }

    SECTION("operate on a scalar") {
        constexpr Scalar arg = 1.0;
        Scalar result = 0.0;

        UnaryMinusOperator operator_object;
        operator_object(arg, result);

        constexpr Scalar expected_result = -arg;
        CHECK(result == expected_result);
    }
}
