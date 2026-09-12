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
 * \brief Implementation of AxesWriter class.
 */
#include "func_sketch/plotter/axes_writer.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>

#include <opencv2/core.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/plotter/plotting_util.h"
#include "func_sketch/plotter/point.h"

namespace func_sketch::plotter {

void AxesWriter::prepare(Margin& plot_region_margin, const PlotConfig& config,
    const PlotRange& range, int height, int width) {
    // Handle axis titles.
    if (!config.axes().x_axis_title().empty()) {
        const int additional_margin =
            x_axis_title_height(config) + config.axes().tick_label_margin();
        plot_region_margin.bottom(
            plot_region_margin.bottom() + additional_margin);
    }
    if (!config.axes().y_axis_title().empty()) {
        const int additional_margin =
            y_axis_title_width(config) + config.axes().tick_label_margin();
        plot_region_margin.left(plot_region_margin.left() + additional_margin);
    }

    // Handle ticks.
    update_axis_ticks(plot_region_margin, config, range, height, width);
    update_x_axis_tick_height(config);
    update_y_axis_tick_width(config);
    plot_region_margin.bottom(plot_region_margin.bottom() +
        x_axis_tick_height_ + config.axes().tick_label_margin());
    plot_region_margin.left(plot_region_margin.left() + y_axis_tick_width_ +
        config.axes().tick_label_margin());
}

void AxesWriter::write(Image& image, const PlotConfig& config,
    const PlotRange& range, const PointConverter& point_converter) {
    write_grid_lines(image, config, range, point_converter);
    write_x_axis(image, config, range, point_converter);
    write_y_axis(image, config, range, point_converter);
}

void AxesWriter::write_grid_lines(Image& image, const PlotConfig& config,
    const PlotRange& range, const PointConverter& point_converter) {
    // vertical lines.
    for (const Real x_value : x_axis_ticks_.values) {
        const int line_width = (x_value == 0.0)
            ? config.grid().zero_line_width()
            : config.grid().line_width();
        write_line(image, Point{.x = x_value, .y = range.y_range().first},
            Point{.x = x_value, .y = range.y_range().second},
            convert_color(config.grid().color()), line_width, point_converter);
    }
    // horizontal lines.
    for (const Real y_value : y_axis_ticks_.values) {
        const int line_width = (y_value == 0.0)
            ? config.grid().zero_line_width()
            : config.grid().line_width();
        write_line(image, Point{.x = range.x_range().first, .y = y_value},
            Point{.x = range.x_range().second, .y = y_value},
            convert_color(config.grid().color()), line_width, point_converter);
    }
}

void AxesWriter::write_x_axis(Image& image, const PlotConfig& config,
    const PlotRange& range, const PointConverter& point_converter) {
    const auto size = image.size;

    const auto color = convert_color(config.axes().color());

    // Draw the x-axis at the bottom in the plot.
    const Real y_value = range.y_range().first;

    if (!config.axes().x_axis_title().empty()) {
        const auto& text = config.axes().x_axis_title();
        const int font_size = config.axes().axes_title_font_size();
        text_renderer_.font_size(font_size);
        const auto [text_height, text_width] = text_renderer_.text_size(text);

        const double x_value =
            (range.x_range().first + range.x_range().second) * 0.5;
        const auto base_position = point_converter.convert_plot_to_image(
            Point{.x = x_value, .y = y_value});
        auto top_left_position = cv::Point(base_position.x - text_width / 2,
            base_position.y + config.axes().tick_label_margin() * 2 +
                x_axis_tick_height_ + text_height);
        top_left_position = adjust_text_position(top_left_position,
            cv::Size(text_width, text_height), cv::Size(size[1], size[0]));

        text_renderer_.render_text(image, text, top_left_position, color);
    }

    write_line(image, Point{.x = range.x_range().first, .y = y_value},
        Point{.x = range.x_range().second, .y = y_value}, color,
        config.axes().line_width(), point_converter);

    const int font_size = config.axes().tick_label_font_size();
    text_renderer_.font_size(font_size);

    assert(x_axis_ticks_.values.size() == x_axis_ticks_.strings.size());
    for (std::size_t i = 0; i < x_axis_ticks_.values.size(); ++i) {
        const Real x_value = x_axis_ticks_.values[i];

        const auto text = x_axis_ticks_.strings[i];
        const auto [text_height, text_width] = text_renderer_.text_size(text);

        const auto base_position = point_converter.convert_plot_to_image(
            Point{.x = x_value, .y = y_value});
        const int tick_margin = config.axes().tick_label_margin();
        auto top_left_position = cv::Point(base_position.x - text_width / 2,
            base_position.y + tick_margin + text_height);
        top_left_position = adjust_text_position(top_left_position,
            cv::Size(text_width, text_height), cv::Size(size[1], size[0]));

        text_renderer_.render_text(image, text, top_left_position, color);
    }
}

void AxesWriter::write_y_axis(Image& image, const PlotConfig& config,
    const PlotRange& range, const PointConverter& point_converter) {
    const auto size = image.size;

    const auto color = convert_color(config.axes().color());

    // Draw the y-axis at the left in the plot.
    const Real x_value = range.x_range().first;

    if (!config.axes().y_axis_title().empty()) {
        const auto& text = config.axes().y_axis_title();
        const int font_size = config.axes().axes_title_font_size();
        text_renderer_.font_size(font_size);
        const auto [text_height, text_width] = text_renderer_.text_size(text);

        const double y_value =
            (range.y_range().first + range.y_range().second) * 0.5;
        const auto base_position = point_converter.convert_plot_to_image(
            Point{.x = x_value, .y = y_value});
        auto top_left_position =
            cv::Point(base_position.x - config.axes().tick_label_margin() * 2 -
                    y_axis_tick_width_ - text_width,
                base_position.y + text_height / 2);
        top_left_position = adjust_text_position(top_left_position,
            cv::Size(text_width, text_height), cv::Size(size[1], size[0]));

        text_renderer_.render_text(image, text, top_left_position, color);
    }

    write_line(image, Point{.x = x_value, .y = range.y_range().first},
        Point{.x = x_value, .y = range.y_range().second}, color,
        config.axes().line_width(), point_converter);

    const int font_size = config.axes().tick_label_font_size();
    text_renderer_.font_size(font_size);

    assert(y_axis_ticks_.values.size() == y_axis_ticks_.strings.size());
    for (std::size_t i = 0; i < y_axis_ticks_.values.size(); ++i) {
        const Real y_value = y_axis_ticks_.values[i];

        const auto text = y_axis_ticks_.strings[i];
        const auto [text_height, text_width] = text_renderer_.text_size(text);

        const auto base_position = point_converter.convert_plot_to_image(
            Point{.x = x_value, .y = y_value});
        const int tick_margin = config.axes().tick_label_margin();
        cv::Point top_left_position;
        top_left_position =
            cv::Point(base_position.x - tick_margin - text_width,
                base_position.y + text_height / 2);
        top_left_position = adjust_text_position(top_left_position,
            cv::Size(text_width, text_height), cv::Size(size[1], size[0]));

        text_renderer_.render_text(image, text, top_left_position, color);
    }
}

void AxesWriter::update_axis_ticks(const Margin& plot_region_margin,
    const PlotConfig& config, const PlotRange& range, int height, int width) {
    auto margin = plot_region_margin;
    // TODO Use approximate sizes of ticks here.

    margin.expand_to_at_least(config.min_plot_margin());

    const int available_width = width - margin.left() - margin.right();
    const int available_height = height - margin.top() - margin.bottom();
    const auto approx_num_ticks_x = static_cast<std::size_t>(std::round(
        static_cast<double>(available_width) /
        static_cast<double>(config.axes().num_pixels_per_tick_in_x_axis())));
    const auto approx_num_ticks_y = static_cast<std::size_t>(std::round(
        static_cast<double>(available_height) /
        static_cast<double>(config.axes().num_pixels_per_tick_in_y_axis())));
    // Too small values will be automatically adjusted by generate_axis_ticks.

    generate_axis_ticks(range.x_range(), approx_num_ticks_x, x_axis_ticks_);
    generate_axis_ticks(range.y_range(), approx_num_ticks_y, y_axis_ticks_);
}

void AxesWriter::update_x_axis_tick_height(const PlotConfig& config) {
    int height = 0;
    const int font_size = config.axes().tick_label_font_size();
    text_renderer_.font_size(font_size);
    for (const auto& str : x_axis_ticks_.strings) {
        const auto [text_height, text_width] = text_renderer_.text_size(str);
        height = std::max(height, text_height);
    }
    x_axis_tick_height_ = height;
}

void AxesWriter::update_y_axis_tick_width(const PlotConfig& config) {
    int width = 0;
    const int font_size = config.axes().tick_label_font_size();
    text_renderer_.font_size(font_size);
    for (const auto& str : y_axis_ticks_.strings) {
        const auto [text_height, text_width] = text_renderer_.text_size(str);
        width = std::max(width, text_width);
    }
    y_axis_tick_width_ = width;
}

int AxesWriter::x_axis_title_height(const PlotConfig& config) {
    const int font_size = config.axes().axes_title_font_size();
    text_renderer_.font_size(font_size);
    const auto [text_height, text_width] =
        text_renderer_.text_size(config.axes().x_axis_title());
    return text_height;
}

int AxesWriter::y_axis_title_width(const PlotConfig& config) {
    const int font_size = config.axes().axes_title_font_size();
    text_renderer_.font_size(font_size);
    const auto [text_height, text_width] =
        text_renderer_.text_size(config.axes().y_axis_title());
    return text_width;
}

}  // namespace func_sketch::plotter
