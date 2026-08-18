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
 * \brief Implementation of GridConfig class.
 */
#include "func_sketch/plotter/grid_config.h"

#include "func_sketch/exceptions.h"

namespace func_sketch::plotter {

GridConfig& GridConfig::line_width(int value) {
    if (value < 0) {
        throw InvalidArgumentException("Grid line width must be non-negative");
    }
    line_width_ = value;
    return *this;
}

GridConfig& GridConfig::zero_line_width(int value) {
    if (value < 0) {
        throw InvalidArgumentException("Zero line width must be non-negative");
    }
    zero_line_width_ = value;
    return *this;
}

GridConfig& GridConfig::color(const RGBColor& value) {
    color_ = value;
    return *this;
}

int GridConfig::line_width() const noexcept { return line_width_; }

int GridConfig::zero_line_width() const noexcept { return zero_line_width_; }

const RGBColor& GridConfig::color() const noexcept { return color_; }

}  // namespace func_sketch::plotter
