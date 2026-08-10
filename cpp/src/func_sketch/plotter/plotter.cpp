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
 * \brief Implementation of Plotter class.
 */
#include "func_sketch/plotter/plotter.h"

#include <algorithm>
#include <cmath>

#include <fmt/format.h>
#include <opencv2/imgproc.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/plotter/plotting_util.h"
#include "func_sketch/plotter/point.h"

namespace func_sketch::plotter {

namespace {

/*!
 * \brief Adjust the position of text to be inside the image.
 *
 * \param[in] position Desired position of the text.
 * \param[in] text_size Size of the text.
 * \param[in] image_size Size of the image.
 * \return Adjusted position of the text.
 */
[[nodiscard]] cv::Point adjust_text_position(const cv::Point& position,
    const cv::Size& text_size, const cv::Size& image_size) {
    cv::Point adjusted_position = position;

    adjusted_position.x = std::max(adjusted_position.x, 0);
    adjusted_position.x =
        std::min(adjusted_position.x, image_size.width - text_size.width);

    adjusted_position.y = std::max(adjusted_position.y, 0);
    adjusted_position.y =
        std::min(adjusted_position.y, image_size.height - text_size.height);

    return adjusted_position;
}

}  // namespace

// NOLINTNEXTLINE(*-pass-by-value): Wrong warning for small objects.
Plotter::Plotter(const PlotRange& range, const PlotConfig& config)
    : range_(range), config_(config) {
    update_grid_positions();
}

Plotter& Plotter::range(const PlotRange& value) {
    range_ = value;
    update_grid_positions();
    return *this;
}

Plotter& Plotter::config(const PlotConfig& value) {
    config_ = value;
    update_grid_positions();
    return *this;
}

void Plotter::update_grid_positions() {
    // TODO Better determination of grid lines.
    constexpr int num_grid_lines = 5;
    // vertical lines.
    x_grid_positions_.clear();
    x_grid_positions_.reserve(num_grid_lines);
    for (int i = 0; i < num_grid_lines; ++i) {
        const Real x_ratio = static_cast<Real>(i) / (num_grid_lines - 1);
        const Real x_value = range_.x_range().first +
            x_ratio * (range_.x_range().second - range_.x_range().first);
        x_grid_positions_.push_back(x_value);
    }
    // horizontal lines.
    y_grid_positions_.clear();
    y_grid_positions_.reserve(num_grid_lines);
    for (int i = 0; i < num_grid_lines; ++i) {
        const Real y_ratio = static_cast<Real>(i) / (num_grid_lines - 1);
        const Real y_value = range_.y_range().first +
            y_ratio * (range_.y_range().second - range_.y_range().first);
        y_grid_positions_.push_back(y_value);
    }
}

void Plotter::write_background(Image& image) const {
    // Background.
    const auto color = convert_color(config_.background_color());
    image = color;

    write_grid_lines(image);
    write_x_axis(image);
    write_y_axis(image);
}

void Plotter::write_curve(const std::vector<Point>& samples,
    const RGBColor& color, Image& image) const {
    const auto size = image.size;

    const auto cv_color = convert_color(color);
    const int line_width = config_.curve_line_width();

    const std::size_t num_samples = samples.size();
    if (num_samples < 2) {
        return;
    }
    for (std::size_t i = 0; i < num_samples - 1; ++i) {
        Point start_xy = samples[i];
        Point end_xy = samples[i + 1];

        const bool is_start_in_range = range_.contains(start_xy);
        const bool is_end_in_range = range_.contains(end_xy);
        if (!is_start_in_range && !is_end_in_range) {
            // In this case, the range of the line segment may contain a
            // singularity of the function.
            continue;
        }

        if (std::isnan(start_xy.x) || std::isnan(start_xy.y) ||
            std::isnan(end_xy.x) || std::isnan(end_xy.y)) {
            // NaN cannot be fixed.
            continue;
        }

        if (!is_start_in_range) {
            if (!try_clamp_infinity(start_xy, range_)) {
                continue;
            }
            start_xy =
                compute_intersection_with_range(end_xy, start_xy, range_);
        }
        if (!is_end_in_range) {
            if (!try_clamp_infinity(end_xy, range_)) {
                continue;
            }
            end_xy = compute_intersection_with_range(start_xy, end_xy, range_);
        }

        write_line(
            image, start_xy, end_xy, cv_color, line_width, range_, config_);
    }
}

void Plotter::write_grid_lines(Image& image) const {
    const auto size = image.size;

    // vertical lines.
    for (const Real x_value : x_grid_positions_) {
        write_line(image, Point{.x = x_value, .y = range_.y_range().first},
            Point{.x = x_value, .y = range_.y_range().second},
            convert_color(config_.grid_color()), config_.grid_line_width(),
            range_, config_);
    }
    // horizontal lines.
    for (const Real y_value : y_grid_positions_) {
        write_line(image, Point{.x = range_.x_range().first, .y = y_value},
            Point{.x = range_.x_range().second, .y = y_value},
            convert_color(config_.grid_color()), config_.grid_line_width(),
            range_, config_);
    }
}

//! Ratio of the threshold to check whether a tick label is at zero.
constexpr Real axis_tick_threshold_ratio = 5e-2;

void Plotter::write_x_axis(Image& image) const {
    const auto size = image.size;

    const auto color = convert_color(config_.axes_color());

    const Real y_value = std::clamp(
        static_cast<Real>(0), range_.y_range().first, range_.y_range().second);

    write_line(image, Point{.x = range_.x_range().first, .y = y_value},
        Point{.x = range_.x_range().second, .y = y_value}, color,
        config_.axes_line_width(), range_, config_);

    const Real tick_threshold =
        std::min(range_.x_range().second - range_.x_range().first,
            range_.y_range().second - range_.y_range().first) *
        axis_tick_threshold_ratio;

    for (const Real x_value : x_grid_positions_) {
        if (std::abs(x_value) < tick_threshold) {
            continue;
        }

        const auto text = fmt::format("{:.1e}", x_value);
        constexpr int font_face = cv::FONT_HERSHEY_SIMPLEX;
        const int font_size = config_.tick_label_font_size();
        const double font_scale =
            cv::getFontScaleFromHeight(font_face, font_size);
        constexpr int thickness = 1;
        const cv::Size text_size =
            cv::getTextSize(text, font_face, font_scale, thickness, nullptr);

        const auto base_position = convert_position(
            Point{.x = x_value, .y = y_value}, range_, config_, size);
        const int tick_margin = font_size / 2;
        auto top_left_position =
            cv::Point(base_position.x - text_size.width / 2,
                base_position.y + tick_margin + text_size.height);
        top_left_position = adjust_text_position(
            top_left_position, text_size, cv::Size(size[1], size[0]));

        cv::putText(image, text, top_left_position, font_face, font_scale,
            color, thickness, cv::LINE_AA);
    }
}

void Plotter::write_y_axis(Image& image) const {
    const auto size = image.size;

    const auto color = convert_color(config_.axes_color());

    const Real x_value = std::clamp(
        static_cast<Real>(0), range_.x_range().first, range_.x_range().second);

    write_line(image, Point{.x = x_value, .y = range_.y_range().first},
        Point{.x = x_value, .y = range_.y_range().second}, color,
        config_.axes_line_width(), range_, config_);

    const Real tick_threshold =
        std::min(range_.x_range().second - range_.x_range().first,
            range_.y_range().second - range_.y_range().first) *
        axis_tick_threshold_ratio;

    for (const Real y_value : y_grid_positions_) {
        if (std::abs(y_value) < tick_threshold) {
            continue;
        }

        const auto text = fmt::format("{:.1e}", y_value);
        constexpr int font_face = cv::FONT_HERSHEY_SIMPLEX;
        const int font_size = config_.tick_label_font_size();
        const double font_scale =
            cv::getFontScaleFromHeight(font_face, font_size);
        constexpr int thickness = 1;
        const cv::Size text_size =
            cv::getTextSize(text, font_face, font_scale, thickness, nullptr);

        const auto base_position = convert_position(
            Point{.x = x_value, .y = y_value}, range_, config_, size);
        const int tick_margin = font_size / 2;
        cv::Point top_left_position;
        if (base_position.x + tick_margin + text_size.width < size[1]) {
            top_left_position = cv::Point(base_position.x + tick_margin,
                base_position.y + text_size.height / 2);
        } else {
            top_left_position =
                cv::Point(base_position.x - tick_margin - text_size.width,
                    base_position.y + text_size.height / 2);
        }
        top_left_position = adjust_text_position(
            top_left_position, text_size, cv::Size(size[1], size[0]));

        cv::putText(image, text, top_left_position, font_face, font_scale,
            color, thickness, cv::LINE_AA);
    }
}

}  // namespace func_sketch::plotter
