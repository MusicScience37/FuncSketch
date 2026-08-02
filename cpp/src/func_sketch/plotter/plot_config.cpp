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

int PlotConfig::left_margin() const noexcept { return left_margin_; }

int PlotConfig::right_margin() const noexcept { return right_margin_; }

int PlotConfig::top_margin() const noexcept { return top_margin_; }

int PlotConfig::bottom_margin() const noexcept { return bottom_margin_; }

int PlotConfig::tick_label_font_size() const noexcept {
    return tick_label_font_size_;
}

int PlotConfig::axes_line_width() const noexcept { return axes_line_width_; }

int PlotConfig::grid_line_width() const noexcept { return grid_line_width_; }

int PlotConfig::curve_line_width() const noexcept { return curve_line_width_; }

const RGBColor& PlotConfig::background_color() const noexcept {
    return background_color_;
}

const RGBColor& PlotConfig::axes_color() const noexcept { return axes_color_; }

const RGBColor& PlotConfig::grid_color() const noexcept { return grid_color_; }

}  // namespace func_sketch::plotter
