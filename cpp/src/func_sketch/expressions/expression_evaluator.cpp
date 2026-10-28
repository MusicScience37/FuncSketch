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

#include <type_traits>
#include <variant>
#include <vector>

#include <boost/container/static_vector.hpp>
#include <fmt/format.h>

#include "func_sketch/common_types.h"
#include "func_sketch/constants.h"
#include "func_sketch/exceptions.h"

namespace func_sketch::expressions {

void ExpressionEvaluator::operator()(const Expression& expression,
    const ParameterValueDict& parameters, Real& result) {
    Number result_as_number;
    evaluate(expression, parameters, result_as_number);
    std::visit(
        [&result](const auto& value) {
            using ValueType = std::decay_t<decltype(value)>;
            if constexpr (std::is_same_v<ValueType, Complex>) {
                result = std::real(value);
            } else {
                result = static_cast<Real>(value);
            }
        },
        result_as_number);
}

void ExpressionEvaluator::operator()(const Expression& expression,
    const ParameterValueDict& parameters, Number& result) {
    evaluate(expression, parameters, result);
}

void ExpressionEvaluator::evaluate(const Expression& expression,
    const ParameterValueDict& parameters, Number& result) {
    std::visit([&parameters, &result](
                   const auto& expr) { evaluate(expr, parameters, result); },
        expression.as_variant());
}

void ExpressionEvaluator::evaluate(const ConstantExpression& expression,
    const ParameterValueDict& /*parameters*/, Number& result) {
    result = expression.value;
}

void ExpressionEvaluator::evaluate(const ParameterExpression& expression,
    const ParameterValueDict& parameters, Number& result) {
    const auto& value = parameters[expression.type];
    if (!value) {
        throw InvalidExpressionException(
            fmt::format("Parameter {} cannot be used here.", expression));
    }
    result = *value;
}

void ExpressionEvaluator::evaluate(const UnaryExpression& expression,
    const ParameterValueDict& parameters, Number& result) {
    Number target_value;
    evaluate(*expression.target, parameters, target_value);
    expression.operator_object(target_value, result);
}

void ExpressionEvaluator::evaluate(const BinaryExpression& expression,
    const ParameterValueDict& parameters, Number& result) {
    Number left_value;
    evaluate(*expression.left, parameters, left_value);
    Number right_value;
    evaluate(*expression.right, parameters, right_value);
    expression.operator_object(left_value, right_value, result);
}

void ExpressionEvaluator::evaluate(const FunctionCallExpression& expression,
    const ParameterValueDict& parameters, Number& result) {
    constexpr std::size_t max_num_args =
        func_sketch::max_num_function_arguments;
    if (expression.arguments.size() > max_num_args) {
        throw InvalidExpressionException(
            fmt::format("Too many function arguments. max: {}, actual: {}.",
                max_num_args, expression.arguments.size()));
    }
    boost::container::static_vector<Number, max_num_args> argument_values;
    for (const auto& argument : expression.arguments) {
        Number argument_value;
        evaluate(*argument, parameters, argument_value);
        argument_values.push_back(argument_value);
    }
    expression.function(argument_values, result);
}

}  // namespace func_sketch::expressions
