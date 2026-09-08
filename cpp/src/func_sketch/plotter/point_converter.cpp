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
 * \brief Implementation of PointConverter class.
 */
#include "func_sketch/plotter/point_converter.h"

#include <cmath>

#include "func_sketch/exceptions.h"

namespace func_sketch::plotter {

PointConverter::PointConverter(const Margin& plot_region_margin,
    const PlotRange& range,  // NOLINT(*-pass-by-value): Wrong warning for
                             // small objects.
    int image_height, int image_width)
    : plot_region_margin_(plot_region_margin),
      range_(range),
      image_height_(image_height),
      image_width_(image_width) {
    if (image_height_ <= 0 || image_width_ <= 0) {
        throw InvalidArgumentException("Invalid image size.");
    }
    update_plot_region_size();
}

cv::Point PointConverter::convert_plot_to_image(const Point& from) const {
    const double x_ratio = (from.x - range_.x_range().first) /
        (range_.x_range().second - range_.x_range().first);
    const double y_ratio = (from.y - range_.y_range().first) /
        (range_.y_range().second - range_.y_range().first);

    // This version does not use shift.
    const int x_in_pixel = static_cast<int>(plot_region_width_ * x_ratio) +
        plot_region_margin_.left();
    const int y_in_pixel =
        static_cast<int>(plot_region_height_ * (1.0 - y_ratio)) +
        plot_region_margin_.top();

    return cv::Point(x_in_pixel, y_in_pixel);
}

cv::Point PointConverter::convert_plot_to_image(
    const Point& from, int shift) const {
    const double x_ratio = (from.x - range_.x_range().first) /
        (range_.x_range().second - range_.x_range().first);
    const double y_ratio = (from.y - range_.y_range().first) /
        (range_.y_range().second - range_.y_range().first);

    const double x_in_pixel_precise =
        static_cast<double>(plot_region_width_) * x_ratio +
        static_cast<double>(plot_region_margin_.left());
    const double y_in_pixel_precise =
        static_cast<double>(plot_region_height_) * (1.0 - y_ratio) +
        static_cast<double>(plot_region_margin_.top());

    const double coeff = std::ldexp(1.0, shift);
    const int x_in_pixel_shifted = static_cast<int>(x_in_pixel_precise * coeff);
    const int y_in_pixel_shifted = static_cast<int>(y_in_pixel_precise * coeff);

    return cv::Point(x_in_pixel_shifted, y_in_pixel_shifted);
}

Point PointConverter::convert_image_to_plot(const cv::Point& from) const {
    const double x_ratio =
        static_cast<double>(from.x - plot_region_margin_.left()) /
        static_cast<double>(plot_region_width_);
    const double y_ratio = 1.0 -
        static_cast<double>(from.y - plot_region_margin_.top()) /
            static_cast<double>(plot_region_height_);

    const double x_value = range_.x_range().first +
        x_ratio * (range_.x_range().second - range_.x_range().first);
    const double y_value = range_.y_range().first +
        y_ratio * (range_.y_range().second - range_.y_range().first);

    return Point{.x = x_value, .y = y_value};
}

std::pair<double, double> PointConverter::image_to_plot_coefficient() const {
    const double x_coeff = (range_.x_range().second - range_.x_range().first) /
        static_cast<double>(plot_region_width_);
    const double y_coeff = (range_.y_range().second - range_.y_range().first) /
        static_cast<double>(plot_region_height_);
    return std::make_pair(x_coeff, y_coeff);
}

void PointConverter::update_plot_region_size() {
    plot_region_height_ = image_height_ - plot_region_margin_.top() -
        plot_region_margin_.bottom();
    plot_region_width_ =
        image_width_ - plot_region_margin_.left() - plot_region_margin_.right();
    if (plot_region_width_ <= 0 || plot_region_height_ <= 0) {
        throw InvalidArgumentException("Too small image size.");
    }
}

}  // namespace func_sketch::plotter
