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
 * \brief Test of PlotConfig class.
 */
#include "func_sketch/plotter/plot_config.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("func_sketch::plotter::PlotConfig") {
    using func_sketch::plotter::PlotConfig;

    SECTION("set and get left margin") {
        PlotConfig config;

        CHECK(config.left_margin() == func_sketch::plotter::default_margins);

        CHECK_NOTHROW(config.left_margin(7));
        CHECK(config.left_margin() == 7);

        CHECK_THROWS(config.left_margin(-1));
        CHECK(config.left_margin() == 7);

        CHECK_NOTHROW(config.left_margin(0));
        CHECK(config.left_margin() == 0);

        CHECK_NOTHROW(config.left_margin(1));
        CHECK(config.left_margin() == 1);
    }

    SECTION("set and get right margin") {
        PlotConfig config;

        CHECK(config.right_margin() == func_sketch::plotter::default_margins);

        CHECK_NOTHROW(config.right_margin(10));
        CHECK(config.right_margin() == 10);

        CHECK_THROWS(config.right_margin(-1));
        CHECK(config.right_margin() == 10);

        CHECK_NOTHROW(config.right_margin(0));
        CHECK(config.right_margin() == 0);

        CHECK_NOTHROW(config.right_margin(1));
        CHECK(config.right_margin() == 1);
    }

    SECTION("set and get top margin") {
        PlotConfig config;

        CHECK(config.top_margin() == func_sketch::plotter::default_margins);

        CHECK_NOTHROW(config.top_margin(20));
        CHECK(config.top_margin() == 20);

        CHECK_THROWS(config.top_margin(-1));
        CHECK(config.top_margin() == 20);

        CHECK_NOTHROW(config.top_margin(0));
        CHECK(config.top_margin() == 0);

        CHECK_NOTHROW(config.top_margin(1));
        CHECK(config.top_margin() == 1);
    }

    SECTION("set and get bottom margin") {
        PlotConfig config;

        CHECK(config.bottom_margin() == func_sketch::plotter::default_margins);

        CHECK_NOTHROW(config.bottom_margin(25));
        CHECK(config.bottom_margin() == 25);

        CHECK_THROWS(config.bottom_margin(-1));
        CHECK(config.bottom_margin() == 25);

        CHECK_NOTHROW(config.bottom_margin(0));
        CHECK(config.bottom_margin() == 0);

        CHECK_NOTHROW(config.bottom_margin(1));
        CHECK(config.bottom_margin() == 1);
    }

    SECTION("set and get tick label font size") {
        PlotConfig config;

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

    SECTION("set and get axes line width") {
        PlotConfig config;

        CHECK(config.axes_line_width() ==
            func_sketch::plotter::default_axes_line_width);

        CHECK_NOTHROW(config.axes_line_width(5));
        CHECK(config.axes_line_width() == 5);

        CHECK_THROWS(config.axes_line_width(-1));
        CHECK(config.axes_line_width() == 5);

        CHECK_NOTHROW(config.axes_line_width(0));
        CHECK(config.axes_line_width() == 0);

        CHECK_NOTHROW(config.axes_line_width(1));
        CHECK(config.axes_line_width() == 1);
    }

    SECTION("set and get grid line width") {
        PlotConfig config;

        CHECK(config.grid_line_width() ==
            func_sketch::plotter::default_grid_line_width);

        CHECK_NOTHROW(config.grid_line_width(2));
        CHECK(config.grid_line_width() == 2);

        CHECK_THROWS(config.grid_line_width(-1));
        CHECK(config.grid_line_width() == 2);

        CHECK_NOTHROW(config.grid_line_width(0));
        CHECK(config.grid_line_width() == 0);

        CHECK_NOTHROW(config.grid_line_width(1));
        CHECK(config.grid_line_width() == 1);
    }

    SECTION("set and get curve line width") {
        PlotConfig config;

        CHECK(config.curve_line_width() ==
            func_sketch::plotter::default_curve_line_width);

        CHECK_NOTHROW(config.curve_line_width(4));
        CHECK(config.curve_line_width() == 4);

        CHECK_THROWS(config.curve_line_width(-1));
        CHECK(config.curve_line_width() == 4);

        CHECK_NOTHROW(config.curve_line_width(0));
        CHECK(config.curve_line_width() == 0);

        CHECK_NOTHROW(config.curve_line_width(1));
        CHECK(config.curve_line_width() == 1);
    }

    SECTION("set and get background color") {
        using func_sketch::plotter::RGBColor;

        PlotConfig config;

        CHECK(config.background_color() ==
            func_sketch::plotter::default_background_color);

        const RGBColor new_color{.r = 100, .g = 150, .b = 200};
        CHECK_NOTHROW(config.background_color(new_color));
        CHECK(config.background_color() == new_color);

        const RGBColor black{.r = 0, .g = 0, .b = 0};
        CHECK_NOTHROW(config.background_color(black));
        CHECK(config.background_color() == black);
    }

    SECTION("set and get axes color") {
        using func_sketch::plotter::RGBColor;

        PlotConfig config;

        CHECK(config.axes_color() == func_sketch::plotter::default_axes_color);

        const RGBColor new_color{.r = 50, .g = 100, .b = 150};
        CHECK_NOTHROW(config.axes_color(new_color));
        CHECK(config.axes_color() == new_color);

        const RGBColor white{.r = 255, .g = 255, .b = 255};
        CHECK_NOTHROW(config.axes_color(white));
        CHECK(config.axes_color() == white);
    }

    SECTION("set and get grid color") {
        using func_sketch::plotter::RGBColor;

        PlotConfig config;

        CHECK(config.grid_color() == func_sketch::plotter::default_grid_color);

        const RGBColor new_color{.r = 100, .g = 150, .b = 200};
        CHECK_NOTHROW(config.grid_color(new_color));
        CHECK(config.grid_color() == new_color);

        const RGBColor light_gray{.r = 220, .g = 220, .b = 220};
        CHECK_NOTHROW(config.grid_color(light_gray));
        CHECK(config.grid_color() == light_gray);
    }

    SECTION("set and get number of sample points") {
        PlotConfig config;

        CHECK(config.num_sample_points() ==
            func_sketch::plotter::default_num_sample_points);

        CHECK_NOTHROW(config.num_sample_points(200));
        CHECK(config.num_sample_points() == 200);

        CHECK_THROWS(config.num_sample_points(-1));
        CHECK(config.num_sample_points() == 200);

        CHECK_THROWS(config.num_sample_points(0));
        CHECK(config.num_sample_points() == 200);

        CHECK_THROWS(config.num_sample_points(1));
        CHECK(config.num_sample_points() == 200);

        CHECK_NOTHROW(config.num_sample_points(2));
        CHECK(config.num_sample_points() == 2);

        CHECK_NOTHROW(config.num_sample_points(3));
        CHECK(config.num_sample_points() == 3);
    }

    SECTION("set and get initial number of sample points") {
        PlotConfig config;

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
        PlotConfig config;

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
        PlotConfig config;

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
        PlotConfig config;

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
        PlotConfig config;

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
