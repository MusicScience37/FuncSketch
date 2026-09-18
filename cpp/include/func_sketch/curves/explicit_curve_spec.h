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
 * \brief Definition of ExplicitCurveSpec struct.
 */
#pragma once

#include <string>

#include <fmt/base.h>

#include "func_sketch/plotter/rgb_color.h"

namespace func_sketch::curves {

/*!
 * \brief Struct of specifications of curves with explicit functions.
 */
struct ExplicitCurveSpec {
    //! Name of the curve.
    std::string name;

    //! String of the function expression.
    std::string function_expression_str;

    //! Color.
    plotter::RGBColor color;
};

}  // namespace func_sketch::curves

/*!
 * \brief Specialization of fmt::formatter for
 * func_sketch::curves::ExplicitCurveSpec.
 */
template <>
struct fmt::formatter<func_sketch::curves::ExplicitCurveSpec>
    : fmt::formatter<string_view> {
    /*!
     * \brief Format a value.
     *
     * \param[in] value Value to format.
     * \param[in] context Format context.
     * \return Iterator to the end of the formatted output.
     */
    auto format(const func_sketch::curves::ExplicitCurveSpec& value,
        format_context& context) const -> format_context::iterator;
};
