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
 * \brief Implementation of ConstantExpression structure.
 */
#include "func_sketch/expressions/constant_expression.h"

#include <fmt/format.h>

auto fmt::formatter<func_sketch::expressions::ConstantExpression>::format(
    const func_sketch::expressions::ConstantExpression& value,
    format_context& context) const -> format_context::iterator {
    return fmt::formatter<func_sketch::Real>::format(value.value, context);
}
