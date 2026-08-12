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
 * \brief Declaration of functions for internal implementation of plotting.
 */
#pragma once

#include <opencv2/core.hpp>

#include "func_sketch/plotter/image.h"
#include "func_sketch/plotter/plot_config.h"
#include "func_sketch/plotter/plot_range.h"
#include "func_sketch/plotter/point.h"
#include "func_sketch/plotter/rgb_color.h"

namespace func_sketch::plotter {

/*!
 * \brief Convert a color from RGBColor to cv::Scalar.
 *
 * \param[in] color Color to convert.
 * \return Converted color.
 *
 * \note This function assumes that the image is in RGB format,
 * not BGR format as in default of OpenCV.
 */
[[nodiscard]] cv::Scalar convert_color(const RGBColor& color);

/*!
 * \brief Convert a position from plot coordinates to image coordinates.
 *
 * \param[in] position Position in plot coordinates.
 * \param[in] range Range of plots.
 * \param[in] config Configuration of plots.
 * \param[in] left_margin Left margin of plots in pixels. (This value is used
 * over the value in config because tuning of the left margin is needed.)
 * \param[in] size Size of the image.
 * \return Converted position in image coordinates.
 */
[[nodiscard]] cv::Point convert_position(const Point& position,
    const PlotRange& range, const PlotConfig& config, int left_margin,
    const cv::MatSize& size);

/*!
 * \brief Write a line on an image.
 *
 * \param[out] image Image to write on.
 * \param[in] start_point Starting point of the line.
 * \param[in] end_point Ending point of the line.
 * \param[in] color Color of the line.
 * \param[in] line_width Width of the line.
 * \param[in] range Range of plots.
 * \param[in] config Configuration of plots.
 * \param[in] left_margin Left margin of plots in pixels. (This value is used
 * over the value in config because tuning of the left margin is needed.)
 */
void write_line(Image& image, const Point& start_point, const Point& end_point,
    const cv::Scalar& color, int line_width, const PlotRange& range,
    const PlotConfig& config, int left_margin);

/*!
 * \brief Try to clamp a point with infinity to the range.
 *
 * \param[in,out] point Point to clamp.
 * \param[in] range Range to clamp the point to.
 * \retval true The point was clamped or the point was finite.
 * \retval false The point could not be clamped because it was infinite in both
 * coordinates.
 *
 * \note This function does not check for NaN values.
 */
[[nodiscard]] bool try_clamp_infinity(Point& point, const PlotRange& range);

/*!
 * \brief Compute the intersection of a line segment with the boundary of  the
 * plot range.
 *
 * \param[in] point_in_range Point inside the range.
 * \param[in] point_out_of_range Point outside the range.
 * \param[in] range Range of plots.
 * \return Intersection point of the line segment with the range.
 *
 * \note This function assumes that all coordinates are finite
 * and that the line segment intersects with the boundary of the range.
 */
[[nodiscard]] Point compute_intersection_with_range(const Point& point_in_range,
    const Point& point_out_of_range, const PlotRange& range);

/*!
 * \brief Clamp a point inside the plot range.
 *
 * \param[in] point Point to clamp.
 * \param[in] range Range of plots.
 * \return Clamped point.
 */
[[nodiscard]] Point clamp_point(const Point& point, const PlotRange& range);

}  // namespace func_sketch::plotter
