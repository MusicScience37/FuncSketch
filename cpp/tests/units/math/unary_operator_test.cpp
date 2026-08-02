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
 * \brief Test of UnaryOperator class.
 */
#include "func_sketch/math/unary_operator.h"

#include <catch2/catch_test_macros.hpp>

#include "func_sketch/math/unary_operators.h"

TEST_CASE("func_sketch::math::UnaryOperator") {
    using func_sketch::Scalar;
    using func_sketch::math::UnaryMinus;
    using func_sketch::math::UnaryOperator;

    SECTION("create and use an operator") {
        UnaryOperator operator_object(UnaryMinus{});

        CHECK(operator_object.name() == "-");

        constexpr Scalar arg = 1.0;
        Scalar result = 0.0;
        operator_object(arg, result);

        constexpr Scalar expected_result = -arg;
        CHECK(result == expected_result);
    }
}
