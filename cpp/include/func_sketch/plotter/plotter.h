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
 * \brief Definition of Plotter class.
 */
#pragma once

#include "func_sketch/plotter/axis_ticks.h"
#include "func_sketch/plotter/image.h"
#include "func_sketch/plotter/margin.h"
#include "func_sketch/plotter/plot_config.h"
#include "func_sketch/plotter/plot_range.h"
#include "func_sketch/plotter/point.h"

namespace func_sketch::plotter {

//! Initial height of the image.
constexpr int initial_height = 600;

//! Initial width of the image.
constexpr int initial_width = 800;

/*!
 * \brief Class for plotting.
 *
 * \note This class assumes that the image is in RGB format,
 * not BGR format as in default of OpenCV.
 */
class Plotter {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] range Range of plots.
     * \param[in] config Configuration of plots.
     */
    Plotter(const PlotRange& range, const PlotConfig& config);

    /*!
     * \brief Set the range of plots.
     *
     * \param[in] value Range of plots.
     * \return Reference to this object.
     */
    Plotter& range(const PlotRange& value);

    /*!
     * \brief Set the configuration of plots.
     *
     * \param[in] value Configuration of plots.
     * \return Reference to this object.
     */
    Plotter& config(const PlotConfig& value);

    /*!
     * \brief Set the desired size of images.
     *
     * \param[in] height Desired height of the plots.
     * \param[in] width Desired width of the plots.
     * \return Reference to this object.
     */
    Plotter& desired_size(int height, int width);

    /*!
     * \brief Get the actual size of images.
     *
     * \return Pair of actual height and actual width of the plots.
     */
    [[nodiscard]] std::pair<int, int> actual_size() const noexcept;

    /*!
     * \brief Write background of plots.
     *
     * \param[in] image Image to write.
     *
     * \note This changes the internal states holding some parameters used in
     * write_curve function.
     */
    void write_background(Image& image);

    /*!
     * \brief Write a curve on plots.
     *
     * \param[in] samples Samples points of the curve.
     * \param[in] color Color of the curve.
     * \param[in] image Image to write.
     *
     * \note This function must be called after write_background function
     * because this function uses some parameters computed in write_background
     * function.
     */
    void write_curve(
        const std::vector<Point>& samples, const RGBColor& color, Image& image);

private:
    /*!
     * \brief Write grid lines of plots.
     *
     * \param[in] image Image to write.
     */
    void write_grid_lines(Image& image);

    /*!
     * \brief Write x axis.
     *
     * \param[in] image Image to write.
     */
    void write_x_axis(Image& image);

    /*!
     * \brief Write y axis.
     *
     * \param[in] image Image to write.
     */
    void write_y_axis(Image& image);

    //! Range of plots.
    PlotRange range_;

    //! Configuration of plots.
    PlotConfig config_;

    //! Desired height of the plots.
    int desired_height_{initial_height};

    //! Desired width of the plots.
    int desired_width_{initial_width};

    //! Actual height of the plots.
    int actual_height_{initial_height};

    //! Actual width of the plots.
    int actual_width_{initial_width};

    /*!
     * \brief Margins of plots. (This configuration is used over the value
     * in config because tuning of the left margin is needed.)
     */
    Margin margin_;

    //! Ticks of the x-axis.
    AxisTicks x_axis_ticks_;

    //! Ticks of the y-axis.
    AxisTicks y_axis_ticks_;
};

}  // namespace func_sketch::plotter
