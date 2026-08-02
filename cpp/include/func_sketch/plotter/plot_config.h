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
 * \brief Definition of PlotConfig class.
 */
#pragma once

#include "func_sketch/plotter/rgb_color.h"

namespace func_sketch::plotter {

// TODO Tune these values

//! Default margins in pixels.
constexpr int default_margins = 15;

//! Default font size of tick labels in pixels.
constexpr int default_tick_label_font_size = 12;

//! Default line width of axes in pixels.
constexpr int default_axes_line_width = 3;

//! Default line width of grid lines in pixels.
constexpr int default_grid_line_width = 3;

//! Default line width of curves in pixels.
constexpr int default_curve_line_width = 3;

//! Default color of axes.
constexpr auto default_axes_color = RGBColor{.r = 0, .g = 0, .b = 0};

//! Default color of grid lines.
constexpr auto default_grid_color = RGBColor{.r = 200, .g = 200, .b = 200};

/*!
 * \brief Class of configurations of a plot.
 */
class PlotConfig {
public:
    /*!
     * \brief Constructor.
     */
    PlotConfig() = default;

    /*!
     * \brief Set the left margin of plots in pixels.
     *
     * \param[in] value Left margin of plots in pixels.
     * \return Reference to this object.
     */
    PlotConfig& left_margin(int value);

    /*!
     * \brief Set the right margin of plots in pixels.
     *
     * \param[in] value Right margin of plots in pixels.
     * \return Reference to this object.
     */
    PlotConfig& right_margin(int value);

    /*!
     * \brief Set the top margin of plots in pixels.
     *
     * \param[in] value Top margin of plots in pixels.
     * \return Reference to this object.
     */
    PlotConfig& top_margin(int value);

    /*!
     * \brief Set the bottom margin of plots in pixels.
     *
     * \param[in] value Bottom margin of plots in pixels.
     * \return Reference to this object.
     */
    PlotConfig& bottom_margin(int value);

    /*!
     * \brief Set the font size of tick labels in pixels.
     *
     * \param[in] value Font size of tick labels in pixels.
     * \return Reference to this object.
     */
    PlotConfig& tick_label_font_size(int value);

    /*!
     * \brief Set the line width of axes in pixels.
     *
     * \param[in] value Line width of axes in pixels.
     * \return Reference to this object.
     */
    PlotConfig& axes_line_width(int value);

    /*!
     * \brief Set the line width of grid lines in pixels.
     *
     * \param[in] value Line width of grid lines in pixels.
     * \return Reference to this object.
     */
    PlotConfig& grid_line_width(int value);

    /*!
     * \brief Set the line width of curves in pixels.
     *
     * \param[in] value Line width of curves in pixels.
     * \return Reference to this object.
     */
    PlotConfig& curve_line_width(int value);

    /*!
     * \brief Set the color of axes.
     *
     * \param[in] value Color of axes.
     * \return Reference to this object.
     */
    PlotConfig& axes_color(const RGBColor& value);

    /*!
     * \brief Set the color of grid lines.
     *
     * \param[in] value Color of grid lines.
     * \return Reference to this object.
     */
    PlotConfig& grid_color(const RGBColor& value);

    /*!
     * \brief Get the left margin of plots in pixels.
     *
     * \return Left margin of plots in pixels.
     */
    [[nodiscard]] int left_margin() const noexcept;

    /*!
     * \brief Get the right margin of plots in pixels.
     *
     * \return Right margin of plots in pixels.
     */
    [[nodiscard]] int right_margin() const noexcept;

    /*!
     * \brief Get the top margin of plots in pixels.
     *
     * \return Top margin of plots in pixels.
     */
    [[nodiscard]] int top_margin() const noexcept;

    /*!
     * \brief Get the bottom margin of plots in pixels.
     *
     * \return Bottom margin of plots in pixels.
     */
    [[nodiscard]] int bottom_margin() const noexcept;

    /*!
     * \brief Get the font size of tick labels in pixels.
     *
     * \return Font size of tick labels in pixels.
     */
    [[nodiscard]] int tick_label_font_size() const noexcept;

    /*!
     * \brief Get the line width of axes in pixels.
     *
     * \return Line width of axes in pixels.
     */
    [[nodiscard]] int axes_line_width() const noexcept;

    /*!
     * \brief Get the line width of grid lines in pixels.
     *
     * \return Line width of grid lines in pixels.
     */
    [[nodiscard]] int grid_line_width() const noexcept;

    /*!
     * \brief Get the line width of curves in pixels.
     *
     * \return Line width of curves in pixels.
     */
    [[nodiscard]] int curve_line_width() const noexcept;

    /*!
     * \brief Get the color of axes.
     *
     * \return Color of axes.
     */
    [[nodiscard]] const RGBColor& axes_color() const noexcept;

    /*!
     * \brief Get the color of grid lines.
     *
     * \return Color of grid lines.
     */
    [[nodiscard]] const RGBColor& grid_color() const noexcept;

private:
    //! Left margin of plots in pixels.
    int left_margin_{default_margins};

    //! Right margin of plots in pixels.
    int right_margin_{default_margins};

    //! Top margin of plots in pixels.
    int top_margin_{default_margins};

    //! Bottom margin of plots in pixels.
    int bottom_margin_{default_margins};

    //! Font size of tick labels in pixels.
    int tick_label_font_size_{default_tick_label_font_size};

    //! Line width of axes in pixels.
    int axes_line_width_{default_axes_line_width};

    //! Line width of grid lines in pixels.
    int grid_line_width_{default_grid_line_width};

    //! Line width of curves in pixels.
    int curve_line_width_{default_curve_line_width};

    //! Color of axes.
    RGBColor axes_color_{default_axes_color};

    //! Color of grid lines.
    RGBColor grid_color_{default_grid_color};
};

}  // namespace func_sketch::plotter
