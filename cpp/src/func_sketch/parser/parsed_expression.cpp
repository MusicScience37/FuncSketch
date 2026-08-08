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
 * \brief Implementation of ParsedExpression structure.
 */
#include "func_sketch/parser/parsed_expression.h"

#include <type_traits>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include "func_sketch/common_types.h"

// NOLINTNEXTLINE(*-static): API of an external library.
auto fmt::formatter<func_sketch::parser::ParsedConstant>::format(
    const func_sketch::parser::ParsedConstant& value,
    format_context& context) const -> format_context::iterator {
    return std::visit(
        [&context](const auto& actual_value) {
            if constexpr (std::is_same_v<std::decay_t<decltype(actual_value)>,
                              func_sketch::Real>) {
                // For testing purposes, we want to distinguish between 1.0 and
                // 1 in the output.
                return fmt::format_to(
                    context.out(), "Constant({:e})", actual_value);
            } else {
                return fmt::format_to(
                    context.out(), "Constant({})", actual_value);
            }
        },
        value.value);
}

// NOLINTNEXTLINE(*-static): API of an external library.
auto fmt::formatter<func_sketch::parser::ParsedIdentifier>::format(
    const func_sketch::parser::ParsedIdentifier& value,
    format_context& context) const -> format_context::iterator {
    return fmt::format_to(context.out(), "Identifier({})", value.name);
}

// NOLINTNEXTLINE(*-static): API of an external library.
auto fmt::formatter<func_sketch::parser::ParsedExpression>::format(
    const func_sketch::parser::ParsedExpression& value,
    format_context& context) const -> format_context::iterator {
    return boost::apply_visitor(
        [&context](const auto& concrete_value) {
            return fmt::format_to(context.out(), "{}", concrete_value);
        },
        value);
}

// NOLINTNEXTLINE(*-static): API of an external library.
auto fmt::formatter<func_sketch::parser::ParsedFunctionCallExpression>::format(
    const func_sketch::parser::ParsedFunctionCallExpression& value,
    format_context& context) const -> format_context::iterator {
    return fmt::format_to(context.out(), "FunctionCall({}, {})",
        value.function_name, fmt::join(value.arguments, ", "));
}

// NOLINTNEXTLINE(*-static): API of an external library.
auto fmt::formatter<func_sketch::parser::ParsedUnaryExpression>::format(
    const func_sketch::parser::ParsedUnaryExpression& value,
    format_context& context) const -> format_context::iterator {
    return fmt::format_to(
        context.out(), "Unary({}, {})", value.operator_str, value.operand);
}

// NOLINTNEXTLINE(*-static): API of an external library.
auto fmt::formatter<func_sketch::parser::ParsedBinaryExpression>::format(
    const func_sketch::parser::ParsedBinaryExpression& value,
    format_context& context) const -> format_context::iterator {
    return fmt::format_to(context.out(), "Binary({}, {}, {})",
        value.operator_str, value.left_operand, value.right_operand);
}
