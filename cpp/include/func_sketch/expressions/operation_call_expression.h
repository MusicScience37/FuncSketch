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
 * \brief Definition of OperationCallExpression structure.
 */
#pragma once

#include <vector>

#include <fmt/base.h>

#include "func_sketch/expressions/expression_decl.h"
#include "func_sketch/expressions/math_operation.h"

namespace func_sketch::expressions {

/*!
 * \brief Struct of operation call expressions.
 */
struct OperationCallExpression {
    //! Arguments.
    std::vector<const Expression*> arguments;

    //! Operation.
    MathOperation operation;
};

}  // namespace func_sketch::expressions

/*!
 * \brief Specialization of fmt::formatter for
 * func_sketch::expressions::OperationCallExpression.
 */
template <>
struct fmt::formatter<func_sketch::expressions::OperationCallExpression>
    : fmt::formatter<string_view> {
    /*!
     * \brief Format a value.
     *
     * \param[in] value Value to format.
     * \param[in] context Format context.
     * \return Iterator to the end of the formatted output.
     */
    auto format(const func_sketch::expressions::OperationCallExpression& value,
        format_context& context) const -> format_context::iterator;
};
