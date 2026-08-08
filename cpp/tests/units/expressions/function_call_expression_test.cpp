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
 * \brief Implementation of FunctionCallExpression structure.
 */
#include "func_sketch/expressions/function_call_expression.h"

#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

#include "func_sketch/expressions/expression_memory_pool.h"
#include "func_sketch/expressions/parameter_expression.h"
#include "func_sketch/math/functions/exp.h"
#include "func_sketch/math/math_function.h"

TEST_CASE("func_sketch::expressions::FunctionCallExpression") {
    using func_sketch::expressions::Expression;
    using func_sketch::expressions::ExpressionMemoryPool;
    using func_sketch::expressions::FunctionCallExpression;
    using func_sketch::expressions::ParameterExpression;
    using func_sketch::math::exp_function;
    using func_sketch::math::MathFunction;

    SECTION("format") {
        ExpressionMemoryPool pool;
        Expression* argument = pool.create<ParameterExpression>();
        auto function = exp_function();
        Expression* function_call_expression =
            pool.create<FunctionCallExpression>(
                std::vector<Expression*>{argument}, function);

        CHECK(fmt::format("{}", *function_call_expression) == "exp(x)");

        pool.destroy(function_call_expression);
    }
}
