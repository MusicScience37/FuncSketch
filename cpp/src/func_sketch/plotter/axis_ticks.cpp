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
 * \brief Implementation of AxisTicks class.
 */
#include "func_sketch/plotter/axis_ticks.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <ranges>

#include <fmt/format.h>

#include "func_sketch/exceptions.h"

namespace func_sketch::plotter {

void generate_axis_ticks(const std::pair<Real, Real>& range,
    std::size_t approx_num_ticks, AxisTicks& ticks) {
    if (approx_num_ticks < 2) {
        throw InvalidArgumentException("Number of ticks must be at least 2.");
    }

    const auto [min_value, max_value] = range;
    const Real range_size = max_value - min_value;
    // Ranges should be checked in PlotRange class, so only assert here.
    assert(range_size > 0.0);
    const Real approx_tick_interval =
        range_size / static_cast<Real>(approx_num_ticks - 1);

    auto tick_interval_digits =
        static_cast<int>(std::floor(std::log10(approx_tick_interval)));
    Real tick_interval_order = std::pow(10.0, tick_interval_digits);
    Real tick_interval_number = approx_tick_interval / tick_interval_order;
    // Round tick interval to "nice numbers" (1, 2, 5, 10, ...).
    if (tick_interval_number < 1.5) {
        tick_interval_number = 1.0;
    } else if (tick_interval_number < 3.5) {
        tick_interval_number = 2.0;
    } else if (tick_interval_number < 7.5) {
        tick_interval_number = 5.0;
    } else {
        tick_interval_number = 1.0;
        tick_interval_digits += 1;
        tick_interval_order *= 10.0;
    }
    const Real tick_interval = tick_interval_number * tick_interval_order;

    using TickIndexType =
        std::int_fast64_t;  // Prevent overflow in conversions from double.
    const auto min_tick_index =
        static_cast<TickIndexType>(std::ceil(min_value / tick_interval));
    const auto max_tick_index =
        static_cast<TickIndexType>(std::floor(max_value / tick_interval));
    const auto num_ticks =
        static_cast<std::size_t>(max_tick_index - min_tick_index + 1);
    ticks.values.resize(num_ticks);
    ticks.strings.resize(num_ticks);

    // Generate tick values.
    std::ranges::copy(std::views::iota(min_tick_index, max_tick_index + 1) |
            std::views::transform([tick_interval](TickIndexType index) {
                return static_cast<Real>(index) * tick_interval;
            }),
        ticks.values.begin());

    // Format tick values according to the order of magnitude.
    const int tick_digits = static_cast<int>(std::floor(
        std::log10(std::max(std::abs(min_value), std::abs(max_value)))));
    const Real tick_order = std::pow(10.0, tick_digits);
    constexpr int digits_threshold_for_scientific_notation = 4;
    if (std::abs(tick_digits) >= digits_threshold_for_scientific_notation) {
        const int tick_digits_after_decimal_point =
            std::max(tick_digits - tick_interval_digits, 0);
        std::ranges::transform(ticks.values, ticks.strings.begin(),
            [tick_order, tick_digits, tick_digits_after_decimal_point](
                Real value) {
                const Real tick_number = value / tick_order;
                return fmt::format("{:.{}f}e{:+}", tick_number,
                    tick_digits_after_decimal_point, tick_digits);
            });
    } else {
        const int tick_digits_after_decimal_point =
            std::max(-tick_interval_digits, 0);
        std::ranges::transform(ticks.values, ticks.strings.begin(),
            [tick_digits_after_decimal_point](Real value) {
                return fmt::format(
                    "{:.{}f}", value, tick_digits_after_decimal_point);
            });
    }
}

}  // namespace func_sketch::plotter
