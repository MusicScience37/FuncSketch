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
 * \brief Test of PointConverter class.
 */
#include "func_sketch/plotter/point_converter.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/plotter/margin.h"
#include "func_sketch/plotter/plot_range.h"
#include "func_sketch/plotter/point.h"

TEST_CASE("func_sketch::plotter::PointConverter") {
    using func_sketch::plotter::Margin;
    using func_sketch::plotter::PlotRange;
    using func_sketch::plotter::Point;
    using func_sketch::plotter::PointConverter;

    constexpr double tolerance = 1e-10;

    const Margin margin{5, 15, 8, 12};
    const PlotRange range({-2.0, 2.0}, {-1.0, 3.0});
    constexpr int image_height = 108;
    constexpr int image_width = 120;

    SECTION("construct with valid values") {
        CHECK_NOTHROW(PointConverter(margin, range, image_height, image_width));
    }

    SECTION("construct with an invalid image size") {
        CHECK_THROWS(PointConverter(margin, range, 0, image_width));
        CHECK_THROWS(PointConverter(margin, range, image_height, 0));
        CHECK_THROWS(PointConverter(margin, range, -1, image_width));
        CHECK_THROWS(PointConverter(margin, range, image_height, -1));
    }

    SECTION("construct with a margin larger than the image size") {
        const Margin large_margin{
            image_width, image_width, image_height, image_height};
        CHECK_THROWS(
            PointConverter(large_margin, range, image_height, image_width));
    }

    SECTION("set the margin of the plot region") {
        PointConverter converter(margin, range, image_height, image_width);

        const Margin new_margin{0, 0, 0, 0};
        CHECK_NOTHROW(converter.plot_region_margin(new_margin));
        CHECK(converter.convert_plot_to_image(Point{.x = -2.0, .y = -1.0}) ==
            cv::Point(0, image_height));

        const Margin too_large_margin{
            image_width, image_width, image_height, image_height};
        CHECK_THROWS(converter.plot_region_margin(too_large_margin));
    }

    SECTION("set the range of plots") {
        PointConverter converter(margin, range, image_height, image_width);

        const PlotRange new_range({0.0, 1.0}, {0.0, 1.0});
        CHECK_NOTHROW(converter.range(new_range));
        CHECK(converter.convert_plot_to_image(Point{.x = 0.0, .y = 0.0}) ==
            cv::Point(margin.left(), image_height - margin.bottom()));
    }

    SECTION("set the size of the image") {
        PointConverter converter(margin, range, image_height, image_width);

        CHECK_NOTHROW(converter.image_size(image_height * 2, image_width * 2));
        CHECK_THROWS(converter.image_size(0, image_width));
        CHECK_THROWS(converter.image_size(image_height, 0));
        CHECK_THROWS(
            converter.image_size(margin.top() + margin.bottom(), image_width));
    }

    SECTION("convert a point from plot coordinates to image coordinates") {
        PointConverter converter(margin, range, image_height, image_width);

        CHECK(converter.convert_plot_to_image(Point{.x = -2.0, .y = -1.0}) ==
            cv::Point(5, 96));

        CHECK(converter.convert_plot_to_image(Point{.x = 2.0, .y = 3.0}) ==
            cv::Point(105, 8));

        CHECK(converter.convert_plot_to_image(Point{.x = 0.0, .y = 1.0}) ==
            cv::Point(55, 52));
    }

    SECTION(
        "convert a point from plot coordinates to image coordinates "
        "with shift") {
        PointConverter converter(margin, range, image_height, image_width);

        CHECK(converter.convert_plot_to_image(Point{.x = -2.0, .y = -1.0}, 0) ==
            converter.convert_plot_to_image(Point{.x = -2.0, .y = -1.0}));
        CHECK(converter.convert_plot_to_image(Point{.x = 2.0, .y = 3.0}, 0) ==
            converter.convert_plot_to_image(Point{.x = 2.0, .y = 3.0}));

        constexpr int shift = 10;
        CHECK(converter.convert_plot_to_image(Point{.x = -2.0, .y = -1.0},
                  shift) == cv::Point(5120, 98304));
        CHECK(converter.convert_plot_to_image(
                  Point{.x = 2.0, .y = 3.0}, shift) == cv::Point(107520, 8192));
        CHECK(converter.convert_plot_to_image(
                  Point{.x = 0.0, .y = 1.0}, shift) == cv::Point(56320, 53248));

        const Point sub_pixel_point{.x = -1.5, .y = 1.0};
        CHECK(converter.convert_plot_to_image(sub_pixel_point, 1) ==
            cv::Point(35, 104));
        CHECK(converter.convert_plot_to_image(sub_pixel_point) ==
            cv::Point(17, 52));
    }

    SECTION("convert a point from image coordinates to plot coordinates") {
        PointConverter converter(margin, range, image_height, image_width);

        const Point lower_left =
            converter.convert_image_to_plot(cv::Point(5, 96));
        CHECK_THAT(lower_left.x, Catch::Matchers::WithinAbs(-2.0, tolerance));
        CHECK_THAT(lower_left.y, Catch::Matchers::WithinAbs(-1.0, tolerance));

        const Point upper_right =
            converter.convert_image_to_plot(cv::Point(105, 8));
        CHECK_THAT(upper_right.x, Catch::Matchers::WithinAbs(2.0, tolerance));
        CHECK_THAT(upper_right.y, Catch::Matchers::WithinAbs(3.0, tolerance));

        const Point center = converter.convert_image_to_plot(cv::Point(55, 52));
        CHECK_THAT(center.x, Catch::Matchers::WithinAbs(0.0, tolerance));
        CHECK_THAT(center.y, Catch::Matchers::WithinAbs(1.0, tolerance));
    }

    SECTION("check that two conversions are consistent") {
        PointConverter converter(margin, range, image_height, image_width);

        for (const Point& original :
            {Point{.x = -2.0, .y = -1.0}, Point{.x = 2.0, .y = 3.0},
                Point{.x = 0.0, .y = 1.0}, Point{.x = -1.0, .y = 2.0}}) {
            const cv::Point image_point =
                converter.convert_plot_to_image(original);
            const Point round_tripped =
                converter.convert_image_to_plot(image_point);

            CHECK_THAT(round_tripped.x,
                Catch::Matchers::WithinAbs(original.x, tolerance));
            CHECK_THAT(round_tripped.y,
                Catch::Matchers::WithinAbs(original.y, tolerance));
        }
    }
}
