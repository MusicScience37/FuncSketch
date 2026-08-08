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
 * \brief Test of ExpressionPtr class.
 */
#include "func_sketch/expressions/expression_ptr.h"

#include <catch2/catch_test_macros.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/expressions/constant_expression.h"
#include "func_sketch/expressions/expression.h"
#include "func_sketch/expressions/expression_memory_pool.h"

TEST_CASE("func_sketch::expressions::ExpressionPtr") {
    using func_sketch::Number;
    using func_sketch::expressions::ConstantExpression;
    using func_sketch::expressions::Expression;
    using func_sketch::expressions::ExpressionMemoryPool;
    using func_sketch::expressions::ExpressionPtr;

    SECTION("create an expression") {
        auto memory_pool = std::make_unique<ExpressionMemoryPool>();
        constexpr double value = 1.23;
        Expression* expression = memory_pool->create<ConstantExpression>(value);

        ExpressionPtr expression_ptr(expression, std::move(memory_pool));

        CHECK(expression_ptr.get() == expression);
        CHECK(expression_ptr->as<ConstantExpression>().value == Number(value));
    }

    SECTION("move construct") {
        auto memory_pool = std::make_unique<ExpressionMemoryPool>();
        constexpr double value = 1.23;
        Expression* expression = memory_pool->create<ConstantExpression>(value);

        ExpressionPtr origin(expression, std::move(memory_pool));
        ExpressionPtr moved(std::move(origin));

        CHECK(moved.get() == expression);
        CHECK(moved->as<ConstantExpression>().value == Number(value));
    }

    SECTION("move assign") {
        auto memory_pool = std::make_unique<ExpressionMemoryPool>();
        constexpr double value = 1.23;
        Expression* expression = memory_pool->create<ConstantExpression>(value);

        ExpressionPtr origin(expression, std::move(memory_pool));
        ExpressionPtr moved;
        moved = std::move(origin);

        CHECK(moved.get() == expression);
        CHECK(moved->as<ConstantExpression>().value == Number(value));
    }

    SECTION("reset") {
        auto memory_pool = std::make_unique<ExpressionMemoryPool>();
        constexpr double value = 1.23;
        Expression* expression = memory_pool->create<ConstantExpression>(value);

        ExpressionPtr expression_ptr(expression, std::move(memory_pool));
        expression_ptr.reset();

        CHECK(expression_ptr.get() == nullptr);
    }
}
