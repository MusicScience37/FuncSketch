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
 * \brief Implementation of PlotRange struct.
 */
#include "func_sketch/plotter/plot_range.h"

#include <cmath>

#include <fmt/format.h>

#include "func_sketch/exceptions.h"

namespace func_sketch::plotter {

PlotRange::PlotRange(const std::pair<double, double>& x_range,
    const std::pair<double, double>& y_range)
    : x_range_(x_range), y_range_(y_range) {
    if (!std::isfinite(x_range.first) || !std::isfinite(x_range.second)) {
        throw InvalidArgumentException("Invalid X range: not finite");
    }
    if (!std::isfinite(y_range.first) || !std::isfinite(y_range.second)) {
        throw InvalidArgumentException("Invalid Y range: not finite");
    }
    if (x_range.first >= x_range.second) {
        throw InvalidArgumentException("Invalid X range: min >= max");
    }
    if (y_range.first >= y_range.second) {
        throw InvalidArgumentException("Invalid Y range: min >= max");
    }
}

auto PlotRange::x_range() const noexcept -> std::pair<double, double> {
    return x_range_;
}

auto PlotRange::y_range() const noexcept -> std::pair<double, double> {
    return y_range_;
}

bool PlotRange::contains(const Point& point) const noexcept {
    return std::isfinite(point.x) && std::isfinite(point.y) &&
        x_range_.first <= point.x && point.x <= x_range_.second &&
        y_range_.first <= point.y && point.y <= y_range_.second;
}

void PlotRange::zoom(const Point& center, double factor) {
    if (!std::isfinite(factor) || factor <= 0.0) {
        throw InvalidArgumentException(
            "Invalid factor for zooming: must be a finite positive number");
    }

    x_range_.first = center.x + (x_range_.first - center.x) / factor;
    x_range_.second = center.x + (x_range_.second - center.x) / factor;
    y_range_.first = center.y + (y_range_.first - center.y) / factor;
    y_range_.second = center.y + (y_range_.second - center.y) / factor;
}

void PlotRange::pan(const Point& diff) {
    if (!std::isfinite(diff.x) || !std::isfinite(diff.y)) {
        throw InvalidArgumentException(
            "Invalid difference for panning: must be a finite number");
    }

    x_range_.first += diff.x;
    x_range_.second += diff.x;
    y_range_.first += diff.y;
    y_range_.second += diff.y;
}

}  // namespace func_sketch::plotter

// NOLINTNEXTLINE(*-static): API of an external library.
auto fmt::formatter<func_sketch::plotter::PlotRange>::format(
    const func_sketch::plotter::PlotRange& value, format_context& context) const
    -> format_context::iterator {
    return fmt::format_to(context.out(),
        "PlotRange(x_range=({}, {}), y_range=({}, {}))", value.x_range().first,
        value.x_range().second, value.y_range().first, value.y_range().second);
}
