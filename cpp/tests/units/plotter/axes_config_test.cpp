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
 * \brief Test of AxesConfig class.
 */
#include "func_sketch/plotter/axes_config.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("func_sketch::plotter::AxesConfig") {
    using func_sketch::plotter::AxesConfig;

    SECTION("set and get x-axis title") {
        AxesConfig config;

        CHECK(config.x_axis_title() ==
            func_sketch::plotter::default_x_axis_title);

        CHECK_NOTHROW(config.x_axis_title("Time"));
        CHECK(config.x_axis_title() == "Time");

        CHECK_NOTHROW(config.x_axis_title(""));
        CHECK(config.x_axis_title().empty());
    }

    SECTION("set and get y-axis title") {
        AxesConfig config;

        CHECK(config.y_axis_title() ==
            func_sketch::plotter::default_y_axis_title);

        CHECK_NOTHROW(config.y_axis_title("Value"));
        CHECK(config.y_axis_title() == "Value");

        CHECK_NOTHROW(config.y_axis_title(""));
        CHECK(config.y_axis_title().empty());
    }

    SECTION("set and get font size of titles of axes") {
        AxesConfig config;

        CHECK(config.axes_title_font_size() ==
            func_sketch::plotter::default_axes_title_font_size);

        CHECK_NOTHROW(config.axes_title_font_size(14));
        CHECK(config.axes_title_font_size() == 14);

        CHECK_THROWS(config.axes_title_font_size(-1));
        CHECK(config.axes_title_font_size() == 14);

        CHECK_NOTHROW(config.axes_title_font_size(0));
        CHECK(config.axes_title_font_size() == 0);

        CHECK_NOTHROW(config.axes_title_font_size(1));
        CHECK(config.axes_title_font_size() == 1);
    }

    SECTION("set and get tick label font size") {
        AxesConfig config;

        CHECK(config.tick_label_font_size() ==
            func_sketch::plotter::default_tick_label_font_size);

        CHECK_NOTHROW(config.tick_label_font_size(14));
        CHECK(config.tick_label_font_size() == 14);

        CHECK_THROWS(config.tick_label_font_size(-1));
        CHECK(config.tick_label_font_size() == 14);

        CHECK_NOTHROW(config.tick_label_font_size(0));
        CHECK(config.tick_label_font_size() == 0);

        CHECK_NOTHROW(config.tick_label_font_size(1));
        CHECK(config.tick_label_font_size() == 1);
    }

    SECTION("set and get tick label margin") {
        AxesConfig config;

        CHECK(config.tick_label_margin() ==
            func_sketch::plotter::default_tick_label_margin);

        CHECK_NOTHROW(config.tick_label_margin(14));
        CHECK(config.tick_label_margin() == 14);

        CHECK_THROWS(config.tick_label_margin(-1));
        CHECK(config.tick_label_margin() == 14);

        CHECK_NOTHROW(config.tick_label_margin(0));
        CHECK(config.tick_label_margin() == 0);

        CHECK_NOTHROW(config.tick_label_margin(1));
        CHECK(config.tick_label_margin() == 1);
    }

    SECTION("set and get axes line width") {
        AxesConfig config;

        CHECK(config.line_width() ==
            func_sketch::plotter::default_axes_line_width);

        CHECK_NOTHROW(config.line_width(5));
        CHECK(config.line_width() == 5);

        CHECK_THROWS(config.line_width(-1));
        CHECK(config.line_width() == 5);

        CHECK_NOTHROW(config.line_width(0));
        CHECK(config.line_width() == 0);

        CHECK_NOTHROW(config.line_width(1));
        CHECK(config.line_width() == 1);
    }

    SECTION("set and get axes color") {
        using func_sketch::plotter::RGBColor;

        AxesConfig config;

        CHECK(config.color() == func_sketch::plotter::default_axes_color);

        const RGBColor new_color{.r = 50, .g = 100, .b = 150};
        CHECK_NOTHROW(config.color(new_color));
        CHECK(config.color() == new_color);

        const RGBColor white{.r = 255, .g = 255, .b = 255};
        CHECK_NOTHROW(config.color(white));
        CHECK(config.color() == white);
    }

    SECTION("set and get number of pixels per tick in the x-axis") {
        AxesConfig config;

        CHECK(config.num_pixels_per_tick_in_x_axis() ==
            func_sketch::plotter::default_num_pixels_per_tick_in_x_axis);

        CHECK_NOTHROW(config.num_pixels_per_tick_in_x_axis(150));
        CHECK(config.num_pixels_per_tick_in_x_axis() == 150);

        CHECK_THROWS(config.num_pixels_per_tick_in_x_axis(0));
        CHECK(config.num_pixels_per_tick_in_x_axis() == 150);

        CHECK_NOTHROW(config.num_pixels_per_tick_in_x_axis(1));
        CHECK(config.num_pixels_per_tick_in_x_axis() == 1);
    }

    SECTION("set and get number of pixels per tick in the y-axis") {
        AxesConfig config;

        CHECK(config.num_pixels_per_tick_in_y_axis() ==
            func_sketch::plotter::default_num_pixels_per_tick_in_y_axis);

        CHECK_NOTHROW(config.num_pixels_per_tick_in_y_axis(150));
        CHECK(config.num_pixels_per_tick_in_y_axis() == 150);

        CHECK_THROWS(config.num_pixels_per_tick_in_y_axis(0));
        CHECK(config.num_pixels_per_tick_in_y_axis() == 150);

        CHECK_NOTHROW(config.num_pixels_per_tick_in_y_axis(1));
        CHECK(config.num_pixels_per_tick_in_y_axis() == 1);
    }
}
