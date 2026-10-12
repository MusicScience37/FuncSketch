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

#include <cmath>
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

    SECTION("sample a simple function") {
        const auto range = PlotRange({-1.0, 1.0}, {-1.0, 1.0});
        const auto config = SamplingConfig();
        auto sampler = PointSampler(range, config);

        const auto func = [](Real param) {
            if (std::abs(param) < std::numeric_limits<Real>::epsilon()) {
                return Point{.x = param, .y = param};
            }
            return Point{.x = param, .y = std::sin(1.0 / param)};
        };
        const auto points = sampler(func, range.x_range());

        // Check the order of sampled points.
        REQUIRE(points.size() >= config.initial_num_sample_points());
        for (std::size_t i = 0; i < points.size() - 1; ++i) {
            INFO("i = " << i);
            CHECK(points[i].x < points[i + 1].x);
        }
    }

    SECTION("sample a function with singularity") {
        const auto range = PlotRange({-1.0, 1.0}, {-1.0, 1.0});
        const auto config = SamplingConfig();
        auto sampler = PointSampler(range, config);

        const auto func = [](Real param) {
            return Point{.x = param, .y = 1.0 / param};
        };
        const auto points = sampler(func, range.x_range());

        // Check the order of sampled points.
        REQUIRE(points.size() >= config.initial_num_sample_points());
        for (std::size_t i = 0; i < points.size() - 1; ++i) {
            INFO("i = " << i);
            CHECK(points[i].x < points[i + 1].x);
        }
    }

    SECTION("sample a function with discontinuity") {
        const auto range = PlotRange({-1.0, 1.0}, {-1.0, 1.0});
        const auto config = SamplingConfig();
        auto sampler = PointSampler(range, config);

        const auto func = [](Real param) {
            return Point{.x = param, .y = 0.5 * std::round(param)};
        };
        const auto points = sampler(func, range.x_range());

        // Check the order of sampled points.
        REQUIRE(points.size() >= config.initial_num_sample_points());
        for (std::size_t i = 0; i < points.size() - 1; ++i) {
            INFO("i = " << i);
            CHECK(points[i].x < points[i + 1].x);
        }
    }

    SECTION("sample a function with infinite oscillation") {
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

        // Check the order of sampled points.
        REQUIRE(points.size() >= config.initial_num_sample_points());
        for (std::size_t i = 0; i < points.size() - 1; ++i) {
            INFO("i = " << i);
            CHECK(points[i].x < points[i + 1].x);
        }
    }

    SECTION("throw an exception for invalid parameter ranges") {
        const auto range = PlotRange({-1.0, 1.0}, {-1.0, 1.0});
        const auto config = SamplingConfig();
        auto sampler = PointSampler(range, config);

        const auto func = [](Real param) {
            return Point{.x = param, .y = param};
        };
        constexpr Real inf = std::numeric_limits<Real>::infinity();
        constexpr Real nan = std::numeric_limits<Real>::quiet_NaN();
        CHECK_THROWS((void)sampler(func, {1.0, -1.0}));
        CHECK_THROWS((void)sampler(func, {1.0, 1.0}));
        CHECK_THROWS((void)sampler(func, {-inf, 1.0}));
        CHECK_THROWS((void)sampler(func, {-1.0, inf}));
        CHECK_THROWS((void)sampler(func, {nan, 1.0}));
    }
}
