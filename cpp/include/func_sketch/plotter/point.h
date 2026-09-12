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

    /*!
     * \brief Add two points.
     *
     * \param[in] left Left point.
     * \param[in] right Right point.
     * \return Sum of the two points.
     */
    friend Point operator+(const Point& left, const Point& right) {
        return Point{.x = left.x + right.x, .y = left.y + right.y};
    }

    /*!
     * \brief Subtract a point from another point.
     *
     * \param[in] left Left point.
     * \param[in] right Right point.
     * \return Difference of the two points.
     */
    friend Point operator-(const Point& left, const Point& right) {
        return Point{.x = left.x - right.x, .y = left.y - right.y};
    }
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
