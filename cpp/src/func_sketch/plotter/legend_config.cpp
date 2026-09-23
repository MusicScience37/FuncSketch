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
 * \brief Implementation of LegendConfig class.
 */
#include "func_sketch/plotter/legend_config.h"

#include <utility>

#include "func_sketch/exceptions.h"

namespace func_sketch::plotter {

LegendConfig& LegendConfig::visible(bool value) noexcept {
    visible_ = value;
    return *this;
}

LegendConfig& LegendConfig::title(std::string value) {
    title_ = std::move(value);
    return *this;
}

LegendConfig& LegendConfig::title_font_size(int value) {
    if (value < 0) {
        throw InvalidArgumentException(
            "Legend title font size must be non-negative.");
    }
    title_font_size_ = value;
    return *this;
}

LegendConfig& LegendConfig::curve_name_font_size(int value) {
    if (value < 0) {
        throw InvalidArgumentException(
            "Font size of curve names in the legend must be non-negative.");
    }
    curve_name_font_size_ = value;
    return *this;
}

LegendConfig& LegendConfig::entry_spacing(int value) {
    if (value < 0) {
        throw InvalidArgumentException(
            "Spacing between legend entries must be non-negative.");
    }
    entry_spacing_ = value;
    return *this;
}

LegendConfig& LegendConfig::margin(int value) {
    if (value < 0) {
        throw InvalidArgumentException("Legend margin must be non-negative.");
    }
    margin_ = value;
    return *this;
}

LegendConfig& LegendConfig::curve_line_length(int value) {
    if (value < 0) {
        throw InvalidArgumentException(
            "Length of lines in the legend must be non-negative.");
    }
    curve_line_length_ = value;
    return *this;
}

LegendConfig& LegendConfig::curve_line_name_spacing(int value) {
    if (value < 0) {
        throw InvalidArgumentException(
            "Spacing between lines and curve names in the legend must be "
            "non-negative.");
    }
    curve_line_name_spacing_ = value;
    return *this;
}

bool LegendConfig::visible() const noexcept { return visible_; }

const std::string& LegendConfig::title() const noexcept { return title_; }

int LegendConfig::title_font_size() const noexcept { return title_font_size_; }

int LegendConfig::curve_name_font_size() const noexcept {
    return curve_name_font_size_;
}

int LegendConfig::entry_spacing() const noexcept { return entry_spacing_; }

int LegendConfig::margin() const noexcept { return margin_; }

int LegendConfig::curve_line_length() const noexcept {
    return curve_line_length_;
}

int LegendConfig::curve_line_name_spacing() const noexcept {
    return curve_line_name_spacing_;
}

}  // namespace func_sketch::plotter
