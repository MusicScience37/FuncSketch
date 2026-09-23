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
 * \brief Test of LegendConfig class.
 */
#include "func_sketch/plotter/legend_config.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("func_sketch::plotter::LegendConfig") {
    using func_sketch::plotter::LegendConfig;

    SECTION("set and get visibility") {
        LegendConfig config;

        CHECK(config.visible() == func_sketch::plotter::default_legend_visible);

        CHECK_NOTHROW(config.visible(false));
        CHECK_FALSE(config.visible());

        CHECK_NOTHROW(config.visible(true));
        CHECK(config.visible());
    }

    SECTION("set and get title") {
        LegendConfig config;

        CHECK(config.title() == func_sketch::plotter::default_legend_title);

        CHECK_NOTHROW(config.title("Functions"));
        CHECK(config.title() == "Functions");

        CHECK_NOTHROW(config.title(""));
        CHECK(config.title().empty());
    }

    SECTION("set and get title font size") {
        LegendConfig config;

        CHECK(config.title_font_size() ==
            func_sketch::plotter::default_legend_title_font_size);

        CHECK_NOTHROW(config.title_font_size(14));
        CHECK(config.title_font_size() == 14);

        CHECK_THROWS(config.title_font_size(-1));
        CHECK(config.title_font_size() == 14);

        CHECK_NOTHROW(config.title_font_size(0));
        CHECK(config.title_font_size() == 0);

        CHECK_NOTHROW(config.title_font_size(1));
        CHECK(config.title_font_size() == 1);
    }

    SECTION("set and get font size of curve names") {
        LegendConfig config;

        CHECK(config.curve_name_font_size() ==
            func_sketch::plotter::default_legend_curve_name_font_size);

        CHECK_NOTHROW(config.curve_name_font_size(14));
        CHECK(config.curve_name_font_size() == 14);

        CHECK_THROWS(config.curve_name_font_size(-1));
        CHECK(config.curve_name_font_size() == 14);

        CHECK_NOTHROW(config.curve_name_font_size(0));
        CHECK(config.curve_name_font_size() == 0);

        CHECK_NOTHROW(config.curve_name_font_size(1));
        CHECK(config.curve_name_font_size() == 1);
    }

    SECTION("set and get color") {
        using func_sketch::plotter::RGBColor;

        LegendConfig config;

        CHECK(config.color() == func_sketch::plotter::default_legend_color);

        const RGBColor new_color{.r = 100, .g = 150, .b = 200};
        CHECK_NOTHROW(config.color(new_color));
        CHECK(config.color() == new_color);
    }

    SECTION("set and get entry spacing") {
        LegendConfig config;

        CHECK(config.entry_spacing() ==
            func_sketch::plotter::default_legend_entry_spacing);

        CHECK_NOTHROW(config.entry_spacing(14));
        CHECK(config.entry_spacing() == 14);

        CHECK_THROWS(config.entry_spacing(-1));
        CHECK(config.entry_spacing() == 14);

        CHECK_NOTHROW(config.entry_spacing(0));
        CHECK(config.entry_spacing() == 0);

        CHECK_NOTHROW(config.entry_spacing(1));
        CHECK(config.entry_spacing() == 1);
    }

    SECTION("set and get margin") {
        LegendConfig config;

        CHECK(config.margin() == func_sketch::plotter::default_legend_margin);

        CHECK_NOTHROW(config.margin(14));
        CHECK(config.margin() == 14);

        CHECK_THROWS(config.margin(-1));
        CHECK(config.margin() == 14);

        CHECK_NOTHROW(config.margin(0));
        CHECK(config.margin() == 0);

        CHECK_NOTHROW(config.margin(1));
        CHECK(config.margin() == 1);
    }

    SECTION("set and get curve line length") {
        LegendConfig config;

        CHECK(config.curve_line_length() ==
            func_sketch::plotter::default_legend_curve_line_length);

        CHECK_NOTHROW(config.curve_line_length(14));
        CHECK(config.curve_line_length() == 14);

        CHECK_THROWS(config.curve_line_length(-1));
        CHECK(config.curve_line_length() == 14);

        CHECK_NOTHROW(config.curve_line_length(0));
        CHECK(config.curve_line_length() == 0);

        CHECK_NOTHROW(config.curve_line_length(1));
        CHECK(config.curve_line_length() == 1);
    }

    SECTION("set and get spacing between curve line and name") {
        LegendConfig config;

        CHECK(config.curve_line_name_spacing() ==
            func_sketch::plotter::default_legend_curve_line_name_spacing);

        CHECK_NOTHROW(config.curve_line_name_spacing(14));
        CHECK(config.curve_line_name_spacing() == 14);

        CHECK_THROWS(config.curve_line_name_spacing(-1));
        CHECK(config.curve_line_name_spacing() == 14);

        CHECK_NOTHROW(config.curve_line_name_spacing(0));
        CHECK(config.curve_line_name_spacing() == 0);

        CHECK_NOTHROW(config.curve_line_name_spacing(1));
        CHECK(config.curve_line_name_spacing() == 1);
    }
}
