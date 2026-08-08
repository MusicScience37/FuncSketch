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
#include "func_sketch/expressions/expression.h"
#include "func_sketch/expressions/expression_memory_pool.h"
#include "func_sketch/math/binary_operators.h"
#include "func_sketch/math/functions/exp.h"
#include "func_sketch/math/unary_operators.h"

TEST_CASE("func_sketch::expressions::ExpressionEvaluator") {
    using func_sketch::Real;
    using func_sketch::expressions::BinaryExpression;
    using func_sketch::expressions::ConstantExpression;
    using func_sketch::expressions::Expression;
    using func_sketch::expressions::ExpressionEvaluator;
    using func_sketch::expressions::ExpressionMemoryPool;
    using func_sketch::expressions::FunctionCallExpression;
    using func_sketch::expressions::ParameterExpression;
    using func_sketch::expressions::UnaryExpression;
    using func_sketch::math::AdditionOperator;
    using func_sketch::math::BinaryOperator;
    using func_sketch::math::ExpFunction;
    using func_sketch::math::MathFunction;
    using func_sketch::math::UnaryMinusOperator;
    using func_sketch::math::UnaryOperator;

    ExpressionMemoryPool pool;
    ExpressionEvaluator evaluator;

    SECTION("evaluate a constant") {
        constexpr Real value = 1.23;
        auto* expression = pool.create<ConstantExpression>(value);

        constexpr Real parameter = 4.56;
        Real result = 0.0;

        evaluator(*expression, parameter, result);

        CHECK(result == value);

        pool.destroy(expression);
    }

    SECTION("evaluate a parameter") {
        auto* expression = pool.create<ParameterExpression>();

        constexpr Real parameter = 4.56;
        Real result = 0.0;

        evaluator(*expression, parameter, result);

        CHECK(result == parameter);

        pool.destroy(expression);
    }

    SECTION("evaluate a unary expression") {
        constexpr Real value = 1.23;
        auto* target_expression = pool.create<ConstantExpression>(value);
        auto* expression = pool.create<UnaryExpression>(
            target_expression, UnaryOperator(UnaryMinusOperator{}));

        constexpr Real parameter = 4.56;
        Real result = 0.0;

        evaluator(*expression, parameter, result);

        CHECK(result == -value);

        pool.destroy(expression);
    }

    SECTION("evaluate a binary expression") {
        constexpr Real left_value = 1.23;
        auto* left_expression = pool.create<ConstantExpression>(left_value);
        auto* right_expression = pool.create<ParameterExpression>();
        auto* expression = pool.create<BinaryExpression>(left_expression,
            right_expression, BinaryOperator(AdditionOperator{}));

        constexpr Real parameter = 4.56;
        Real result = 0.0;

        evaluator(*expression, parameter, result);

        CHECK(result == left_value + parameter);

        pool.destroy(expression);
    }

    SECTION("evaluate a function call expression") {
        auto* argument = pool.create<ParameterExpression>();
        auto* expression = pool.create<FunctionCallExpression>(
            std::vector<Expression*>{argument}, MathFunction(ExpFunction{}));

        constexpr Real parameter = 4.56;
        Real result = 0.0;

        evaluator(*expression, parameter, result);

        CHECK(result == std::exp(parameter));

        pool.destroy(expression);
    }
}
