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
 * \brief Definition of PlotRange class.
 */
#pragma once

#include <utility>

#include <fmt/base.h>

#include "func_sketch/plotter/point.h"

namespace func_sketch::plotter {

/*!
 * \brief Class of a range of a plot.
 */
class PlotRange {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] x_range X range.
     * \param[in] y_range Y range.
     */
    PlotRange(const std::pair<double, double>& x_range,
        const std::pair<double, double>& y_range);

    /*!
     * \brief Get X range.
     *
     * \return X range.
     */
    [[nodiscard]] auto x_range() const noexcept -> std::pair<double, double>;

    /*!
     * \brief Get Y range.
     *
     * \return Y range.
     */
    [[nodiscard]] auto y_range() const noexcept -> std::pair<double, double>;

    /*!
     * \brief Check if a point is in the range.
     *
     * \param[in] point Point to check.
     * \retval true The point is in the range.
     * \retval false The point is not in the range.
     */
    [[nodiscard]] bool contains(const Point& point) const noexcept;

    /*!
     * \brief Zoom this plot range.
     *
     * \param[in] center Center point for zooming. This point won't move after
     * zooming.
     * \param[in] factor Factor for zooming. Values greater than 1 will zoom in,
     * and values between 0 and 1 will zoom out.
     */
    void zoom(const Point& center, double factor);

private:
    //! X range.
    std::pair<double, double> x_range_;

    //! Y range.
    std::pair<double, double> y_range_;
};

}  // namespace func_sketch::plotter

/*!
 * \brief Specialization of fmt::formatter for
 * func_sketch::plotter::PlotRange.
 */
template <>
struct fmt::formatter<func_sketch::plotter::PlotRange>
    : fmt::formatter<string_view> {
    /*!
     * \brief Format a value.
     *
     * \param[in] value Value to format.
     * \param[in] context Format context.
     * \return Iterator to the end of the formatted output.
     */
    auto format(const func_sketch::plotter::PlotRange& value,
        format_context& context) const -> format_context::iterator;
};
