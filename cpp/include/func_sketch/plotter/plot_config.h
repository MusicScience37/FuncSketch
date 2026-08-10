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

#include <cstddef>

#include "func_sketch/plotter/rgb_color.h"

namespace func_sketch::plotter {

// TODO Tune these values

//! Default margins in pixels.
constexpr int default_margins = 40;

//! Default font size of tick labels in pixels.
constexpr int default_tick_label_font_size = 11;

//! Default line width of axes in pixels.
constexpr int default_axes_line_width = 1;

//! Default line width of grid lines in pixels.
constexpr int default_grid_line_width = 1;

//! Default line width of curves in pixels.
constexpr int default_curve_line_width = 1;

//! Default color of background.
constexpr auto default_background_color =
    RGBColor{.r = 255, .g = 255, .b = 255};

//! Default color of axes.
constexpr auto default_axes_color = RGBColor{.r = 0x24, .g = 0x24, .b = 0x24};

//! Default color of grid lines.
constexpr auto default_grid_color = RGBColor{.r = 0xC8, .g = 0xC8, .b = 0xC8};

//! Default number of points to sample for each function.
constexpr int default_num_sample_points =
    100;  // TODO Remove this value after implementing adaptive sampling.

//! Default number of points to sample initially in adaptive sampling.
constexpr std::size_t default_initial_num_sample_points = 110;

//! Default maximum number of points to sample in adaptive sampling.
constexpr std::size_t default_max_num_sample_points = 2000;

//! Maximum value of the maximum number of points to sample in adaptive sampling for safety limit of memory usage.
constexpr std::size_t max_max_num_sample_points = 10000;

//! Default threshold of the change in coordinates of sample points relative to the plot range in adaptive sampling.
constexpr double default_max_coordinate_change_rate = 0.01;

//! Default threshold of the change in slope normalized by the plot range in adaptive sampling.
constexpr double default_slope_change_threshold = 0.1;

//! Default minimum rate of parameter change in adaptive sampling.
constexpr double default_min_param_change_rate = 0.001;

//! Minimum value of the minimum rate of parameter change in adaptive sampling for safety limit of memory usage.
constexpr double min_min_param_change_rate = 1e-4;

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
     * \brief Set the color of background.
     *
     * \param[in] value Color of background.
     * \return Reference to this object.
     */
    PlotConfig& background_color(const RGBColor& value);

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
     * \brief Set the number of points to sample for each function.
     *
     * \param[in] value Number of points to sample for each function.
     * \return Reference to this object.
     */
    PlotConfig& num_sample_points(int value);

    /*!
     * \brief Set the number of points to sample initially in adaptive
     * sampling.
     *
     * \param[in] value Number of points to sample initially in adaptive
     * sampling.
     * \return Reference to this object.
     */
    PlotConfig& initial_num_sample_points(std::size_t value);

    /*!
     * \brief Set the maximum number of points to sample in adaptive
     * sampling.
     *
     * \param[in] value Maximum number of points to sample in adaptive
     * sampling.
     * \return Reference to this object.
     *
     * \note This value should be larger than initial_num_sample_points.
     * Otherwise, this configuration has no effect.
     * \note This value is limited to max_max_num_sample_points for safety limit
     * of memory usage.
     */
    PlotConfig& max_num_sample_points(std::size_t value);

    /*!
     * \brief Set the threshold of the change in coordinates of sample points
     * relative to the plot range in adaptive sampling.
     *
     * \param[in] value Threshold of the change in coordinates of sample
     * points relative to the plot range in adaptive sampling.
     * \return Reference to this object.
     */
    PlotConfig& max_coordinate_change_rate(double value);

    /*!
     * \brief Set the threshold of the change in slope normalized by the plot
     * range in adaptive sampling.
     *
     * \param[in] value Threshold of the change in slope normalized by the
     * plot range in adaptive sampling.
     * \return Reference to this object.
     */
    PlotConfig& slope_change_threshold(double value);

    /*!
     * \brief Set the minimum rate of parameter change in adaptive sampling.
     *
     * \param[in] value Minimum rate of parameter change in adaptive
     * sampling.
     * \return Reference to this object.
     *
     * \note This value is limited to min_min_param_change_rate for safety limit
     * of memory usage.
     */
    PlotConfig& min_param_change_rate(double value);

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
     * \brief Get the color of background.
     *
     * \return Color of background.
     */
    [[nodiscard]] const RGBColor& background_color() const noexcept;

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

    /*!
     * \brief Get the number of points to sample for each function.
     *
     * \return Number of points to sample for each function.
     */
    [[nodiscard]] int num_sample_points() const noexcept;

    /*!
     * \brief Get the number of points to sample initially in adaptive
     * sampling.
     *
     * \return Number of points to sample initially in adaptive sampling.
     */
    [[nodiscard]] std::size_t initial_num_sample_points() const noexcept;

    /*!
     * \brief Get the maximum number of points to sample in adaptive
     * sampling.
     *
     * \return Maximum number of points to sample in adaptive sampling.
     */
    [[nodiscard]] std::size_t max_num_sample_points() const noexcept;

    /*!
     * \brief Get the threshold of the change in coordinates of sample points
     * relative to the plot range in adaptive sampling.
     *
     * \return Threshold of the change in coordinates of sample points
     * relative to the plot range in adaptive sampling.
     */
    [[nodiscard]] double max_coordinate_change_rate() const noexcept;

    /*!
     * \brief Get the threshold of the change in slope normalized by the plot
     * range in adaptive sampling.
     *
     * \return Threshold of the change in slope normalized by the plot range
     * in adaptive sampling.
     */
    [[nodiscard]] double slope_change_threshold() const noexcept;

    /*!
     * \brief Get the minimum rate of parameter change in adaptive sampling.
     *
     * \return Minimum rate of parameter change in adaptive sampling.
     */
    [[nodiscard]] double min_param_change_rate() const noexcept;

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

    //! Color of background.
    RGBColor background_color_{default_background_color};

    //! Color of axes.
    RGBColor axes_color_{default_axes_color};

    //! Color of grid lines.
    RGBColor grid_color_{default_grid_color};

    //! Number of points to sample for each function.
    int num_sample_points_{default_num_sample_points};

    //! Number of points to sample initially in adaptive sampling.
    std::size_t initial_num_sample_points_{default_initial_num_sample_points};

    //! Maximum number of points to sample in adaptive sampling.
    std::size_t max_num_sample_points_{default_max_num_sample_points};

    //! Threshold of the change in coordinates of sample points relative to
    //! the plot range in adaptive sampling.
    double max_coordinate_change_rate_{default_max_coordinate_change_rate};

    //! Threshold of the change in slope normalized by the plot range in
    //! adaptive sampling.
    double slope_change_threshold_{default_slope_change_threshold};

    //! Minimum rate of parameter change in adaptive sampling.
    double min_param_change_rate_{default_min_param_change_rate};
};

}  // namespace func_sketch::plotter
