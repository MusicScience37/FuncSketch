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
 * \brief Definition of ParsedExpression structure.
 */
#pragma once

#include <string>

#include <boost/variant.hpp>
#include <fmt/base.h>

#include "func_sketch/common_types.h"

namespace func_sketch::parser {

/*!
 * \brief Struct of parsed literals.
 */
struct ParsedLiteral {
    //! Value.
    Number value;
};

/*!
 * \brief Struct of parsed identifiers.
 */
struct ParsedIdentifier {
    //! Name.
    std::string name;
};

struct ParsedFunctionCallExpression;
struct ParsedUnaryExpression;
struct ParsedBinaryExpression;

/*!
 * \brief Variant of parsed expressions.
 */
using ParsedExpression = boost::variant<ParsedLiteral, ParsedIdentifier,
    boost::recursive_wrapper<ParsedFunctionCallExpression>,
    boost::recursive_wrapper<ParsedUnaryExpression>,
    boost::recursive_wrapper<ParsedBinaryExpression>>;

/*!
 * \brief Struct of parsed function call expressions.
 */
struct ParsedFunctionCallExpression {
    //! Function name.
    ParsedIdentifier function_name;

    //! Arguments.
    std::vector<ParsedExpression> arguments;
};

/*!
 * \brief Struct of parsed unary expressions.
 */
struct ParsedUnaryExpression {
    //! Operator.
    std::string operator_str;

    //! Operand.
    ParsedExpression operand;
};

/*!
 * \brief Struct of parsed binary expressions.
 */
struct ParsedBinaryExpression {
    //! Operator.
    std::string operator_str;

    //! Left operand.
    ParsedExpression left_operand;

    //! Right operand.
    ParsedExpression right_operand;
};

}  // namespace func_sketch::parser

// Implement fmt::formatter specialization for testing.

/*!
 * \brief Specialization of fmt::formatter for
 * func_sketch::parser::ParsedLiteral.
 */
template <>
struct fmt::formatter<func_sketch::parser::ParsedLiteral>
    : fmt::formatter<string_view> {
    /*!
     * \brief Format a value.
     *
     * \param[in] value Value to format.
     * \param[in] context Format context.
     * \return Iterator to the end of the formatted output.
     */
    auto format(const func_sketch::parser::ParsedLiteral& value,
        format_context& context) const -> format_context::iterator;
};

/*!
 * \brief Specialization of fmt::formatter for
 * func_sketch::parser::ParsedIdentifier.
 */
template <>
struct fmt::formatter<func_sketch::parser::ParsedIdentifier>
    : fmt::formatter<string_view> {
    /*!
     * \brief Format a value.
     *
     * \param[in] value Value to format.
     * \param[in] context Format context.
     * \return Iterator to the end of the formatted output.
     */
    auto format(const func_sketch::parser::ParsedIdentifier& value,
        format_context& context) const -> format_context::iterator;
};

/*!
 * \brief Specialization of fmt::formatter for
 * func_sketch::parser::ParsedExpression.
 */
template <>
struct fmt::formatter<func_sketch::parser::ParsedExpression>
    : fmt::formatter<string_view> {
    /*!
     * \brief Format a value.
     *
     * \param[in] value Value to format.
     * \param[in] context Format context.
     * \return Iterator to the end of the formatted output.
     */
    auto format(const func_sketch::parser::ParsedExpression& value,
        format_context& context) const -> format_context::iterator;
};

/*!
 * \brief Specialization of fmt::formatter for
 * func_sketch::parser::ParsedFunctionCallExpression.
 */
template <>
struct fmt::formatter<func_sketch::parser::ParsedFunctionCallExpression>
    : fmt::formatter<string_view> {
    /*!
     * \brief Format a value.
     *
     * \param[in] value Value to format.
     * \param[in] context Format context.
     * \return Iterator to the end of the formatted output.
     */
    auto format(const func_sketch::parser::ParsedFunctionCallExpression& value,
        format_context& context) const -> format_context::iterator;
};

/*!
 * \brief Specialization of fmt::formatter for
 * func_sketch::parser::ParsedUnaryExpression.
 */
template <>
struct fmt::formatter<func_sketch::parser::ParsedUnaryExpression>
    : fmt::formatter<string_view> {
    /*!
     * \brief Format a value.
     *
     * \param[in] value Value to format.
     * \param[in] context Format context.
     * \return Iterator to the end of the formatted output.
     */
    auto format(const func_sketch::parser::ParsedUnaryExpression& value,
        format_context& context) const -> format_context::iterator;
};

/*!
 * \brief Specialization of fmt::formatter for
 * func_sketch::parser::ParsedBinaryExpression.
 */
template <>
struct fmt::formatter<func_sketch::parser::ParsedBinaryExpression>
    : fmt::formatter<string_view> {
    /*!
     * \brief Format a value.
     *
     * \param[in] value Value to format.
     * \param[in] context Format context.
     * \return Iterator to the end of the formatted output.
     */
    auto format(const func_sketch::parser::ParsedBinaryExpression& value,
        format_context& context) const -> format_context::iterator;
};
