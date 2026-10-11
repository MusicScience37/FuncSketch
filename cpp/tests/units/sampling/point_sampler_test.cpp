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
 * \brief Tests for PointSampler class.
 */
#include "func_sketch/sampling/point_sampler.h"

#include <cstdlib>
#include <limits>

#include <catch2/catch_test_macros.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/plotter/plot_range.h"
#include "func_sketch/point.h"

TEST_CASE("func_sketch::sampling::PointSampler") {
    using func_sketch::Point;
    using func_sketch::Real;
    using func_sketch::plotter::PlotRange;
    using func_sketch::sampling::PointSampler;
    using func_sketch::sampling::SamplingConfig;

    SECTION("sample points in the order of the parameter") {
        const auto range = PlotRange({-1.0, 1.0}, {-1.0, 1.0});
        const auto config = SamplingConfig();
        auto sampler = PointSampler(range, config);

        const auto func = [](Real param) {
            if (std::abs(param) < std::numeric_limits<Real>::epsilon()) {
                return Point{.x = param, .y = 0.0};
            }
            return Point{.x = param, .y = std::sin(1.0 / param)};
        };
        const auto points = sampler(func, range.x_range());

        REQUIRE(points.size() >= config.initial_num_sample_points());
        for (std::size_t i = 0; i < points.size() - 1; ++i) {
            INFO("i = " << i);
            CHECK(points[i].x < points[i + 1].x);
        }
    }
}
