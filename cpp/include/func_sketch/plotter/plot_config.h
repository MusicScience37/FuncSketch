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

#include <string>
#include <string_view>

#include "func_sketch/plotter/axes_config.h"
#include "func_sketch/plotter/grid_config.h"
#include "func_sketch/plotter/margin.h"
#include "func_sketch/plotter/rgb_color.h"
#include "func_sketch/plotter/sampling_config.h"

namespace func_sketch::plotter {

//! Default title of the plot. (No title.)
constexpr std::string_view default_plot_title;

//! Default font size of the title of the plot.
constexpr int default_plot_title_font_size = 20;

//! Default color of the title of the plot.
constexpr auto default_plot_title_color = default_axes_color;

//! Default margin for the title of the plot.
constexpr int default_plot_title_margin = 20;

//! Default minimum left margin of the plot region in pixels.
constexpr int default_min_plot_left_margin = 60;

//! Default minimum right margin of the plot region in pixels.
constexpr int default_min_plot_right_margin = 60;

//! Default minimum top margin of the plot region in pixels.
constexpr int default_min_plot_top_margin = 50;

//! Default minimum bottom margin of the plot region in pixels.
constexpr int default_min_plot_bottom_margin = 50;

//! Default base margin of plots in pixels.
constexpr int default_base_margin = 5;

//! Default line width of curves in pixels.
constexpr int default_curve_line_width = 1;

//! Default color of background.
constexpr auto default_background_color =
    RGBColor{.r = 255, .g = 255, .b = 255};

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
     * \brief Access the configuration of the minimum margins of the plot
     * region.
     *
     * \return Reference to the configuration of the minimum margins of the
     * plot region.
     */
    [[nodiscard]] Margin& min_plot_margin() noexcept;

    /*!
     * \brief Get the configuration of the minimum margins of the plot
     * region.
     *
     * \return Reference to the configuration of the minimum margins of the
     * plot region.
     */
    [[nodiscard]] const Margin& min_plot_margin() const noexcept;

    /*!
     * \brief Access the configuration of the base margin.
     *
     * \return Reference to the configuration of the base margin.
     */
    [[nodiscard]] Margin& base_margin() noexcept;

    /*!
     * \brief Get the configuration of the base margin.
     *
     * \return Reference to the configuration of the base margin.
     */
    [[nodiscard]] const Margin& base_margin() const noexcept;

    /*!
     * \brief Access the configuration of axes.
     *
     * \return Reference to the configuration of axes.
     */
    [[nodiscard]] AxesConfig& axes() noexcept;

    /*!
     * \brief Get the configuration of axes.
     *
     * \return Reference to the configuration of axes.
     */
    [[nodiscard]] const AxesConfig& axes() const noexcept;

    /*!
     * \brief Access the configuration of the grid.
     *
     * \return Reference to the configuration of the grid.
     */
    [[nodiscard]] GridConfig& grid() noexcept;

    /*!
     * \brief Get the configuration of the grid.
     *
     * \return Reference to the configuration of the grid.
     */
    [[nodiscard]] const GridConfig& grid() const noexcept;

    /*!
     * \brief Access the configuration of sampling.
     *
     * \return Reference to the configuration of sampling.
     */
    [[nodiscard]] SamplingConfig& sampling() noexcept;

    /*!
     * \brief Get the configuration of sampling.
     *
     * \return Reference to the configuration of sampling.
     */
    [[nodiscard]] const SamplingConfig& sampling() const noexcept;

    /*!
     * \brief Set the title of the plot.
     *
     * \param[in] value Title of the plot.
     * \return Reference to this object.
     *
     * \note Empty string means no title.
     */
    PlotConfig& plot_title(std::string value);

    /*!
     * \brief Set the font size of the title of the plot.
     *
     * \param[in] value Font size of the title of the plot.
     * \return Reference to this object.
     */
    PlotConfig& plot_title_font_size(int value);

    /*!
     * \brief Set the color of the title of the plot.
     *
     * \param[in] value Color of the title of the plot.
     * \return Reference to this object.
     */
    PlotConfig& plot_title_color(const RGBColor& value);

    /*!
     * \brief Set the margin for the title of the plot.
     *
     * \param[in] value Margin for the title of the plot.
     * \return Reference to this object.
     */
    PlotConfig& plot_title_margin(int value);

    /*!
     * \brief Set the line width of curves in pixels.
     *
     * \param[in] value Line width of curves in pixels.
     * \return Reference to this object.
     */
    PlotConfig& curve_line_width(int value);

    /*!
     * \brief Set the color of background.
     *
     * \param[in] value Color of background.
     * \return Reference to this object.
     */
    PlotConfig& background_color(const RGBColor& value);

    /*!
     * \brief Get the title of the plot.
     *
     * \return Title of the plot.
     *
     * \note Empty string means no title.
     */
    [[nodiscard]] const std::string& plot_title() const noexcept;

    /*!
     * \brief Get the font size of the title of the plot.
     *
     * \return Font size of the title of the plot.
     */
    [[nodiscard]] int plot_title_font_size() const noexcept;

    /*!
     * \brief Get the color of the title of the plot.
     *
     * \return Color of the title of the plot.
     */
    [[nodiscard]] const RGBColor& plot_title_color() const noexcept;

    /*!
     * \brief Get the margin for the title of the plot.
     *
     * \return Margin for the title of the plot.
     */
    [[nodiscard]] int plot_title_margin() const noexcept;

    /*!
     * \brief Get the line width of curves in pixels.
     *
     * \return Line width of curves in pixels.
     */
    [[nodiscard]] int curve_line_width() const noexcept;

    /*!
     * \brief Get the color of background.
     *
     * \return Color of background.
     */
    [[nodiscard]] const RGBColor& background_color() const noexcept;

private:
    //! Configuration of the minimum margins of the plot region.
    Margin min_plot_margin_{default_min_plot_left_margin,
        default_min_plot_right_margin, default_min_plot_top_margin,
        default_min_plot_bottom_margin};

    //! Configuration of the base margin.
    Margin base_margin_{default_base_margin, default_base_margin,
        default_base_margin, default_base_margin};

    //! Configuration of axes.
    AxesConfig axes_;

    //! Configuration of the grid.
    GridConfig grid_;

    //! Configuration of sampling.
    SamplingConfig sampling_;

    //! Title of the plot.
    std::string plot_title_{default_plot_title};

    //! Font size of the title of the plot.
    int plot_title_font_size_{default_plot_title_font_size};

    //! Color of the title of the plot.
    RGBColor plot_title_color_{default_plot_title_color};

    //! Margin for the title of the plot.
    int plot_title_margin_{default_plot_title_margin};

    //! Line width of curves in pixels.
    int curve_line_width_{default_curve_line_width};

    //! Color of background.
    RGBColor background_color_{default_background_color};
};

}  // namespace func_sketch::plotter
