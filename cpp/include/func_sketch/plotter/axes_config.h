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
 * \brief Definition of AxesConfig class.
 */
#pragma once

#include <cstddef>
#include <string>
#include <string_view>

#include "func_sketch/plotter/rgb_color.h"

namespace func_sketch::plotter {

//! Default title of x-axis.
constexpr std::string_view default_x_axis_title = "x";

//! Default title of y-axis.
constexpr std::string_view default_y_axis_title = "y";

//! Default font size of titles of axes in pixels.
constexpr int default_axes_title_font_size = 11;

//! Default font size of tick labels in pixels.
constexpr int default_tick_label_font_size = 11;

//! Default margin of tick labels in pixels.
constexpr int default_tick_label_margin = 8;

//! Default line width of axes in pixels.
constexpr int default_axes_line_width = 1;

//! Default color of axes.
constexpr auto default_axes_color = RGBColor{.r = 0x24, .g = 0x24, .b = 0x24};

//! Default number of pixels per tick in the x-axis.
constexpr std::size_t default_num_pixels_per_tick_in_x_axis = 120;

//! Default number of pixels per tick in the y-axis.
constexpr std::size_t default_num_pixels_per_tick_in_y_axis = 90;

/*!
 * \brief Class of configurations of axes.
 */
class AxesConfig {
public:
    /*!
     * \brief Constructor.
     */
    AxesConfig() = default;

    /*!
     * \brief Set the title of x-axis.
     *
     * \param[in] value Title of x-axis.
     * \return Reference to this object.
     *
     * \note Empty string means no title.
     */
    AxesConfig& x_axis_title(std::string value);

    /*!
     * \brief Set the title of y-axis.
     *
     * \param[in] value Title of y-axis.
     * \return Reference to this object.
     *
     * \note Empty string means no title.
     */
    AxesConfig& y_axis_title(std::string value);

    /*!
     * \brief Set the font size of titles of axes in pixels.
     *
     * \param[in] value Font size of titles of axes in pixels.
     * \return Reference to this object.
     */
    AxesConfig& axes_title_font_size(int value);

    /*!
     * \brief Set the font size of tick labels in pixels.
     *
     * \param[in] value Font size of tick labels in pixels.
     * \return Reference to this object.
     */
    AxesConfig& tick_label_font_size(int value);

    /*!
     * \brief Set the margin of tick labels in pixels.
     *
     * \param[in] value Margin of tick labels in pixels.
     * \return Reference to this object.
     */
    AxesConfig& tick_label_margin(int value);

    /*!
     * \brief Set the line width of axes in pixels.
     *
     * \param[in] value Line width of axes in pixels.
     * \return Reference to this object.
     */
    AxesConfig& line_width(int value);

    /*!
     * \brief Set the color of axes.
     *
     * \param[in] value Color of axes.
     * \return Reference to this object.
     */
    AxesConfig& color(const RGBColor& value);

    /*!
     * \brief Set the number of pixels per tick in the x-axis.
     *
     * \param[in] value Number of pixels per tick in the x-axis.
     * \return Reference to this object.
     */
    AxesConfig& num_pixels_per_tick_in_x_axis(std::size_t value);

    /*!
     * \brief Set the number of pixels per tick in the y-axis.
     *
     * \param[in] value Number of pixels per tick in the y-axis.
     * \return Reference to this object.
     */
    AxesConfig& num_pixels_per_tick_in_y_axis(std::size_t value);

    /*!
     * \brief Get the title of x-axis.
     *
     * \return Title of x-axis.
     *
     * \note Empty string means no title.
     */
    [[nodiscard]] const std::string& x_axis_title() const noexcept;

    /*!
     * \brief Get the title of y-axis.
     *
     * \return Title of y-axis.
     *
     * \note Empty string means no title.
     */
    [[nodiscard]] const std::string& y_axis_title() const noexcept;

    /*!
     * \brief Get the font size of titles of axes in pixels.
     *
     * \return Font size of titles of axes in pixels.
     */
    [[nodiscard]] int axes_title_font_size() const noexcept;

    /*!
     * \brief Get the font size of tick labels in pixels.
     *
     * \return Font size of tick labels in pixels.
     */
    [[nodiscard]] int tick_label_font_size() const noexcept;

    /*!
     * \brief Get the margin of tick labels in pixels.
     *
     * \return Margin of tick labels in pixels.
     */
    [[nodiscard]] int tick_label_margin() const noexcept;

    /*!
     * \brief Get the line width of axes in pixels.
     *
     * \return Line width of axes in pixels.
     */
    [[nodiscard]] int line_width() const noexcept;

    /*!
     * \brief Get the color of axes.
     *
     * \return Color of axes.
     */
    [[nodiscard]] const RGBColor& color() const noexcept;

    /*!
     * \brief Get the number of pixels per tick in the x-axis.
     *
     * \return Number of pixels per tick in the x-axis.
     */
    [[nodiscard]] std::size_t num_pixels_per_tick_in_x_axis() const noexcept;

    /*!
     * \brief Get the number of pixels per tick in the y-axis.
     *
     * \return Number of pixels per tick in the y-axis.
     */
    [[nodiscard]] std::size_t num_pixels_per_tick_in_y_axis() const noexcept;

private:
    //! Title of x-axis.
    std::string x_axis_title_{default_x_axis_title};

    //! Title of y-axis.
    std::string y_axis_title_{default_y_axis_title};

    //! Font size of titles of axes in pixels.
    int axes_title_font_size_{default_axes_title_font_size};

    //! Font size of tick labels in pixels.
    int tick_label_font_size_{default_tick_label_font_size};

    //! Margin of tick labels in pixels.
    int tick_label_margin_{default_tick_label_margin};

    //! Line width of axes in pixels.
    int line_width_{default_axes_line_width};

    //! Color of axes.
    RGBColor color_{default_axes_color};

    //! Number of pixels per tick in the x-axis.
    std::size_t num_pixels_per_tick_in_x_axis_{
        default_num_pixels_per_tick_in_x_axis};

    //! Number of pixels per tick in the y-axis.
    std::size_t num_pixels_per_tick_in_y_axis_{
        default_num_pixels_per_tick_in_y_axis};
};

}  // namespace func_sketch::plotter
