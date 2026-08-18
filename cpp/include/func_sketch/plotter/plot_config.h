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

#include "func_sketch/plotter/axes_config.h"
#include "func_sketch/plotter/grid_config.h"
#include "func_sketch/plotter/margin.h"
#include "func_sketch/plotter/rgb_color.h"

namespace func_sketch::plotter {

// TODO Tune these values

//! Default line width of curves in pixels.
constexpr int default_curve_line_width = 1;

//! Default color of background.
constexpr auto default_background_color =
    RGBColor{.r = 255, .g = 255, .b = 255};

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
     * \brief Access the configuration of margins.
     *
     * \return Reference to the configuration of margins.
     */
    [[nodiscard]] Margin& margin() noexcept;

    /*!
     * \brief Get the configuration of margins.
     *
     * \return Reference to the configuration of margins.
     */
    [[nodiscard]] const Margin& margin() const noexcept;

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
    //! Configuration of margins.
    Margin margin_;

    //! Configuration of axes.
    AxesConfig axes_;

    //! Configuration of the grid.
    GridConfig grid_;

    //! Line width of curves in pixels.
    int curve_line_width_{default_curve_line_width};

    //! Color of background.
    RGBColor background_color_{default_background_color};

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
