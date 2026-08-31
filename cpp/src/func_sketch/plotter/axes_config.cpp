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
 * \brief Implementation of AxesConfig class.
 */
#include "func_sketch/plotter/axes_config.h"

#include "func_sketch/exceptions.h"

namespace func_sketch::plotter {

AxesConfig& AxesConfig::x_axis_title(std::string value) {
    x_axis_title_ = std::move(value);
    return *this;
}

AxesConfig& AxesConfig::y_axis_title(std::string value) {
    y_axis_title_ = std::move(value);
    return *this;
}

AxesConfig& AxesConfig::axes_title_font_size(int value) {
    if (value < 0) {
        throw InvalidArgumentException(
            "Axes title font size must be non-negative");
    }
    axes_title_font_size_ = value;
    return *this;
}

AxesConfig& AxesConfig::tick_label_font_size(int value) {
    if (value < 0) {
        throw InvalidArgumentException(
            "Tick label font size must be non-negative");
    }
    tick_label_font_size_ = value;
    return *this;
}

AxesConfig& AxesConfig::tick_label_margin(int value) {
    if (value < 0) {
        throw InvalidArgumentException(
            "Tick label margin must be non-negative");
    }
    tick_label_margin_ = value;
    return *this;
}

AxesConfig& AxesConfig::line_width(int value) {
    if (value < 0) {
        throw InvalidArgumentException("Axes line width must be non-negative");
    }
    line_width_ = value;
    return *this;
}

AxesConfig& AxesConfig::color(const RGBColor& value) {
    color_ = value;
    return *this;
}

AxesConfig& AxesConfig::num_pixels_per_tick_in_x_axis(std::size_t value) {
    if (value == 0) {
        throw InvalidArgumentException(
            "Number of pixels per tick in the x-axis must be positive.");
    }
    num_pixels_per_tick_in_x_axis_ = value;
    return *this;
}

AxesConfig& AxesConfig::num_pixels_per_tick_in_y_axis(std::size_t value) {
    if (value == 0) {
        throw InvalidArgumentException(
            "Number of pixels per tick in the y-axis must be positive.");
    }
    num_pixels_per_tick_in_y_axis_ = value;
    return *this;
}

const std::string& AxesConfig::x_axis_title() const noexcept {
    return x_axis_title_;
}

const std::string& AxesConfig::y_axis_title() const noexcept {
    return y_axis_title_;
}

int AxesConfig::axes_title_font_size() const noexcept {
    return axes_title_font_size_;
}

int AxesConfig::tick_label_font_size() const noexcept {
    return tick_label_font_size_;
}

int AxesConfig::tick_label_margin() const noexcept {
    return tick_label_margin_;
}

int AxesConfig::line_width() const noexcept { return line_width_; }

const RGBColor& AxesConfig::color() const noexcept { return color_; }

std::size_t AxesConfig::num_pixels_per_tick_in_x_axis() const noexcept {
    return num_pixels_per_tick_in_x_axis_;
}

std::size_t AxesConfig::num_pixels_per_tick_in_y_axis() const noexcept {
    return num_pixels_per_tick_in_y_axis_;
}

}  // namespace func_sketch::plotter
