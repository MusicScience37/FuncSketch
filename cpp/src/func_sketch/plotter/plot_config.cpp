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
 * \brief Implementation of PlotConfig class.
 */
#include "func_sketch/plotter/plot_config.h"

#include <fmt/format.h>

#include "func_sketch/exceptions.h"

namespace func_sketch::plotter {

PlotConfig& PlotConfig::left_margin(int value) {
    if (value < 0) {
        throw InvalidArgumentException("Left margin must be non-negative");
    }
    left_margin_ = value;
    return *this;
}

PlotConfig& PlotConfig::right_margin(int value) {
    if (value < 0) {
        throw InvalidArgumentException("Right margin must be non-negative");
    }
    right_margin_ = value;
    return *this;
}

PlotConfig& PlotConfig::top_margin(int value) {
    if (value < 0) {
        throw InvalidArgumentException("Top margin must be non-negative");
    }
    top_margin_ = value;
    return *this;
}

PlotConfig& PlotConfig::bottom_margin(int value) {
    if (value < 0) {
        throw InvalidArgumentException("Bottom margin must be non-negative");
    }
    bottom_margin_ = value;
    return *this;
}

PlotConfig& PlotConfig::tick_label_font_size(int value) {
    if (value < 0) {
        throw InvalidArgumentException(
            "Tick label font size must be non-negative");
    }
    tick_label_font_size_ = value;
    return *this;
}

PlotConfig& PlotConfig::axes_line_width(int value) {
    if (value < 0) {
        throw InvalidArgumentException("Axes line width must be non-negative");
    }
    axes_line_width_ = value;
    return *this;
}

PlotConfig& PlotConfig::grid_line_width(int value) {
    if (value < 0) {
        throw InvalidArgumentException("Grid line width must be non-negative");
    }
    grid_line_width_ = value;
    return *this;
}

PlotConfig& PlotConfig::zero_line_width(int value) {
    if (value < 0) {
        throw InvalidArgumentException("Zero line width must be non-negative");
    }
    zero_line_width_ = value;
    return *this;
}

PlotConfig& PlotConfig::curve_line_width(int value) {
    if (value < 0) {
        throw InvalidArgumentException("Curve line width must be non-negative");
    }
    curve_line_width_ = value;
    return *this;
}

PlotConfig& PlotConfig::background_color(const RGBColor& value) {
    background_color_ = value;
    return *this;
}

PlotConfig& PlotConfig::axes_color(const RGBColor& value) {
    axes_color_ = value;
    return *this;
}

PlotConfig& PlotConfig::grid_color(const RGBColor& value) {
    grid_color_ = value;
    return *this;
}

PlotConfig& PlotConfig::initial_num_sample_points(std::size_t value) {
    if (value < 2) {
        throw InvalidArgumentException(
            "Number of sample points must be at least 2");
    }
    initial_num_sample_points_ = value;
    return *this;
}

PlotConfig& PlotConfig::max_num_sample_points(std::size_t value) {
    if (value < 2) {
        throw InvalidArgumentException(
            "Number of sample points must be at least 2.");
    }
    if (value > max_max_num_sample_points) {
        throw InvalidArgumentException(
            fmt::format("Number of sample points must be at most {}",
                max_max_num_sample_points));
    }
    max_num_sample_points_ = value;
    return *this;
}

PlotConfig& PlotConfig::max_coordinate_change_rate(double value) {
    if (value <= 0.0) {
        throw InvalidArgumentException(
            "Maximum coordinate change rate must be positive.");
    }
    max_coordinate_change_rate_ = value;
    return *this;
}

PlotConfig& PlotConfig::slope_change_threshold(double value) {
    if (value <= 0.0) {
        throw InvalidArgumentException(
            "Slope change threshold must be positive.");
    }
    slope_change_threshold_ = value;
    return *this;
}

PlotConfig& PlotConfig::min_param_change_rate(double value) {
    if (value < min_min_param_change_rate) {
        throw InvalidArgumentException(
            fmt::format("Minimum parameter change rate must be at least {}",
                min_min_param_change_rate));
    }
    min_param_change_rate_ = value;
    return *this;
}

PlotConfig& PlotConfig::num_pixels_per_tick_in_x_axis(std::size_t value) {
    if (value == 0) {
        throw InvalidArgumentException(
            "Number of pixels per tick in the x-axis must be positive.");
    }
    num_pixels_per_tick_in_x_axis_ = value;
    return *this;
}

PlotConfig& PlotConfig::num_pixels_per_tick_in_y_axis(std::size_t value) {
    if (value == 0) {
        throw InvalidArgumentException(
            "Number of pixels per tick in the y-axis must be positive.");
    }
    num_pixels_per_tick_in_y_axis_ = value;
    return *this;
}

int PlotConfig::left_margin() const noexcept { return left_margin_; }

int PlotConfig::right_margin() const noexcept { return right_margin_; }

int PlotConfig::top_margin() const noexcept { return top_margin_; }

int PlotConfig::bottom_margin() const noexcept { return bottom_margin_; }

int PlotConfig::tick_label_font_size() const noexcept {
    return tick_label_font_size_;
}

int PlotConfig::axes_line_width() const noexcept { return axes_line_width_; }

int PlotConfig::grid_line_width() const noexcept { return grid_line_width_; }

int PlotConfig::zero_line_width() const noexcept { return zero_line_width_; }

int PlotConfig::curve_line_width() const noexcept { return curve_line_width_; }

const RGBColor& PlotConfig::background_color() const noexcept {
    return background_color_;
}

const RGBColor& PlotConfig::axes_color() const noexcept { return axes_color_; }

const RGBColor& PlotConfig::grid_color() const noexcept { return grid_color_; }

std::size_t PlotConfig::initial_num_sample_points() const noexcept {
    return initial_num_sample_points_;
}

std::size_t PlotConfig::max_num_sample_points() const noexcept {
    return max_num_sample_points_;
}

double PlotConfig::max_coordinate_change_rate() const noexcept {
    return max_coordinate_change_rate_;
}

double PlotConfig::slope_change_threshold() const noexcept {
    return slope_change_threshold_;
}

double PlotConfig::min_param_change_rate() const noexcept {
    return min_param_change_rate_;
}

std::size_t PlotConfig::num_pixels_per_tick_in_x_axis() const noexcept {
    return num_pixels_per_tick_in_x_axis_;
}

std::size_t PlotConfig::num_pixels_per_tick_in_y_axis() const noexcept {
    return num_pixels_per_tick_in_y_axis_;
}

}  // namespace func_sketch::plotter
