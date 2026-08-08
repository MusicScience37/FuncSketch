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

#include "func_sketch/common_types.h"
#include "func_sketch/plotter/image.h"
#include "func_sketch/plotter/plot_config.h"
#include "func_sketch/plotter/plot_range.h"
#include "func_sketch/plotter/point.h"

namespace func_sketch::plotter {

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
     * \brief Write background of plots.
     *
     * \param[in] image Image to write.
     */
    void write_background(Image& image) const;

    /*!
     * \brief Write a curve on plots.
     *
     * \param[in] samples Samples points of the curve.
     * \param[in] color Color of the curve.
     * \param[in] image Image to write.
     */
    void write_curve(const std::vector<Point>& samples, const RGBColor& color,
        Image& image) const;

private:
    /*!
     * \brief Update grid positions.
     */
    void update_grid_positions();

    /*!
     * \brief Write grid lines of plots.
     *
     * \param[in] image Image to write.
     */
    void write_grid_lines(Image& image) const;

    /*!
     * \brief Write x axis.
     *
     * \param[in] image Image to write.
     */
    void write_x_axis(Image& image) const;

    /*!
     * \brief Write y axis.
     *
     * \param[in] image Image to write.
     */
    void write_y_axis(Image& image) const;

    //! Range of plots.
    PlotRange range_;

    //! Configuration of plots.
    PlotConfig config_;

    //! Grid positions in x axis.
    std::vector<Real> x_grid_positions_;

    //! Grid positions in y axis.
    std::vector<Real> y_grid_positions_;
};

}  // namespace func_sketch::plotter
