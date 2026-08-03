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
 * \brief Implementation of convert_expression function.
 */
#include "func_sketch/parser/convert_expression.h"

#include "func_sketch/exceptions.h"
#include "func_sketch/expressions/binary_expression.h"
#include "func_sketch/expressions/constant_expression.h"
#include "func_sketch/expressions/expression.h"
#include "func_sketch/expressions/expression_memory_pool.h"
#include "func_sketch/expressions/parameter_expression.h"
#include "func_sketch/expressions/unary_expression.h"
#include "func_sketch/math/binary_operator.h"
#include "func_sketch/math/binary_operators.h"
#include "func_sketch/math/math_function_list.h"
#include "func_sketch/math/unary_operators.h"

namespace func_sketch::parser {

/*!
 * \brief Convert parsed expression.
 *
 * \param[in] parsed_expression Parsed expression to convert.
 * \param[in] math_function_list List of math functions.
 * \param[in] pool Memory pool to allocate expressions.
 * \return Converted expression.
 */
[[nodiscard]] expressions::Expression* convert_expression(
    const ParsedExpression& parsed_expression,
    const math::MathFunctionList& math_function_list,
    expressions::ExpressionMemoryPool& pool);

/*!
 * \brief Convert parsed expression.
 *
 * \param[in] parsed_expression Parsed expression to convert.
 * \param[in] pool Memory pool to allocate expressions.
 * \return Converted expression.
 */
[[nodiscard]] expressions::Expression* convert_expression(
    const ParsedConstant& parsed_expression,
    const math::MathFunctionList& /*math_function_list*/,
    expressions::ExpressionMemoryPool& pool) {
    return pool.create<expressions::ConstantExpression>(
        parsed_expression.value);
}

/*!
 * \brief Convert parsed expression.
 *
 * \param[in] parsed_expression Parsed expression to convert.
 * \param[in] pool Memory pool to allocate expressions.
 * \return Converted expression.
 */
[[nodiscard]] expressions::Expression* convert_expression(
    const ParsedIdentifier& parsed_expression,
    const math::MathFunctionList& /*math_function_list*/,
    expressions::ExpressionMemoryPool& pool) {
    if (parsed_expression.name == "x") {
        return pool.create<expressions::ParameterExpression>();
    }
    throw InvalidExpressionException(
        "Unknown identifier: " + parsed_expression.name);
}

/*!
 * \brief Convert parsed expression.
 *
 * \param[in] parsed_expression Parsed expression to convert.
 * \param[in] math_function_list List of math functions.
 * \param[in] pool Memory pool to allocate expressions.
 * \return Converted expression.
 */
[[nodiscard]] expressions::Expression* convert_expression(
    const ParsedFunctionCallExpression& parsed_expression,
    const math::MathFunctionList& math_function_list,
    expressions::ExpressionMemoryPool& pool) {
    auto function =
        math_function_list.get(parsed_expression.function_name.name);
    if (!function) {
        throw InvalidExpressionException(
            "Unknown function: " + parsed_expression.function_name.name);
    }
    std::vector<expressions::Expression*> arguments;
    arguments.reserve(parsed_expression.arguments.size());
    for (const auto& argument : parsed_expression.arguments) {
        arguments.push_back(
            convert_expression(argument, math_function_list, pool));
    }
    return pool.create<expressions::FunctionCallExpression>(
        std::move(arguments), std::move(*function));
}

/*!
 * \brief Get a unary operator by name.
 *
 * \param[in] operator_str Name of the operator.
 * \return Unary operator.
 */
[[nodiscard]] math::UnaryOperator get_unary_operator(
    const std::string& operator_str) {
    if (operator_str == "+") {
        return math::UnaryOperator(math::UnaryPlusOperator());
    }
    if (operator_str == "-") {
        return math::UnaryOperator(math::UnaryMinusOperator());
    }
    throw InvalidExpressionException("Unknown unary operator: " + operator_str);
}

/*!
 * \brief Convert parsed expression.
 *
 * \param[in] parsed_expression Parsed expression to convert.
 * \param[in] math_function_list List of math functions.
 * \param[in] pool Memory pool to allocate expressions.
 * \return Converted expression.
 */
[[nodiscard]] expressions::Expression* convert_expression(
    const ParsedUnaryExpression& parsed_expression,
    const math::MathFunctionList& math_function_list,
    expressions::ExpressionMemoryPool& pool) {
    return pool.create<expressions::UnaryExpression>(
        convert_expression(parsed_expression.operand, math_function_list, pool),
        get_unary_operator(parsed_expression.operator_str));
}

/*!
 * \brief Get a binary operator by name.
 *
 * \param[in] operator_str Name of the operator.
 * \return Binary operator.
 */
[[nodiscard]] math::BinaryOperator get_binary_operator(
    const std::string& operator_str) {
    if (operator_str == "+") {
        return math::BinaryOperator(math::AdditionOperator());
    }
    if (operator_str == "-") {
        return math::BinaryOperator(math::SubtractionOperator());
    }
    if (operator_str == "*") {
        return math::BinaryOperator(math::MultiplicationOperator());
    }
    if (operator_str == "/") {
        return math::BinaryOperator(math::DivisionOperator());
    }
    throw InvalidExpressionException(
        "Unknown binary operator: " + operator_str);
}

/*!
 * \brief Convert parsed expression.
 *
 * \param[in] parsed_expression Parsed expression to convert.
 * \param[in] math_function_list List of math functions.
 * \param[in] pool Memory pool to allocate expressions.
 * \return Converted expression.
 */
[[nodiscard]] expressions::Expression* convert_expression(
    const ParsedBinaryExpression& parsed_expression,
    const math::MathFunctionList& math_function_list,
    expressions::ExpressionMemoryPool& pool) {
    return pool.create<expressions::BinaryExpression>(
        convert_expression(
            parsed_expression.left_operand, math_function_list, pool),
        convert_expression(
            parsed_expression.right_operand, math_function_list, pool),
        get_binary_operator(parsed_expression.operator_str));
}

[[nodiscard]] expressions::Expression* convert_expression(
    const ParsedExpression& parsed_expression,
    const math::MathFunctionList& math_function_list,
    expressions::ExpressionMemoryPool& pool) {
    return boost::apply_visitor(
        [&pool, &math_function_list](
            const auto& concrete_expression) -> expressions::Expression* {
            return convert_expression(
                concrete_expression, math_function_list, pool);
        },
        parsed_expression);
}

[[nodiscard]] expressions::ExpressionPtr convert_expression(
    const ParsedExpression& parsed_expression,
    const math::MathFunctionList& math_function_list) {
    auto pool = std::make_unique<expressions::ExpressionMemoryPool>();
    auto* expression =
        convert_expression(parsed_expression, math_function_list, *pool);
    return expressions::ExpressionPtr(expression, std::move(pool));
}

}  // namespace func_sketch::parser
