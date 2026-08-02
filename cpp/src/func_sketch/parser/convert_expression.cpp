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
#include "func_sketch/math/unary_operators.h"

namespace func_sketch::parser {

/*!
 * \brief Convert parsed expression.
 *
 * \param[in] parsed_expression Parsed expression to convert.
 * \param[in] pool Memory pool to allocate expressions.
 * \return Converted expression.
 */
[[nodiscard]] expressions::Expression* convert_expression(
    const ParsedExpression& parsed_expression,
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
 * \param[in] pool Memory pool to allocate expressions.
 * \return Converted expression.
 */
[[nodiscard]] expressions::Expression* convert_expression(
    const ParsedFunctionCallExpression& parsed_expression,
    expressions::ExpressionMemoryPool& pool) {
    // TODO
    throw InvalidExpressionException("Function call is not implemented yet.");
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
 * \param[in] pool Memory pool to allocate expressions.
 * \return Converted expression.
 */
[[nodiscard]] expressions::Expression* convert_expression(
    const ParsedUnaryExpression& parsed_expression,
    expressions::ExpressionMemoryPool& pool) {
    return pool.create<expressions::UnaryExpression>(
        convert_expression(parsed_expression.operand, pool),
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
 * \param[in] pool Memory pool to allocate expressions.
 * \return Converted expression.
 */
[[nodiscard]] expressions::Expression* convert_expression(
    const ParsedBinaryExpression& parsed_expression,
    expressions::ExpressionMemoryPool& pool) {
    return pool.create<expressions::BinaryExpression>(
        convert_expression(parsed_expression.left_operand, pool),
        convert_expression(parsed_expression.right_operand, pool),
        get_binary_operator(parsed_expression.operator_str));
}

[[nodiscard]] expressions::Expression* convert_expression(
    const ParsedExpression& parsed_expression,
    expressions::ExpressionMemoryPool& pool) {
    return boost::apply_visitor(
        [&pool](const auto& concrete_expression) -> expressions::Expression* {
            return convert_expression(concrete_expression, pool);
        },
        parsed_expression);
}

[[nodiscard]] expressions::ExpressionPtr convert_expression(
    const ParsedExpression& parsed_expression) {
    auto pool = std::make_unique<expressions::ExpressionMemoryPool>();
    auto* expression = convert_expression(parsed_expression, *pool);
    return expressions::ExpressionPtr(expression, std::move(pool));
}

}  // namespace func_sketch::parser
