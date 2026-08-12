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
 * \brief Declaration of convert_expression function.
 */
#pragma once

#include "func_sketch/expressions/expression_ptr.h"
#include "func_sketch/math/constant_list.h"
#include "func_sketch/math/math_function_list.h"
#include "func_sketch/parser/parsed_expression.h"

namespace func_sketch::parser {

/*!
 * \brief Convert parsed expression.
 *
 * \param[in] parsed_expression Parsed expression to convert.
 * \param[in] math_function_list List of math functions.
 * \param[in] constant_list List of constants.
 * \return Converted expression.
 */
[[nodiscard]] expressions::ExpressionPtr convert_expression(
    const ParsedExpression& parsed_expression,
    const math::MathFunctionList& math_function_list,
    const math::ConstantList& constant_list);

}  // namespace func_sketch::parser
