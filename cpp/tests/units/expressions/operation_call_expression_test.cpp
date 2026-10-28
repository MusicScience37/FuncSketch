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
 * \brief Test of OperationCallExpression structure.
 */
#include "func_sketch/expressions/operation_call_expression.h"

#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

#include "func_sketch/common_types.h"
#include "func_sketch/expressions/constant_expression.h"
#include "func_sketch/expressions/expression_memory_pool.h"
#include "func_sketch/expressions/operations/integration_operation.h"
#include "func_sketch/expressions/parameter_expression.h"
#include "func_sketch/parameter_type.h"

TEST_CASE("func_sketch::expressions::OperationCallExpression") {
    using func_sketch::Number;
    using func_sketch::ParameterType;
    using func_sketch::expressions::ConstantExpression;
    using func_sketch::expressions::Expression;
    using func_sketch::expressions::ExpressionMemoryPool;
    using func_sketch::expressions::integration_operation;
    using func_sketch::expressions::OperationCallExpression;
    using func_sketch::expressions::ParameterExpression;

    SECTION("format") {
        ExpressionMemoryPool pool;
        Expression* function =
            pool.create<ParameterExpression>(ParameterType::s);
        Expression* left = pool.create<ConstantExpression>(Number(0.0));
        Expression* right = pool.create<ParameterExpression>(ParameterType::x);
        Expression* operation_call_expression =
            pool.create<OperationCallExpression>(
                std::vector<Expression*>{function, left, right},
                integration_operation());

        CHECK(fmt::format("{}", *operation_call_expression) ==
            "integrate(s, 0, x)");

        pool.destroy(operation_call_expression);
    }
}
