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
 * \brief Definition of Expression class.
 */
#pragma once

#include <variant>

#include <fmt/base.h>

#include "func_sketch/expressions/binary_expression.h"
#include "func_sketch/expressions/constant_expression.h"
#include "func_sketch/expressions/expression_decl.h"  // IWYU pragma: keep
#include "func_sketch/expressions/parameter_expression.h"
#include "func_sketch/expressions/unary_expression.h"

namespace func_sketch::expressions {

/*!
 * \brief Class of expressions.
 *
 * \note This class must have a forward declaration to implement tree structures
 * of expressions. So this class is not a simple alias of std::variant.
 */
class Expression {
public:
    //! Type of the variant of expressions.
    using VariantType = std::variant<ConstantExpression, ParameterExpression,
        UnaryExpression, BinaryExpression>;

    /*!
     * \brief Constructor.
     *
     * \param[in] expression Expression.
     */
    explicit Expression(ConstantExpression expression)
        : expression_(expression) {}

    /*!
     * \brief Constructor.
     *
     * \param[in] expression Expression.
     */
    explicit Expression(ParameterExpression expression)
        : expression_(expression) {}

    /*!
     * \brief Constructor.
     *
     * \param[in] expression Expression.
     */
    explicit Expression(UnaryExpression expression) : expression_(expression) {}

    /*!
     * \brief Constructor.
     *
     * \param[in] expression Expression.
     */
    explicit Expression(BinaryExpression expression)
        : expression_(expression) {}

    /*!
     * \brief Get as a type.
     *
     * \tparam T Type.
     * \return Expression as the type.
     */
    template <typename T>
    [[nodiscard]] const T& as() const {
        return std::get<T>(expression_);
    }

    /*!
     * \brief Get the expression as variant.
     *
     * \return Expression as variant.
     */
    [[nodiscard]] const VariantType& as_variant() const { return expression_; }

private:
    //! Expression.
    VariantType expression_;
};

}  // namespace func_sketch::expressions

/*!
 * \brief Specialization of fmt::formatter for
 * func_sketch::expressions::Expression.
 */
template <>
struct fmt::formatter<func_sketch::expressions::Expression>
    : fmt::formatter<string_view> {
    /*!
     * \brief Format a value.
     *
     * \param[in] value Value to format.
     * \param[in] context Format context.
     * \return Iterator to the end of the formatted output.
     */
    auto format(const func_sketch::expressions::Expression& value,
        format_context& context) const -> format_context::iterator;
};
