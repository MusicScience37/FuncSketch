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
 * \brief Implementation of CurveWriter class.
 */
#include "func_sketch/plotter/curve_writer.h"

#include <cmath>
#include <cstddef>

#include "func_sketch/plotter/plotting_util.h"
#include "func_sketch/plotter/point.h"

namespace func_sketch::plotter {

void CurveWriter::write_curve(const std::vector<Point>& samples,
    const RGBColor& color, Image& image, const PlotConfig& config,
    const PlotRange& range, const PointConverter& point_converter) {
    const auto cv_color = convert_color(color);
    const int line_width = config.curve_line_width();

    const std::size_t num_samples = samples.size();
    if (num_samples < 2) {
        return;
    }
    for (std::size_t i = 0; i < num_samples - 1; ++i) {
        Point start_xy = samples[i];
        Point end_xy = samples[i + 1];

        const bool is_start_in_range = range.contains(start_xy);
        const bool is_end_in_range = range.contains(end_xy);
        if (!is_start_in_range && !is_end_in_range) {
            // In this case, the range of the line segment may contain a
            // singularity of the function.
            continue;
        }

        if (std::isnan(start_xy.x) || std::isnan(start_xy.y) ||
            std::isnan(end_xy.x) || std::isnan(end_xy.y)) {
            // NaN cannot be fixed.
            continue;
        }

        if (!is_start_in_range) {
            if (!try_clamp_infinity(start_xy, range)) {
                continue;
            }
            start_xy = compute_intersection_with_range(end_xy, start_xy, range);
        }
        if (!is_end_in_range) {
            if (!try_clamp_infinity(end_xy, range)) {
                continue;
            }
            end_xy = compute_intersection_with_range(start_xy, end_xy, range);
        }

        write_line(
            image, start_xy, end_xy, cv_color, line_width, point_converter);
    }
}

}  // namespace func_sketch::plotter
