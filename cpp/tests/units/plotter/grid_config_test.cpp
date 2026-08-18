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
 * \brief Test of GridConfig class.
 */
#include "func_sketch/plotter/grid_config.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("func_sketch::plotter::GridConfig") {
    using func_sketch::plotter::GridConfig;

    SECTION("set and get line width") {
        GridConfig config;

        CHECK(config.line_width() ==
            func_sketch::plotter::default_grid_line_width);

        CHECK_NOTHROW(config.line_width(2));
        CHECK(config.line_width() == 2);

        CHECK_THROWS(config.line_width(-1));
        CHECK(config.line_width() == 2);

        CHECK_NOTHROW(config.line_width(0));
        CHECK(config.line_width() == 0);

        CHECK_NOTHROW(config.line_width(1));
        CHECK(config.line_width() == 1);
    }

    SECTION("set and get zero line width") {
        GridConfig config;

        CHECK(config.zero_line_width() ==
            func_sketch::plotter::default_zero_line_width);

        CHECK_NOTHROW(config.zero_line_width(3));
        CHECK(config.zero_line_width() == 3);

        CHECK_THROWS(config.zero_line_width(-1));
        CHECK(config.zero_line_width() == 3);

        CHECK_NOTHROW(config.zero_line_width(0));
        CHECK(config.zero_line_width() == 0);

        CHECK_NOTHROW(config.zero_line_width(1));
        CHECK(config.zero_line_width() == 1);
    }

    SECTION("set and get color") {
        using func_sketch::plotter::RGBColor;

        GridConfig config;

        CHECK(config.color() == func_sketch::plotter::default_grid_color);

        const RGBColor new_color{.r = 100, .g = 150, .b = 200};
        CHECK_NOTHROW(config.color(new_color));
        CHECK(config.color() == new_color);

        const RGBColor light_gray{.r = 220, .g = 220, .b = 220};
        CHECK_NOTHROW(config.color(light_gray));
        CHECK(config.color() == light_gray);
    }
}
