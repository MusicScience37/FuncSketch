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
#include <stdexcept>

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

}  // namespace

// NOLINTNEXTLINE(*-pass-by-value): Wrong warning for small objects.
Plotter::Plotter(const PlotRange& range, const PlotConfig& config)
    : range_(range), config_(config) {
    update_internal_parameters();
}

Plotter& Plotter::range(const PlotRange& value) {
    range_ = value;
    update_internal_parameters();
    return *this;
}

Plotter& Plotter::config(const PlotConfig& value) {
    config_ = value;
    update_internal_parameters();
    return *this;
}

Plotter& Plotter::desired_size(int height, int width) {
    desired_height_ = height;
    desired_width_ = width;
    update_internal_parameters();
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

    // Background.
    const auto color = convert_color(config_.background_color());
    image = color;

    write_grid_lines(image);
    write_plot_title(image);
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

        write_line(image, start_xy, end_xy, cv_color, line_width, range_,
            plot_region_margin_);
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
            convert_color(config_.grid().color()), line_width, range_,
            plot_region_margin_);
    }
    // horizontal lines.
    for (const Real y_value : y_axis_ticks_.values) {
        const int line_width = (y_value == 0.0)
            ? config_.grid().zero_line_width()
            : config_.grid().line_width();
        write_line(image, Point{.x = range_.x_range().first, .y = y_value},
            Point{.x = range_.x_range().second, .y = y_value},
            convert_color(config_.grid().color()), line_width, range_,
            plot_region_margin_);
    }
}

void Plotter::write_plot_title(Image& image) {
    if (config_.plot_title().empty()) {
        return;
    }
    const auto size = image.size;
    const auto color = convert_color(config_.plot_title_color());

    const auto& text = config_.plot_title();
    const int font_size = config_.plot_title_font_size();
    text_renderer_.font_size(font_size);
    const auto [text_height, text_width] = text_renderer_.text_size(text);

    cv::Point top_left_position(config_.base_margin().left(),
        plot_region_margin_.top() - config_.plot_title_margin());
    top_left_position = adjust_text_position(top_left_position,
        cv::Size(text_width, text_height), cv::Size(size[1], size[0]));

    text_renderer_.render_text(image, text, top_left_position, color);
}

void Plotter::write_x_axis(Image& image) {
    const auto size = image.size;

    const auto color = convert_color(config_.axes().color());

    // Draw the x-axis at the bottom in the plot.
    const Real y_value = range_.y_range().first;

    if (!config_.axes().x_axis_title().empty()) {
        const auto& text = config_.axes().x_axis_title();
        const int font_size = config_.axes().axes_title_font_size();
        text_renderer_.font_size(font_size);
        const auto [text_height, text_width] = text_renderer_.text_size(text);

        const double x_value =
            (range_.x_range().first + range_.x_range().second) * 0.5;
        const auto base_position =
            convert_position(Point{.x = x_value, .y = y_value}, range_,
                plot_region_margin_, size);
        auto top_left_position = cv::Point(base_position.x - text_width / 2,
            base_position.y + config_.axes().tick_label_margin() * 2 +
                x_axis_tick_height_ + text_height);
        top_left_position = adjust_text_position(top_left_position,
            cv::Size(text_width, text_height), cv::Size(size[1], size[0]));

        text_renderer_.render_text(image, text, top_left_position, color);
    }

    write_line(image, Point{.x = range_.x_range().first, .y = y_value},
        Point{.x = range_.x_range().second, .y = y_value}, color,
        config_.axes().line_width(), range_, plot_region_margin_);

    const int font_size = config_.axes().tick_label_font_size();
    text_renderer_.font_size(font_size);

    assert(x_axis_ticks_.values.size() == x_axis_ticks_.strings.size());
    for (std::size_t i = 0; i < x_axis_ticks_.values.size(); ++i) {
        const Real x_value = x_axis_ticks_.values[i];

        const auto text = x_axis_ticks_.strings[i];
        const auto [text_height, text_width] = text_renderer_.text_size(text);

        const auto base_position =
            convert_position(Point{.x = x_value, .y = y_value}, range_,
                plot_region_margin_, size);
        const int tick_margin = config_.axes().tick_label_margin();
        auto top_left_position = cv::Point(base_position.x - text_width / 2,
            base_position.y + tick_margin + text_height);
        top_left_position = adjust_text_position(top_left_position,
            cv::Size(text_width, text_height), cv::Size(size[1], size[0]));

        text_renderer_.render_text(image, text, top_left_position, color);
    }
}

void Plotter::write_y_axis(Image& image) {
    const auto size = image.size;

    const auto color = convert_color(config_.axes().color());

    // Draw the y-axis at the left in the plot.
    const Real x_value = range_.x_range().first;

    if (!config_.axes().y_axis_title().empty()) {
        const auto& text = config_.axes().y_axis_title();
        const int font_size = config_.axes().axes_title_font_size();
        text_renderer_.font_size(font_size);
        const auto [text_height, text_width] = text_renderer_.text_size(text);

        const double y_value =
            (range_.y_range().first + range_.y_range().second) * 0.5;
        const auto base_position =
            convert_position(Point{.x = x_value, .y = y_value}, range_,
                plot_region_margin_, size);
        auto top_left_position =
            cv::Point(base_position.x - config_.axes().tick_label_margin() * 2 -
                    y_axis_tick_width_ - text_width,
                base_position.y + text_height / 2);
        top_left_position = adjust_text_position(top_left_position,
            cv::Size(text_width, text_height), cv::Size(size[1], size[0]));

        text_renderer_.render_text(image, text, top_left_position, color);
    }

    write_line(image, Point{.x = x_value, .y = range_.y_range().first},
        Point{.x = x_value, .y = range_.y_range().second}, color,
        config_.axes().line_width(), range_, plot_region_margin_);

    const int font_size = config_.axes().tick_label_font_size();
    text_renderer_.font_size(font_size);

    assert(y_axis_ticks_.values.size() == y_axis_ticks_.strings.size());
    for (std::size_t i = 0; i < y_axis_ticks_.values.size(); ++i) {
        const Real y_value = y_axis_ticks_.values[i];

        const auto text = y_axis_ticks_.strings[i];
        const auto [text_height, text_width] = text_renderer_.text_size(text);

        const auto base_position =
            convert_position(Point{.x = x_value, .y = y_value}, range_,
                plot_region_margin_, size);
        const int tick_margin = config_.axes().tick_label_margin();
        cv::Point top_left_position;
        top_left_position =
            cv::Point(base_position.x - tick_margin - text_width,
                base_position.y + text_height / 2);
        top_left_position = adjust_text_position(top_left_position,
            cv::Size(text_width, text_height), cv::Size(size[1], size[0]));

        text_renderer_.render_text(image, text, top_left_position, color);
    }
}

void Plotter::update_internal_parameters() {
    // At first, try with the desired image size.
    actual_height_ = desired_height_;
    actual_width_ = desired_width_;

    // Prevent too small image sizes before iterating to adjust them.
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

    const double desired_aspect_ratio = static_cast<double>(desired_width_) /
        static_cast<double>(desired_height_);

    constexpr std::size_t max_retries = 50;
    constexpr double image_size_increment_scale = 1.1;
    for (std::size_t i = 0; i < max_retries; ++i) {
        if (try_update_internal_parameters()) {
            return;
        }
        actual_height_ =
            static_cast<int>(actual_height_ * image_size_increment_scale);
        actual_width_ = static_cast<int>(desired_aspect_ratio * actual_height_);
    }
    // This should not occur in normal circumstances because 1.1^50*300
    // (approximately 35217) is large enough.
    throw std::runtime_error("Failed to tune parameters for plots.");
}

bool Plotter::try_update_internal_parameters() {
    // Margin of the overall graphics.
    plot_region_margin_ = config_.base_margin();

    // Handle the plot title.
    if (!config_.plot_title().empty()) {
        const int additional_margin =
            plot_title_height() + config_.plot_title_margin();
        plot_region_margin_.top(plot_region_margin_.top() + additional_margin);
    }

    // Handle axis titles.
    if (!config_.axes().x_axis_title().empty()) {
        const int additional_margin =
            x_axis_title_height() + config_.axes().tick_label_margin();
        plot_region_margin_.bottom(
            plot_region_margin_.bottom() + additional_margin);
    }
    if (!config_.axes().y_axis_title().empty()) {
        const int additional_margin =
            y_axis_title_width() + config_.axes().tick_label_margin();
        plot_region_margin_.left(
            plot_region_margin_.left() + additional_margin);
    }

    // Handle ticks.
    update_axis_ticks();
    update_x_axis_tick_height();
    update_y_axis_tick_width();
    plot_region_margin_.bottom(plot_region_margin_.bottom() +
        x_axis_tick_height_ + config_.axes().tick_label_margin());
    plot_region_margin_.left(plot_region_margin_.left() + y_axis_tick_width_ +
        config_.axes().tick_label_margin());

    // Handle minimum margins.
    plot_region_margin_.expand_to_at_least(config_.min_plot_margin());

    // Finally, check the available area for the plot region.
    const int available_height = actual_height_ - plot_region_margin_.top() -
        plot_region_margin_.bottom();
    const int available_width = actual_width_ - plot_region_margin_.left() -
        plot_region_margin_.right();
    // Use the tick spacing as the minimum size.
    const auto min_available_height =
        static_cast<int>(config_.axes().num_pixels_per_tick_in_y_axis());
    const auto min_available_width =
        static_cast<int>(config_.axes().num_pixels_per_tick_in_x_axis());
    return available_height > min_available_height &&
        available_width > min_available_width;
}

int Plotter::plot_title_height() {
    const int font_size = config_.plot_title_font_size();
    text_renderer_.font_size(font_size);
    const auto [text_height, text_width] =
        text_renderer_.text_size(config_.plot_title());
    return text_height;
}

void Plotter::update_axis_ticks() {
    auto margin = plot_region_margin_;
    // TODO Use approximate sizes of ticks here.

    margin.expand_to_at_least(config_.min_plot_margin());

    const int available_width = actual_width_ - margin.left() - margin.right();
    const int available_height =
        actual_height_ - margin.top() - margin.bottom();
    const auto approx_num_ticks_x = static_cast<std::size_t>(std::round(
        static_cast<double>(available_width) /
        static_cast<double>(config_.axes().num_pixels_per_tick_in_x_axis())));
    const auto approx_num_ticks_y = static_cast<std::size_t>(std::round(
        static_cast<double>(available_height) /
        static_cast<double>(config_.axes().num_pixels_per_tick_in_y_axis())));
    // Too small values will be automatically adjusted by generate_axis_ticks.

    generate_axis_ticks(range_.x_range(), approx_num_ticks_x, x_axis_ticks_);
    generate_axis_ticks(range_.y_range(), approx_num_ticks_y, y_axis_ticks_);
}

void Plotter::update_x_axis_tick_height() {
    int height = 0;
    const int font_size = config_.axes().tick_label_font_size();
    text_renderer_.font_size(font_size);
    for (const auto& str : x_axis_ticks_.strings) {
        const auto [text_height, text_width] = text_renderer_.text_size(str);
        height = std::max(height, text_height);
    }
    x_axis_tick_height_ = height;
}

void Plotter::update_y_axis_tick_width() {
    int width = 0;
    const int font_size = config_.axes().tick_label_font_size();
    text_renderer_.font_size(font_size);
    for (const auto& str : y_axis_ticks_.strings) {
        const auto [text_height, text_width] = text_renderer_.text_size(str);
        width = std::max(width, text_width);
    }
    y_axis_tick_width_ = width;
}

int Plotter::x_axis_title_height() {
    const int font_size = config_.axes().axes_title_font_size();
    text_renderer_.font_size(font_size);
    const auto [text_height, text_width] =
        text_renderer_.text_size(config_.axes().x_axis_title());
    return text_height;
}

int Plotter::y_axis_title_width() {
    const int font_size = config_.axes().axes_title_font_size();
    text_renderer_.font_size(font_size);
    const auto [text_height, text_width] =
        text_renderer_.text_size(config_.axes().y_axis_title());
    return text_width;
}

}  // namespace func_sketch::plotter
