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
 * \brief Definition of PointConverter class.
 */
#pragma once

#include <utility>

#include <opencv2/core.hpp>

#include "func_sketch/plotter/margin.h"
#include "func_sketch/plotter/plot_range.h"
#include "func_sketch/plotter/point.h"

namespace func_sketch::plotter {

/*!
 * \brief Class to convert points between coordinate systems.
 */
class PointConverter {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] plot_region_margin Margin of the plot region.
     * \param[in] range Range of plots.
     * \param[in] image_height Height of the image.
     * \param[in] image_width Width of the image.
     */
    PointConverter(const Margin& plot_region_margin, const PlotRange& range,
        int image_height, int image_width);

    /*!
     * \brief Convert a point from plot coordinates to image coordinates.
     *
     * \param[in] from Point in plot coordinates.
     * \return Point in image coordinates.
     */
    [[nodiscard]] cv::Point convert_plot_to_image(const Point& from) const;

    /*!
     * \brief Convert a point from plot coordinates to image coordinates.
     *
     * \param[in] from Point in plot coordinates.
     * \param[in] shift Number of fractional bits in the image coordinates.
     * \return Point in image coordinates.
     */
    [[nodiscard]] cv::Point convert_plot_to_image(
        const Point& from, int shift) const;

    /*!
     * \brief Convert a point from image coordinates to plot coordinates.
     *
     * \param[in] from Point in image coordinates.
     * \return Point in plot coordinates.
     */
    [[nodiscard]] Point convert_image_to_plot(const cv::Point& from) const;

    /*!
     * \brief Get the coefficients for converting differences in image
     * coordinates to plot coordinates.
     *
     * \return Coefficients for converting differences in image coordinates to
     * plot coordinates for x and y.
     */
    [[nodiscard]] std::pair<double, double> image_to_plot_coefficient() const;

private:
    /*!
     * \brief Update the size of the plot region.
     */
    void update_plot_region_size();

    //! Margin of the plot region.
    Margin plot_region_margin_;

    //! Range of plots.
    PlotRange range_;

    //! Height of the image.
    int image_height_;

    //! Width of the image.
    int image_width_;

    //! Height of the plot region.
    int plot_region_height_{};

    //! Width of the plot region.
    int plot_region_width_{};
};

}  // namespace func_sketch::plotter
