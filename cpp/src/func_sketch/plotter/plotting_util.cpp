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
 * \brief Implementation of functions for internal implementation of plotting.
 */
#include "func_sketch/plotter/plotting_util.h"

#include <algorithm>
#include <cmath>

#include <opencv2/imgproc.hpp>

#include "func_sketch/exceptions.h"

namespace func_sketch::plotter {

cv::Scalar convert_color(const RGBColor& color) {
    // Use RGB order in this implementation.
    return cv::Scalar(color.r, color.g, color.b);
}

cv::Point convert_position(const Point& position, const PlotRange& range,
    const PlotConfig& config, const cv::MatSize& size) {
    const int plot_width =
        size[1] - config.left_margin() - config.right_margin();
    const int plot_height =
        size[0] - config.top_margin() - config.bottom_margin();
    if (plot_width <= 0 || plot_height <= 0) {
        throw InvalidArgumentException("Too small image size.");
    }

    const double x_ratio = (position.x - range.x_range().first) /
        (range.x_range().second - range.x_range().first);
    const double y_ratio = (position.y - range.y_range().first) /
        (range.y_range().second - range.y_range().first);

    // This version does not use shift.
    const int x_in_pixel =
        static_cast<int>(plot_width * x_ratio) + config.left_margin();
    const int y_in_pixel =
        static_cast<int>(plot_height * (1.0 - y_ratio)) + config.top_margin();

    return cv::Point(x_in_pixel, y_in_pixel);
}

/*!
 * \brief Convert a position from plot coordinates to image coordinates with
 * shift.
 *
 * \param[in] position Position in plot coordinates.
 * \param[in] range Range of plots.
 * \param[in] config Configuration of plots.
 * \param[in] size Size of the image.
 * \param[in] shift Number of fractional bits in the image coordinates.
 * \return Converted position in image coordinates.
 */
[[nodiscard]] cv::Point convert_position_with_shift(const Point& position,
    const PlotRange& range, const PlotConfig& config, const cv::MatSize& size,
    int shift) {
    const int plot_width =
        size[1] - config.left_margin() - config.right_margin();
    const int plot_height =
        size[0] - config.top_margin() - config.bottom_margin();
    if (plot_width <= 0 || plot_height <= 0) {
        throw InvalidArgumentException("Too small image size.");
    }

    const double x_ratio = (position.x - range.x_range().first) /
        (range.x_range().second - range.x_range().first);
    const double y_ratio = (position.y - range.y_range().first) /
        (range.y_range().second - range.y_range().first);

    const double x_in_pixel_precise =
        static_cast<double>(plot_width) * x_ratio +
        static_cast<double>(config.left_margin());
    const double y_in_pixel_precise =
        static_cast<double>(plot_height) * (1.0 - y_ratio) +
        static_cast<double>(config.top_margin());

    const double coeff = std::ldexp(1.0, shift);
    const int x_in_pixel_shifted = static_cast<int>(x_in_pixel_precise * coeff);
    const int y_in_pixel_shifted = static_cast<int>(y_in_pixel_precise * coeff);

    return cv::Point(x_in_pixel_shifted, y_in_pixel_shifted);
}

void write_line(Image& image, const Point& start_point, const Point& end_point,
    const cv::Scalar& color, int line_width, const PlotRange& range,
    const PlotConfig& config) {
    // Use shift to draw lines precisely.
    constexpr int shift = 10;
    const auto start_pixel = convert_position_with_shift(
        start_point, range, config, image.size, shift);
    const auto end_pixel = convert_position_with_shift(
        end_point, range, config, image.size, shift);
    cv::line(
        image, start_pixel, end_pixel, color, line_width, cv::LINE_AA, shift);
}

Point clamp_point(const Point& point, const PlotRange& range) {
    // TODO Better implementation.
    return Point{
        .x = std::clamp(point.x, range.x_range().first, range.x_range().second),
        .y =
            std::clamp(point.y, range.y_range().first, range.y_range().second)};
}

}  // namespace func_sketch::plotter
