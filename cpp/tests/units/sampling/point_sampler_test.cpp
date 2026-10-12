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

#include <array>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <utility>

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
            return Point{.x = param, .y = param};
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

    SECTION("sample with a range with large numbers") {
        const auto range =
            PlotRange({1.0e10, 1.0e10 + 1.0}, {1.0e10, 1.0e10 + 1.0});
        const auto config = SamplingConfig();
        auto sampler = PointSampler(range, config);

        const auto func = [](Real param) {
            return Point{.x = param, .y = param};
        };
        const auto points = sampler(func, range.x_range());

        // Check the order of sampled points.
        REQUIRE(points.size() >= config.initial_num_sample_points());
        for (std::size_t i = 0; i < points.size() - 1; ++i) {
            INFO("i = " << i);
            CHECK(points[i].x < points[i + 1].x);
        }
    }

    SECTION("sample with extreme ranges allowed in PlotRange") {
        constexpr std::array<std::pair<Real, Real>, 7> ranges{{
            {0.0, 1.01e-300},
            {-1.01e-300, 0.0},
            {1e-288, 1e-288 + 1.01e-300},
            {1e+15, 1e+15 + 1.01e+3},
            {-1e+15 - 1.01e+3, -1e+15},
            {1e+300, 1.00000000000101e+300},
            {-8e+307, 8e+307},
        }};
        const auto config = SamplingConfig();
        const auto func = [](Real param) {
            return Point{.x = param, .y = param};
        };

        for (const auto& x_range : ranges) {
            INFO("range = (" << x_range.first << ", " << x_range.second << ")");
            const auto range = PlotRange(x_range, x_range);
            auto sampler = PointSampler(range, config);

            const auto points = sampler(func, range.x_range());

            // Check the order of sampled points.
            // The number of points can be smaller than the configured initial
            // number of sample points due to the precision of parameters.
            REQUIRE(points.size() >= 2);
            CHECK(points.size() <= config.max_num_sample_points() + 1);
            for (std::size_t i = 0; i < points.size() - 1; ++i) {
                INFO("i = " << i);
                CHECK(points[i].x < points[i + 1].x);
            }
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
        CHECK_THROWS((void)sampler(func, {-1e+308, 1e+308}));
        CHECK_THROWS((void)sampler(func, {0.0, 0.99e-300}));
        CHECK_THROWS((void)sampler(func, {1e+15, 1e+15 + 0.99e+3}));
    }
}
