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
 * \brief Test of ExpressionEvaluator class.
 */
#include "func_sketch/expressions/expression_evaluator.h"

#include <catch2/catch_test_macros.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/expressions/expression_memory_pool.h"
#include "func_sketch/math/binary_operators.h"

TEST_CASE("func_sketch::expressions::ExpressionEvaluator") {
    using func_sketch::Scalar;
    using func_sketch::expressions::BinaryExpression;
    using func_sketch::expressions::ConstantExpression;
    using func_sketch::expressions::ExpressionEvaluator;
    using func_sketch::expressions::ExpressionMemoryPool;
    using func_sketch::expressions::ParameterExpression;
    using func_sketch::math::AdditionOperator;
    using func_sketch::math::BinaryOperator;

    ExpressionMemoryPool pool;
    ExpressionEvaluator evaluator;

    SECTION("evaluate a constant") {
        constexpr Scalar value = 1.23;
        const auto* expression = pool.create<ConstantExpression>(value);

        constexpr Scalar parameter = 4.56;
        Scalar result = 0.0;

        evaluator(*expression, parameter, result);

        CHECK(result == value);
    }

    SECTION("evaluate a parameter") {
        const auto* expression = pool.create<ParameterExpression>();

        constexpr Scalar parameter = 4.56;
        Scalar result = 0.0;

        evaluator(*expression, parameter, result);

        CHECK(result == parameter);
    }

    SECTION("evaluate a binary expression") {
        constexpr Scalar left_value = 1.23;
        auto* left_expression = pool.create<ConstantExpression>(left_value);
        auto* right_expression = pool.create<ParameterExpression>();
        const auto* expression = pool.create<BinaryExpression>(left_expression,
            right_expression, BinaryOperator(AdditionOperator{}));

        constexpr Scalar parameter = 4.56;
        Scalar result = 0.0;

        evaluator(*expression, parameter, result);

        CHECK(result == left_value + parameter);
    }
}
