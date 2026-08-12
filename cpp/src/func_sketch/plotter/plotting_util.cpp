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
#include <cassert>
#include <cmath>

#include <opencv2/imgproc.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/exceptions.h"

namespace func_sketch::plotter {

cv::Scalar convert_color(const RGBColor& color) {
    // Use RGB order in this implementation.
    return cv::Scalar(color.r, color.g, color.b);
}

cv::Point convert_position(const Point& position, const PlotRange& range,
    const PlotConfig& config, int left_margin, const cv::MatSize& size) {
    const int plot_width = size[1] - left_margin - config.right_margin();
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
    const int x_in_pixel = static_cast<int>(plot_width * x_ratio) + left_margin;
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
 * \param[in] left_margin Left margin of plots in pixels. (This value is used
 * over the value in config because tuning of the left margin is needed.)
 * \param[in] size Size of the image.
 * \param[in] shift Number of fractional bits in the image coordinates.
 * \return Converted position in image coordinates.
 */
[[nodiscard]] cv::Point convert_position_with_shift(const Point& position,
    const PlotRange& range, const PlotConfig& config, int left_margin,
    const cv::MatSize& size, int shift) {
    const int plot_width = size[1] - left_margin - config.right_margin();
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
        static_cast<double>(left_margin);
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
    const PlotConfig& config, int left_margin) {
    // Use shift to draw lines precisely.
    constexpr int shift = 10;
    const auto start_pixel = convert_position_with_shift(
        start_point, range, config, left_margin, image.size, shift);
    const auto end_pixel = convert_position_with_shift(
        end_point, range, config, left_margin, image.size, shift);
    cv::line(
        image, start_pixel, end_pixel, color, line_width, cv::LINE_AA, shift);
}

bool try_clamp_infinity(Point& point, const PlotRange& range) {
    if (std::isinf(point.x) && std::isinf(point.y)) {
        return false;
    }
    if (std::isinf(point.x)) {
        point.x =
            (point.x > 0) ? range.x_range().second : range.x_range().first;
    }
    if (std::isinf(point.y)) {
        point.y =
            (point.y > 0) ? range.y_range().second : range.y_range().first;
    }
    return true;
}

/*!
 * \brief Compute the intersection of a line segment with a vertical line.
 *
 * \param[in] point1 First point of the line segment.
 * \param[in] point2 Second point of the line segment.
 * \param[in] x_value X-coordinate of the vertical line.
 * \return Intersection point of the line segment with the vertical line.
 */
Point compute_intersection_with_vertical_line(
    const Point& point1, const Point& point2, Real x_value) {
    assert(point1.x != point2.x);
    const Real slope = (point2.y - point1.y) / (point2.x - point1.x);
    const Real y_value = point1.y + slope * (x_value - point1.x);
    return Point{.x = x_value, .y = y_value};
}

/*!
 * \brief Compute the intersection of a line segment with a horizontal line.
 *
 * \param[in] point1 First point of the line segment.
 * \param[in] point2 Second point of the line segment.
 * \param[in] y_value Y-coordinate of the horizontal line.
 * \return Intersection point of the line segment with the horizontal line.
 */
Point compute_intersection_with_horizontal_line(
    const Point& point1, const Point& point2, Real y_value) {
    assert(point1.y != point2.y);
    const Real slope = (point2.x - point1.x) / (point2.y - point1.y);
    const Real x_value = point1.x + slope * (y_value - point1.y);
    return Point{.x = x_value, .y = y_value};
}

Point compute_intersection_with_range(const Point& point_in_range,
    const Point& point_out_of_range, const PlotRange& range) {
    Point intersection = point_out_of_range;

    if (intersection.x < range.x_range().first) {
        intersection = compute_intersection_with_vertical_line(
            point_in_range, intersection, range.x_range().first);
    } else if (intersection.x > range.x_range().second) {
        intersection = compute_intersection_with_vertical_line(
            point_in_range, intersection, range.x_range().second);
    }

    if (intersection.y < range.y_range().first) {
        intersection = compute_intersection_with_horizontal_line(
            point_in_range, intersection, range.y_range().first);
    } else if (intersection.y > range.y_range().second) {
        intersection = compute_intersection_with_horizontal_line(
            point_in_range, intersection, range.y_range().second);
    }

    return intersection;
}

Point clamp_point(const Point& point, const PlotRange& range) {
    // TODO Better implementation.
    return Point{
        .x = std::clamp(point.x, range.x_range().first, range.x_range().second),
        .y =
            std::clamp(point.y, range.y_range().first, range.y_range().second)};
}

}  // namespace func_sketch::plotter
