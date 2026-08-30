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
#include <cstddef>

#include <fmt/format.h>
#include <opencv2/imgproc.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/exceptions.h"
#include "func_sketch/plotter/axis_ticks.h"
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

/*!
 * \brief Update axis ticks.
 *
 * \param[in] range Range of the axis. Pair of minimum and maximum values.
 * \param[in] image_size Size of the image.
 * \param[in] config Configuration of the plot.
 * \param[out] x_axis_ticks Ticks of the x-axis.
 * \param[out] y_axis_ticks Ticks of the y-axis.
 */
void update_axis_ticks(const PlotRange& range, const cv::MatSize& image_size,
    const PlotConfig& config, AxisTicks& x_axis_ticks,
    AxisTicks& y_axis_ticks) {
    const std::size_t approx_num_ticks_x = std::max(static_cast<std::size_t>(1),
        static_cast<std::size_t>(image_size[1]) /
            config.axes().num_pixels_per_tick_in_x_axis());
    const std::size_t approx_num_ticks_y = std::max(static_cast<std::size_t>(1),
        static_cast<std::size_t>(image_size[0]) /
            config.axes().num_pixels_per_tick_in_y_axis());

    generate_axis_ticks(range.x_range(), approx_num_ticks_x, x_axis_ticks);
    generate_axis_ticks(range.y_range(), approx_num_ticks_y, y_axis_ticks);
}

//! Font face used for texts in plots.
constexpr int plot_text_font_face = cv::FONT_HERSHEY_SIMPLEX;

//! Thickness of texts in plots.
constexpr int plot_text_thickness = 1;

/*!
 * \brief Compute the required width for y-axis tick labels in pixels.
 *
 * \param[in] y_axis_ticks Ticks of the y-axis.
 * \param[in] config Configuration of the plot.
 * \return Required width for y-axis tick labels in pixels.
 */
[[nodiscard]] int compute_required_width_for_y_axis_tick_labels(
    const AxisTicks& y_axis_ticks, const PlotConfig& config) {
    const int font_size = config.axes().tick_label_font_size();
    const double font_scale =
        cv::getFontScaleFromHeight(plot_text_font_face, font_size);
    int required_width = 0;
    for (const auto& text : y_axis_ticks.strings) {
        const cv::Size text_size = cv::getTextSize(text, plot_text_font_face,
            font_scale, plot_text_thickness, nullptr);
        required_width = std::max(required_width, text_size.width);
    }
    return required_width;
}

}  // namespace

// NOLINTNEXTLINE(*-pass-by-value): Wrong warning for small objects.
Plotter::Plotter(const PlotRange& range, const PlotConfig& config)
    : range_(range), config_(config) {}

Plotter& Plotter::range(const PlotRange& value) {
    range_ = value;
    return *this;
}

Plotter& Plotter::config(const PlotConfig& value) {
    config_ = value;
    return *this;
}

Plotter& Plotter::desired_size(int height, int width) {
    desired_height_ = height;
    desired_width_ = width;

    actual_height_ = desired_height_;
    actual_width_ = desired_width_;
    // TODO Tune actual sizes later.
    constexpr int min_height = 300;
    if (actual_height_ < min_height) {
        double scale = static_cast<double>(min_height) /
            static_cast<double>(actual_height_);
        actual_height_ = min_height;
        actual_width_ = static_cast<int>(actual_width_ * scale);
    }
    constexpr int min_width = 300;
    if (actual_width_ < min_width) {
        double scale =
            static_cast<double>(min_width) / static_cast<double>(actual_width_);
        actual_width_ = min_width;
        actual_height_ = static_cast<int>(actual_height_ * scale);
    }

    return *this;
}

[[nodiscard]] std::pair<int, int> Plotter::actual_size() const noexcept {
    return {actual_height_, actual_width_};
}

void Plotter::write_background(Image& image) {
    const auto size = image.size;
    if (size.dims() != 2 || size[0] != actual_height_ ||
        size[1] != actual_width_) {
        throw InvalidArgumentException("Invalid image size.");
    }

    update_axis_ticks(range_, size, config_, x_axis_ticks_, y_axis_ticks_);
    margin_ = config_.margin();
    const int required_width_for_y_axis_tick_labels =
        compute_required_width_for_y_axis_tick_labels(y_axis_ticks_, config_);
    const int margin_for_y_axis_tick_labels =
        config_.axes().tick_label_font_size();
    margin_.left(std::max(margin_.left(),
        required_width_for_y_axis_tick_labels + margin_for_y_axis_tick_labels));

    // Background.
    const auto color = convert_color(config_.background_color());
    image = color;

    write_grid_lines(image);
    write_x_axis(image);
    write_y_axis(image);
}

void Plotter::write_curve(
    const std::vector<Point>& samples, const RGBColor& color, Image& image) {
    const auto size = image.size;
    if (size.dims() != 2 || size[0] != actual_height_ ||
        size[1] != actual_width_) {
        throw InvalidArgumentException("Invalid image size.");
    }

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
            image, start_xy, end_xy, cv_color, line_width, range_, margin_);
    }
}

void Plotter::write_grid_lines(Image& image) {
    const auto size = image.size;

    // vertical lines.
    for (const Real x_value : x_axis_ticks_.values) {
        const int line_width = (x_value == 0.0)
            ? config_.grid().zero_line_width()
            : config_.grid().line_width();
        write_line(image, Point{.x = x_value, .y = range_.y_range().first},
            Point{.x = x_value, .y = range_.y_range().second},
            convert_color(config_.grid().color()), line_width, range_, margin_);
    }
    // horizontal lines.
    for (const Real y_value : y_axis_ticks_.values) {
        const int line_width = (y_value == 0.0)
            ? config_.grid().zero_line_width()
            : config_.grid().line_width();
        write_line(image, Point{.x = range_.x_range().first, .y = y_value},
            Point{.x = range_.x_range().second, .y = y_value},
            convert_color(config_.grid().color()), line_width, range_, margin_);
    }
}

void Plotter::write_x_axis(Image& image) {
    const auto size = image.size;

    const auto color = convert_color(config_.axes().color());

    // Draw the x-axis at the bottom in the plot.
    const Real y_value = range_.y_range().first;

    write_line(image, Point{.x = range_.x_range().first, .y = y_value},
        Point{.x = range_.x_range().second, .y = y_value}, color,
        config_.axes().line_width(), range_, margin_);

    const int font_size = config_.axes().tick_label_font_size();
    const double font_scale =
        cv::getFontScaleFromHeight(plot_text_font_face, font_size);

    assert(x_axis_ticks_.values.size() == x_axis_ticks_.strings.size());
    for (std::size_t i = 0; i < x_axis_ticks_.values.size(); ++i) {
        const Real x_value = x_axis_ticks_.values[i];

        const auto text = x_axis_ticks_.strings[i];
        const cv::Size text_size = cv::getTextSize(text, plot_text_font_face,
            font_scale, plot_text_thickness, nullptr);

        const auto base_position = convert_position(
            Point{.x = x_value, .y = y_value}, range_, margin_, size);
        const int tick_margin = font_size / 2;
        auto top_left_position =
            cv::Point(base_position.x - text_size.width / 2,
                base_position.y + tick_margin + text_size.height);
        top_left_position = adjust_text_position(
            top_left_position, text_size, cv::Size(size[1], size[0]));

        cv::putText(image, text, top_left_position, plot_text_font_face,
            font_scale, color, plot_text_thickness, cv::LINE_AA);
    }
}

void Plotter::write_y_axis(Image& image) {
    const auto size = image.size;

    const auto color = convert_color(config_.axes().color());

    // Draw the y-axis at the left in the plot.
    const Real x_value = range_.x_range().first;

    write_line(image, Point{.x = x_value, .y = range_.y_range().first},
        Point{.x = x_value, .y = range_.y_range().second}, color,
        config_.axes().line_width(), range_, margin_);

    const int font_size = config_.axes().tick_label_font_size();
    const double font_scale =
        cv::getFontScaleFromHeight(plot_text_font_face, font_size);

    assert(y_axis_ticks_.values.size() == y_axis_ticks_.strings.size());
    for (std::size_t i = 0; i < y_axis_ticks_.values.size(); ++i) {
        const Real y_value = y_axis_ticks_.values[i];

        const auto text = y_axis_ticks_.strings[i];
        const cv::Size text_size = cv::getTextSize(text, plot_text_font_face,
            font_scale, plot_text_thickness, nullptr);

        const auto base_position = convert_position(
            Point{.x = x_value, .y = y_value}, range_, margin_, size);
        const int tick_margin = font_size / 2;
        cv::Point top_left_position;
        top_left_position =
            cv::Point(base_position.x - tick_margin - text_size.width,
                base_position.y + text_size.height / 2);
        top_left_position = adjust_text_position(
            top_left_position, text_size, cv::Size(size[1], size[0]));

        cv::putText(image, text, top_left_position, plot_text_font_face,
            font_scale, color, plot_text_thickness, cv::LINE_AA);
    }
}

}  // namespace func_sketch::plotter
