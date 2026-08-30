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

Margin& PlotConfig::min_plot_margin() noexcept { return min_plot_margin_; }

const Margin& PlotConfig::min_plot_margin() const noexcept {
    return min_plot_margin_;
}

Margin& PlotConfig::base_margin() noexcept { return base_margin_; }

const Margin& PlotConfig::base_margin() const noexcept { return base_margin_; }

AxesConfig& PlotConfig::axes() noexcept { return axes_; }

const AxesConfig& PlotConfig::axes() const noexcept { return axes_; }

GridConfig& PlotConfig::grid() noexcept { return grid_; }

const GridConfig& PlotConfig::grid() const noexcept { return grid_; }

SamplingConfig& PlotConfig::sampling() noexcept { return sampling_; }

const SamplingConfig& PlotConfig::sampling() const noexcept {
    return sampling_;
}

PlotConfig& PlotConfig::plot_title(std::string value) {
    plot_title_ = std::move(value);
    return *this;
}

PlotConfig& PlotConfig::plot_title_font_size(int value) {
    if (value < 0) {
        throw InvalidArgumentException(
            "Plot title font size must be non-negative");
    }
    plot_title_font_size_ = value;
    return *this;
}

PlotConfig& PlotConfig::plot_title_margin(int value) {
    if (value < 0) {
        throw InvalidArgumentException(
            "Plot title margin must be non-negative");
    }
    plot_title_margin_ = value;
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

const std::string& PlotConfig::plot_title() const noexcept {
    return plot_title_;
}

int PlotConfig::plot_title_font_size() const noexcept {
    return plot_title_font_size_;
}

int PlotConfig::plot_title_margin() const noexcept {
    return plot_title_margin_;
}

int PlotConfig::curve_line_width() const noexcept { return curve_line_width_; }

const RGBColor& PlotConfig::background_color() const noexcept {
    return background_color_;
}

}  // namespace func_sketch::plotter
