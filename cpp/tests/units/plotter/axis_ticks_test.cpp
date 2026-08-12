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

    SECTION("generate ticks for top digit 1 and range order in 0 to 10000") {
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

        REQUIRE(ticks.strings.size() == 6);
        CHECK(ticks.strings.at(0) == "-30");
        CHECK(ticks.strings.at(1) == "-20");
        CHECK(ticks.strings.at(2) == "-10");
        CHECK(ticks.strings.at(3) == "0");
        CHECK(ticks.strings.at(4) == "10");
        CHECK(ticks.strings.at(5) == "20");
    }

    SECTION("generate ticks for top digit 2 and range order in 1e-4 to 0") {
        constexpr std::pair<double, double> range{-0.01, 0.1};
        constexpr std::size_t approx_num_ticks = 6;
        // Tick interval: 0.02

        AxisTicks ticks;
        generate_axis_ticks(range, approx_num_ticks, ticks);

        REQUIRE(ticks.values.size() == 6);
        constexpr double tolerance = 1e-10;
        CHECK_THAT(
            ticks.values.at(0), Catch::Matchers::WithinAbs(0.0, tolerance));
        CHECK_THAT(
            ticks.values.at(1), Catch::Matchers::WithinAbs(0.02, tolerance));
        CHECK_THAT(
            ticks.values.at(2), Catch::Matchers::WithinAbs(0.04, tolerance));
        CHECK_THAT(
            ticks.values.at(3), Catch::Matchers::WithinAbs(0.06, tolerance));
        CHECK_THAT(
            ticks.values.at(4), Catch::Matchers::WithinAbs(0.08, tolerance));
        CHECK_THAT(
            ticks.values.at(5), Catch::Matchers::WithinAbs(0.1, tolerance));

        REQUIRE(ticks.strings.size() == 6);
        CHECK(ticks.strings.at(0) == "0.00");
        CHECK(ticks.strings.at(1) == "0.02");
        CHECK(ticks.strings.at(2) == "0.04");
        CHECK(ticks.strings.at(3) == "0.06");
        CHECK(ticks.strings.at(4) == "0.08");
        CHECK(ticks.strings.at(5) == "0.10");
    }

    SECTION(
        "generate ticks for top digit 5 and range order greater than 1e+4") {
        constexpr std::pair<double, double> range{1e+5, 2e+5};
        constexpr std::size_t approx_num_ticks = 3;
        // Tick interval: 5e+4

        AxisTicks ticks;
        generate_axis_ticks(range, approx_num_ticks, ticks);

        REQUIRE(ticks.values.size() == 3);
        constexpr double tolerance = 1e-5;
        CHECK_THAT(
            ticks.values.at(0), Catch::Matchers::WithinAbs(1e+5, tolerance));
        CHECK_THAT(
            ticks.values.at(1), Catch::Matchers::WithinAbs(1.5e+5, tolerance));
        CHECK_THAT(
            ticks.values.at(2), Catch::Matchers::WithinAbs(2e+5, tolerance));

        REQUIRE(ticks.strings.size() == 3);
        CHECK(ticks.strings.at(0) == "1.0e+5");
        CHECK(ticks.strings.at(1) == "1.5e+5");
        CHECK(ticks.strings.at(2) == "2.0e+5");
    }

    SECTION("generate ticks for top digit 1 and range order less than 1e-4") {
        constexpr std::pair<double, double> range{1e-5, 4.9e-5};
        constexpr std::size_t approx_num_ticks = 4;
        // Tick interval: 1e-5

        AxisTicks ticks;
        generate_axis_ticks(range, approx_num_ticks, ticks);

        REQUIRE(ticks.values.size() == 4);
        constexpr double tolerance = 1e-10;
        CHECK_THAT(
            ticks.values.at(0), Catch::Matchers::WithinAbs(1e-5, tolerance));
        CHECK_THAT(
            ticks.values.at(1), Catch::Matchers::WithinAbs(2e-5, tolerance));
        CHECK_THAT(
            ticks.values.at(2), Catch::Matchers::WithinAbs(3e-5, tolerance));
        CHECK_THAT(
            ticks.values.at(3), Catch::Matchers::WithinAbs(4e-5, tolerance));

        REQUIRE(ticks.strings.size() == 4);
        CHECK(ticks.strings.at(0) == "1e-5");
        CHECK(ticks.strings.at(1) == "2e-5");
        CHECK(ticks.strings.at(2) == "3e-5");
        CHECK(ticks.strings.at(3) == "4e-5");
    }

    SECTION("check the number of ticks") {
        constexpr std::pair<double, double> range{0.0, 1.0};

        AxisTicks ticks;
        CHECK_THROWS(generate_axis_ticks(range, 0, ticks));
        CHECK_THROWS(generate_axis_ticks(range, 1, ticks));
        CHECK_THROWS(generate_axis_ticks(range, 2, ticks));
        CHECK_NOTHROW(generate_axis_ticks(range, 3, ticks));
        CHECK(ticks.values.size() >= 2);
        CHECK_NOTHROW(generate_axis_ticks(range, 4, ticks));
        CHECK(ticks.values.size() >= 2);
    }
}
