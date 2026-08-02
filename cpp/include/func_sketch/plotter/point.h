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
 * \brief Definition of Point struct.
 */
#pragma once

#include <fmt/base.h>

namespace func_sketch::plotter {

/*!
 * \brief Struct of a point.
 */
struct Point {
    //! X coordinate.
    double x;

    //! Y coordinate.
    double y;
};

}  // namespace func_sketch::plotter

/*!
 * \brief Specialization of fmt::formatter for
 * func_sketch::plotter::Point.
 */
template <>
struct fmt::formatter<func_sketch::plotter::Point>
    : fmt::formatter<string_view> {
    /*!
     * \brief Format a value.
     *
     * \param[in] value Value to format.
     * \param[in] context Format context.
     * \return Iterator to the end of the formatted output.
     */
    auto format(const func_sketch::plotter::Point& value,
        format_context& context) const -> format_context::iterator;
};
