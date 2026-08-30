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

    SECTION(
        "access the configuration of the minimum margins of the plot "
        "region") {
        PlotConfig config;

        CHECK(config.min_plot_margin().left() ==
            func_sketch::plotter::default_min_plot_left_margin);
        CHECK(config.min_plot_margin().right() ==
            func_sketch::plotter::default_min_plot_right_margin);
        CHECK(config.min_plot_margin().top() ==
            func_sketch::plotter::default_min_plot_top_margin);
        CHECK(config.min_plot_margin().bottom() ==
            func_sketch::plotter::default_min_plot_bottom_margin);

        config.min_plot_margin().left(7).right(10).top(20).bottom(25);

        CHECK(config.min_plot_margin().left() == 7);
        CHECK(config.min_plot_margin().right() == 10);
        CHECK(config.min_plot_margin().top() == 20);
        CHECK(config.min_plot_margin().bottom() == 25);

        const PlotConfig& const_config = config;
        CHECK(const_config.min_plot_margin().left() == 7);
        CHECK(const_config.min_plot_margin().right() == 10);
        CHECK(const_config.min_plot_margin().top() == 20);
        CHECK(const_config.min_plot_margin().bottom() == 25);
    }

    SECTION("access the configuration of the base margin") {
        PlotConfig config;

        CHECK(config.base_margin().left() ==
            func_sketch::plotter::default_base_margin);
        CHECK(config.base_margin().right() ==
            func_sketch::plotter::default_base_margin);
        CHECK(config.base_margin().top() ==
            func_sketch::plotter::default_base_margin);
        CHECK(config.base_margin().bottom() ==
            func_sketch::plotter::default_base_margin);

        config.base_margin().left(7).right(10).top(20).bottom(25);

        CHECK(config.base_margin().left() == 7);
        CHECK(config.base_margin().right() == 10);
        CHECK(config.base_margin().top() == 20);
        CHECK(config.base_margin().bottom() == 25);

        const PlotConfig& const_config = config;
        CHECK(const_config.base_margin().left() == 7);
        CHECK(const_config.base_margin().right() == 10);
        CHECK(const_config.base_margin().top() == 20);
        CHECK(const_config.base_margin().bottom() == 25);
    }

    SECTION("access the configuration of axes") {
        using func_sketch::plotter::RGBColor;

        PlotConfig config;

        CHECK(config.axes().tick_label_font_size() ==
            func_sketch::plotter::default_tick_label_font_size);
        CHECK(config.axes().tick_label_margin() ==
            func_sketch::plotter::default_tick_label_margin);
        CHECK(config.axes().line_width() ==
            func_sketch::plotter::default_axes_line_width);
        CHECK(
            config.axes().color() == func_sketch::plotter::default_axes_color);
        CHECK(config.axes().num_pixels_per_tick_in_x_axis() ==
            func_sketch::plotter::default_num_pixels_per_tick_in_x_axis);
        CHECK(config.axes().num_pixels_per_tick_in_y_axis() ==
            func_sketch::plotter::default_num_pixels_per_tick_in_y_axis);

        const RGBColor new_color{.r = 50, .g = 100, .b = 150};
        config.axes()
            .tick_label_font_size(14)
            .tick_label_margin(7)
            .line_width(5)
            .color(new_color)
            .num_pixels_per_tick_in_x_axis(150)
            .num_pixels_per_tick_in_y_axis(100);

        CHECK(config.axes().tick_label_font_size() == 14);
        CHECK(config.axes().tick_label_margin() == 7);
        CHECK(config.axes().line_width() == 5);
        CHECK(config.axes().color() == new_color);
        CHECK(config.axes().num_pixels_per_tick_in_x_axis() == 150);
        CHECK(config.axes().num_pixels_per_tick_in_y_axis() == 100);

        const PlotConfig& const_config = config;
        CHECK(const_config.axes().tick_label_font_size() == 14);
        CHECK(const_config.axes().tick_label_margin() == 7);
        CHECK(const_config.axes().line_width() == 5);
        CHECK(const_config.axes().color() == new_color);
        CHECK(const_config.axes().num_pixels_per_tick_in_x_axis() == 150);
        CHECK(const_config.axes().num_pixels_per_tick_in_y_axis() == 100);
    }

    SECTION("access the configuration of the grid") {
        using func_sketch::plotter::RGBColor;

        PlotConfig config;

        CHECK(config.grid().line_width() ==
            func_sketch::plotter::default_grid_line_width);
        CHECK(config.grid().zero_line_width() ==
            func_sketch::plotter::default_zero_line_width);
        CHECK(
            config.grid().color() == func_sketch::plotter::default_grid_color);

        const RGBColor new_color{.r = 100, .g = 150, .b = 200};
        config.grid().line_width(2).zero_line_width(3).color(new_color);

        CHECK(config.grid().line_width() == 2);
        CHECK(config.grid().zero_line_width() == 3);
        CHECK(config.grid().color() == new_color);

        const PlotConfig& const_config = config;
        CHECK(const_config.grid().line_width() == 2);
        CHECK(const_config.grid().zero_line_width() == 3);
        CHECK(const_config.grid().color() == new_color);
    }

    SECTION("set and get plot title") {
        PlotConfig config;

        CHECK(config.plot_title() == func_sketch::plotter::default_plot_title);

        CHECK_NOTHROW(config.plot_title("My Plot"));
        CHECK(config.plot_title() == "My Plot");

        CHECK_NOTHROW(config.plot_title(""));
        CHECK(config.plot_title().empty());
    }

    SECTION("set and get font size of the title of the plot") {
        PlotConfig config;

        CHECK(config.plot_title_font_size() ==
            func_sketch::plotter::default_plot_title_font_size);

        CHECK_NOTHROW(config.plot_title_font_size(14));
        CHECK(config.plot_title_font_size() == 14);

        CHECK_THROWS(config.plot_title_font_size(-1));
        CHECK(config.plot_title_font_size() == 14);

        CHECK_NOTHROW(config.plot_title_font_size(0));
        CHECK(config.plot_title_font_size() == 0);

        CHECK_NOTHROW(config.plot_title_font_size(1));
        CHECK(config.plot_title_font_size() == 1);
    }

    SECTION("set and get color of the title of the plot") {
        using func_sketch::plotter::RGBColor;

        PlotConfig config;

        CHECK(config.plot_title_color() ==
            func_sketch::plotter::default_plot_title_color);

        const RGBColor new_color{.r = 100, .g = 150, .b = 200};
        CHECK_NOTHROW(config.plot_title_color(new_color));
        CHECK(config.plot_title_color() == new_color);

        const RGBColor black{.r = 0, .g = 0, .b = 0};
        CHECK_NOTHROW(config.plot_title_color(black));
        CHECK(config.plot_title_color() == black);
    }

    SECTION("set and get margin for the title of the plot") {
        PlotConfig config;

        CHECK(config.plot_title_margin() ==
            func_sketch::plotter::default_plot_title_margin);

        CHECK_NOTHROW(config.plot_title_margin(14));
        CHECK(config.plot_title_margin() == 14);

        CHECK_THROWS(config.plot_title_margin(-1));
        CHECK(config.plot_title_margin() == 14);

        CHECK_NOTHROW(config.plot_title_margin(0));
        CHECK(config.plot_title_margin() == 0);

        CHECK_NOTHROW(config.plot_title_margin(1));
        CHECK(config.plot_title_margin() == 1);
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

    SECTION("access the configuration of sampling") {
        PlotConfig config;

        CHECK(config.sampling().initial_num_sample_points() ==
            func_sketch::plotter::default_initial_num_sample_points);
        CHECK(config.sampling().max_num_sample_points() ==
            func_sketch::plotter::default_max_num_sample_points);
        CHECK(config.sampling().max_coordinate_change_rate() ==
            func_sketch::plotter::default_max_coordinate_change_rate);
        CHECK(config.sampling().slope_change_threshold() ==
            func_sketch::plotter::default_slope_change_threshold);
        CHECK(config.sampling().min_param_change_rate() ==
            func_sketch::plotter::default_min_param_change_rate);

        config.sampling()
            .initial_num_sample_points(200)
            .max_num_sample_points(3000)
            .max_coordinate_change_rate(0.05)
            .slope_change_threshold(0.5)
            .min_param_change_rate(0.01);

        CHECK(config.sampling().initial_num_sample_points() == 200);
        CHECK(config.sampling().max_num_sample_points() == 3000);
        CHECK(config.sampling().max_coordinate_change_rate() == 0.05);
        CHECK(config.sampling().slope_change_threshold() == 0.5);
        CHECK(config.sampling().min_param_change_rate() == 0.01);

        const PlotConfig& const_config = config;
        CHECK(const_config.sampling().initial_num_sample_points() == 200);
        CHECK(const_config.sampling().max_num_sample_points() == 3000);
        CHECK(const_config.sampling().max_coordinate_change_rate() == 0.05);
        CHECK(const_config.sampling().slope_change_threshold() == 0.5);
        CHECK(const_config.sampling().min_param_change_rate() == 0.01);
    }
}
