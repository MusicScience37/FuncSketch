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
 * \brief Test of SamplingConfig class.
 */
#include "func_sketch/plotter/sampling_config.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("func_sketch::plotter::SamplingConfig") {
    using func_sketch::plotter::SamplingConfig;

    SECTION("set and get initial number of sample points") {
        SamplingConfig config;

        CHECK(config.initial_num_sample_points() ==
            func_sketch::plotter::default_initial_num_sample_points);

        CHECK_NOTHROW(config.initial_num_sample_points(200));
        CHECK(config.initial_num_sample_points() == 200);

        CHECK_THROWS(config.initial_num_sample_points(0));
        CHECK(config.initial_num_sample_points() == 200);

        CHECK_THROWS(config.initial_num_sample_points(1));
        CHECK(config.initial_num_sample_points() == 200);

        CHECK_NOTHROW(config.initial_num_sample_points(2));
        CHECK(config.initial_num_sample_points() == 2);

        CHECK_NOTHROW(config.initial_num_sample_points(3));
        CHECK(config.initial_num_sample_points() == 3);
    }

    SECTION("set and get maximum number of sample points") {
        SamplingConfig config;

        CHECK(config.max_num_sample_points() ==
            func_sketch::plotter::default_max_num_sample_points);

        CHECK_NOTHROW(config.max_num_sample_points(2000));
        CHECK(config.max_num_sample_points() == 2000);

        CHECK_THROWS(config.max_num_sample_points(0));
        CHECK(config.max_num_sample_points() == 2000);

        CHECK_THROWS(config.max_num_sample_points(1));
        CHECK(config.max_num_sample_points() == 2000);

        CHECK_NOTHROW(config.max_num_sample_points(2));
        CHECK(config.max_num_sample_points() == 2);

        CHECK_NOTHROW(config.max_num_sample_points(
            func_sketch::plotter::max_max_num_sample_points));
        CHECK(config.max_num_sample_points() ==
            func_sketch::plotter::max_max_num_sample_points);

        CHECK_THROWS(config.max_num_sample_points(
            func_sketch::plotter::max_max_num_sample_points + 1));
        CHECK(config.max_num_sample_points() ==
            func_sketch::plotter::max_max_num_sample_points);
    }

    SECTION("set and get maximum coordinate change rate") {
        SamplingConfig config;

        CHECK(config.max_coordinate_change_rate() ==
            func_sketch::plotter::default_max_coordinate_change_rate);

        CHECK_NOTHROW(config.max_coordinate_change_rate(0.05));
        CHECK(config.max_coordinate_change_rate() == 0.05);

        CHECK_THROWS(config.max_coordinate_change_rate(0.0));
        CHECK(config.max_coordinate_change_rate() == 0.05);

        CHECK_THROWS(config.max_coordinate_change_rate(-0.01));
        CHECK(config.max_coordinate_change_rate() == 0.05);
    }

    SECTION("set and get slope change threshold") {
        SamplingConfig config;

        CHECK(config.slope_change_threshold() ==
            func_sketch::plotter::default_slope_change_threshold);

        CHECK_NOTHROW(config.slope_change_threshold(0.5));
        CHECK(config.slope_change_threshold() == 0.5);

        CHECK_THROWS(config.slope_change_threshold(0.0));
        CHECK(config.slope_change_threshold() == 0.5);

        CHECK_THROWS(config.slope_change_threshold(-0.1));
        CHECK(config.slope_change_threshold() == 0.5);
    }

    SECTION("set and get minimum parameter change rate") {
        SamplingConfig config;

        CHECK(config.min_param_change_rate() ==
            func_sketch::plotter::default_min_param_change_rate);

        CHECK_NOTHROW(config.min_param_change_rate(0.01));
        CHECK(config.min_param_change_rate() == 0.01);

        CHECK_NOTHROW(config.min_param_change_rate(
            func_sketch::plotter::min_min_param_change_rate));
        CHECK(config.min_param_change_rate() ==
            func_sketch::plotter::min_min_param_change_rate);

        CHECK_THROWS(config.min_param_change_rate(
            func_sketch::plotter::min_min_param_change_rate / 2.0));
        CHECK(config.min_param_change_rate() ==
            func_sketch::plotter::min_min_param_change_rate);
    }
}
