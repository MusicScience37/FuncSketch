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
#include <cstddef>

#include <fmt/format.h>
#include <opencv2/imgproc.hpp>

#include "func_sketch/exceptions.h"
#include "func_sketch/plotter/curve_writer.h"
#include "func_sketch/plotter/plotting_util.h"
#include "func_sketch/plotter/point.h"

namespace func_sketch::plotter {

// NOLINTNEXTLINE(*-pass-by-value): Wrong warning for small objects.
Plotter::Plotter(const PlotRange& range, const PlotConfig& config)
    : range_(range),
      config_(config),
      point_converter_(
          plot_region_margin_, range_, actual_height_, actual_width_) {
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
    desired_height_ = std::max(height, 1);
    desired_width_ = std::max(width, 1);
    update_internal_parameters();
    return *this;
}

[[nodiscard]] std::pair<int, int> Plotter::actual_size() const noexcept {
    return {actual_height_, actual_width_};
}

[[nodiscard]] const PointConverter& Plotter::point_converter() const noexcept {
    return point_converter_;
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

    title_writer_.write(image, plot_region_margin_, config_);
    axes_writer_.write(image, config_, range_, point_converter_);
}

void Plotter::write_curve(
    const std::vector<Point>& samples, const RGBColor& color, Image& image) {
    const auto size = image.size;
    if (size.dims() != 2 || size[0] != actual_height_ ||
        size[1] != actual_width_) {
        throw InvalidArgumentException("Invalid image size.");
    }

    CurveWriter::write_curve(
        samples, color, image, config_, range_, point_converter_);
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
    throw AlgorithmFailureException("Failed to tune parameters for plots.");
}

bool Plotter::try_update_internal_parameters() {
    // Start from the margin of the overall graphics.
    plot_region_margin_ = config_.base_margin();

    title_writer_.prepare(plot_region_margin_, config_);

    axes_writer_.prepare(
        plot_region_margin_, config_, range_, actual_height_, actual_width_);

    plot_region_margin_.expand_to_at_least(config_.min_plot_margin());

    // Finally, check the available area for the plot region.
    const int available_height = actual_height_ - plot_region_margin_.top() -
        plot_region_margin_.bottom();
    const int available_width = actual_width_ - plot_region_margin_.left() -
        plot_region_margin_.right();
    // Use the tick spacing as the minimum size to prevent no ticks.
    const auto min_available_height =
        static_cast<int>(config_.axes().num_pixels_per_tick_in_y_axis());
    const auto min_available_width =
        static_cast<int>(config_.axes().num_pixels_per_tick_in_x_axis());
    if (available_height <= min_available_height ||
        available_width <= min_available_width) {
        return false;
    }

    point_converter_ = PointConverter(
        plot_region_margin_, range_, actual_height_, actual_width_);
    return true;
}

}  // namespace func_sketch::plotter
