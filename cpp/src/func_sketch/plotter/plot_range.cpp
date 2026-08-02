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

#include <fmt/format.h>

// NOLINTNEXTLINE(*-static): API of an external library.
auto fmt::formatter<func_sketch::plotter::PlotRange>::format(
    const func_sketch::plotter::PlotRange& value, format_context& context) const
    -> format_context::iterator {
    return fmt::format_to(context.out(),
        "PlotRange(x_range=({}, {}), y_range=({}, {}))", value.x_range.first,
        value.x_range.second, value.y_range.first, value.y_range.second);
}
