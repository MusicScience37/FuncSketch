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
 * \brief Implementation of ExpressionEvaluator class.
 */
#include "func_sketch/expressions/expression_evaluator.h"

#include <limits>
#include <variant>
#include <vector>

#include "func_sketch/common_types.h"

namespace func_sketch::expressions {

void ExpressionEvaluator::operator()(
    const Expression& expression, Real parameter, Real& result) {
    std::visit([&parameter, &result](
                   const auto& expr) { evaluate(expr, parameter, result); },
        expression.as_variant());
}

void ExpressionEvaluator::evaluate(
    const ConstantExpression& expression, Real /*parameter*/, Real& result) {
    result = expression.value;
}

void ExpressionEvaluator::evaluate(
    const ParameterExpression& /*expression*/, Real parameter, Real& result) {
    result = parameter;
}

void ExpressionEvaluator::evaluate(
    const UnaryExpression& expression, Real parameter, Real& result) {
    Real target_value{std::numeric_limits<Real>::quiet_NaN()};
    operator()(*expression.target, parameter, target_value);
    expression.operator_object(target_value, result);
}

void ExpressionEvaluator::evaluate(
    const BinaryExpression& expression, Real parameter, Real& result) {
    Real left_value{std::numeric_limits<Real>::quiet_NaN()};
    operator()(*expression.left, parameter, left_value);
    Real right_value{std::numeric_limits<Real>::quiet_NaN()};
    operator()(*expression.right, parameter, right_value);
    expression.operator_object(left_value, right_value, result);
}

void ExpressionEvaluator::evaluate(
    const FunctionCallExpression& expression, Real parameter, Real& result) {
    std::vector<Real> argument_values;
    argument_values.reserve(expression.arguments.size());
    for (const auto& argument : expression.arguments) {
        Real argument_value{std::numeric_limits<Real>::quiet_NaN()};
        operator()(*argument, parameter, argument_value);
        argument_values.push_back(argument_value);
    }
    expression.function(argument_values, result);
}

}  // namespace func_sketch::expressions
