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
 * \brief Test of BinaryOperator class.
 */
#include "func_sketch/math/binary_operator.h"

#include <catch2/catch_test_macros.hpp>

#include "func_sketch/math/binary_operators.h"

TEST_CASE("func_sketch::math::BinaryOperator") {
    using func_sketch::Number;
    using func_sketch::math::AdditionOperator;
    using func_sketch::math::BinaryOperator;

    SECTION("create and use an operator") {
        BinaryOperator operator_object(AdditionOperator{});

        CHECK(operator_object.name() == "add");

        constexpr Number left = 1.0;
        constexpr Number right = 2.0;
        Number result = 0.0;
        operator_object(left, right, result);

        constexpr Number expected_result =
            std::get<double>(left) + std::get<double>(right);
        CHECK(result == expected_result);
    }
}
