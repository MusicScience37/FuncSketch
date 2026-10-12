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
 * \brief Implementation of validate_bounds function.
 */
#include "func_sketch/utilities/validate_bounds.h"

#include <algorithm>
#include <cmath>

#include <fmt/format.h>

#include "func_sketch/exceptions.h"

namespace func_sketch::utilities {

void validate_bounds(
    const std::pair<double, double>& bounds, std::string_view name) {
    if (!std::isfinite(bounds.first) || !std::isfinite(bounds.second)) {
        throw InvalidArgumentException(
            fmt::format("Invalid {} range: not finite", name));
    }
    if (bounds.first >= bounds.second) {
        throw InvalidArgumentException(
            fmt::format("Invalid {} range: min >= max", name));
    }
    const double range_size = bounds.second - bounds.first;
    if (!std::isfinite(range_size)) {
        throw InvalidArgumentException(
            fmt::format("Invalid {} range: size not finite", name));
    }
    // Too small ranges cause loss of precision in calculations.
    constexpr double min_range_size = 1e-300;
    constexpr double min_relative_range_size = 1e-12;
    if (range_size < min_range_size) {
        throw InvalidArgumentException(
            fmt::format("Invalid {} range: size too small", name));
    }
    const double max_abs_bound =
        std::max(std::abs(bounds.first), std::abs(bounds.second));
    if (range_size < max_abs_bound * min_relative_range_size) {
        throw InvalidArgumentException(fmt::format(
            "Invalid {} range: size too small relative to the bounds", name));
    }
}

}  // namespace func_sketch::utilities
