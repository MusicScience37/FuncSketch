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
 * \brief Test of BinaryExpression structure.
 */
#include "func_sketch/expressions/binary_expression.h"

#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

#include "func_sketch/expressions/constant_expression.h"
#include "func_sketch/expressions/expression_memory_pool.h"
#include "func_sketch/expressions/parameter_expression.h"
#include "func_sketch/math/binary_operators.h"

TEST_CASE("BinaryExpression") {
    using func_sketch::expressions::BinaryExpression;
    using func_sketch::expressions::ConstantExpression;
    using func_sketch::expressions::Expression;
    using func_sketch::expressions::ExpressionMemoryPool;
    using func_sketch::expressions::ParameterExpression;
    using func_sketch::math::AdditionOperator;
    using func_sketch::math::BinaryOperator;

    SECTION("format") {
        ExpressionMemoryPool pool;
        constexpr double left_value = 1.23;
        Expression* left = pool.create<ConstantExpression>(left_value);
        Expression* right = pool.create<ParameterExpression>();
        Expression* binary_expression = pool.create<BinaryExpression>(
            left, right, BinaryOperator(AdditionOperator{}));

        CHECK(fmt::format("{}", *binary_expression) == "add(1.23, x)");
    }
}
