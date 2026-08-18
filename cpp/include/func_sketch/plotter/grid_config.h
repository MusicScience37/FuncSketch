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
 * \brief Definition of GridConfig class.
 */
#pragma once

#include "func_sketch/plotter/rgb_color.h"

namespace func_sketch::plotter {

//! Default line width of grid lines in pixels.
constexpr int default_grid_line_width = 1;

//! Default line width of the grid line at zero in pixels.
constexpr int default_zero_line_width = 2;

//! Default color of grid lines.
constexpr auto default_grid_color = RGBColor{.r = 0xC8, .g = 0xC8, .b = 0xC8};

/*!
 * \brief Class of configurations of a grid.
 */
class GridConfig {
public:
    /*!
     * \brief Constructor.
     */
    GridConfig() = default;

    /*!
     * \brief Set the line width of grid lines in pixels.
     *
     * \param[in] value Line width of grid lines in pixels.
     * \return Reference to this object.
     */
    GridConfig& line_width(int value);

    /*!
     * \brief Set the line width of the grid line at zero in pixels.
     *
     * \param[in] value Line width of the grid line at zero in pixels.
     * \return Reference to this object.
     */
    GridConfig& zero_line_width(int value);

    /*!
     * \brief Set the color of grid lines.
     *
     * \param[in] value Color of grid lines.
     * \return Reference to this object.
     */
    GridConfig& color(const RGBColor& value);

    /*!
     * \brief Get the line width of grid lines in pixels.
     *
     * \return Line width of grid lines in pixels.
     */
    [[nodiscard]] int line_width() const noexcept;

    /*!
     * \brief Get the line width of the grid line at zero in pixels.
     *
     * \return Line width of the grid line at zero in pixels.
     */
    [[nodiscard]] int zero_line_width() const noexcept;

    /*!
     * \brief Get the color of grid lines.
     *
     * \return Color of grid lines.
     */
    [[nodiscard]] const RGBColor& color() const noexcept;

private:
    //! Line width of grid lines in pixels.
    int line_width_{default_grid_line_width};

    //! Line width of the grid line at zero in pixels.
    int zero_line_width_{default_zero_line_width};

    //! Color of grid lines.
    RGBColor color_{default_grid_color};
};

}  // namespace func_sketch::plotter
