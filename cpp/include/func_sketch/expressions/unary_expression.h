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
 * \brief Definition of UnaryExpression structure.
 */
#pragma once

#include <fmt/base.h>

#include "func_sketch/expressions/expression_decl.h"
#include "func_sketch/math/unary_operator.h"

namespace func_sketch::expressions {

/*!
 * \brief Struct of unary expressions.
 */
struct UnaryExpression {
    //! Target expression.
    Expression* target{};

    //! Operator.
    math::UnaryOperator operator_object;
};

}  // namespace func_sketch::expressions

/*!
 * \brief Specialization of fmt::formatter for
 * func_sketch::expressions::UnaryExpression.
 */
template <>
struct fmt::formatter<func_sketch::expressions::UnaryExpression>
    : fmt::formatter<string_view> {
    /*!
     * \brief Format a value.
     *
     * \param[in] value Value to format.
     * \param[in] context Format context.
     * \return Iterator to the end of the formatted output.
     */
    auto format(const func_sketch::expressions::UnaryExpression& value,
        format_context& context) const -> format_context::iterator;
};
