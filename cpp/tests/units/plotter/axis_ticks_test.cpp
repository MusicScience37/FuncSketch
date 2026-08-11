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
 * \brief Test of AxisTicks class.
 */
#include "func_sketch/plotter/axis_ticks.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("func_sketch::plotter::AxisTicks") {
    using func_sketch::plotter::AxisTicks;
    using func_sketch::plotter::generate_axis_ticks;

    SECTION("generate ticks for top digit 1 and small range") {
        constexpr std::pair<double, double> range{-36, 26};
        constexpr std::size_t approx_num_ticks = 7;
        // Tick interval: 10

        AxisTicks ticks;
        generate_axis_ticks(range, approx_num_ticks, ticks);

        REQUIRE(ticks.values.size() == 6);
        constexpr double tolerance = 1e-10;
        CHECK_THAT(
            ticks.values.at(0), Catch::Matchers::WithinAbs(-30.0, tolerance));
        CHECK_THAT(
            ticks.values.at(1), Catch::Matchers::WithinAbs(-20.0, tolerance));
        CHECK_THAT(
            ticks.values.at(2), Catch::Matchers::WithinAbs(-10.0, tolerance));
        CHECK_THAT(
            ticks.values.at(3), Catch::Matchers::WithinAbs(0.0, tolerance));
        CHECK_THAT(
            ticks.values.at(4), Catch::Matchers::WithinAbs(10.0, tolerance));
        CHECK_THAT(
            ticks.values.at(5), Catch::Matchers::WithinAbs(20.0, tolerance));
    }

    // TODO Remaining tests.
}
