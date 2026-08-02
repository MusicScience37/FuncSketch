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
 * \brief Test of Plotter class.
 */
#include "func_sketch/plotter/plotter.h"

#include <limits>

#include <catch2/catch_test_macros.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "func_sketch/plotter/image.h"
#include "func_sketch/plotter/point.h"
#include "func_sketch/plotter/rgb_color.h"

TEST_CASE("func_sketch::plotter::Plotter") {
    using func_sketch::plotter::Image;
    using func_sketch::plotter::PlotConfig;
    using func_sketch::plotter::PlotRange;
    using func_sketch::plotter::Plotter;
    using func_sketch::plotter::Point;
    using func_sketch::plotter::RGBColor;

    SECTION("write background") {
        const auto range = PlotRange({-1.0, 1.0}, {-1.5, 1.5});
        const auto config = PlotConfig().background_color(
            RGBColor{.r = 0xFD, .g = 0xF4, .b = 0xEF});
        Plotter plotter(range, config);

        constexpr int width = 800;
        constexpr int height = 600;
        Image image(height, width, CV_8UC3);
        plotter.write_background(image);

        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        CHECK(cv::imwrite("plotter_test_write_background.png", image));

        // Check colors in the actual images.
    }

    SECTION("write background at bottom right") {
        const auto range = PlotRange({-1.0, -0.2}, {0.5, 1.5});
        const auto config = PlotConfig().background_color(
            RGBColor{.r = 0xFD, .g = 0xF4, .b = 0xEF});
        Plotter plotter(range, config);

        constexpr int width = 800;
        constexpr int height = 600;
        Image image(height, width, CV_8UC3);
        plotter.write_background(image);

        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        CHECK(cv::imwrite(
            "plotter_test_write_background_at_bottom_right.png", image));

        // Check colors in the actual images.
    }

    SECTION("write background at top left") {
        const auto range = PlotRange({0.3, 1.2}, {-2.0, -0.5});
        const auto config = PlotConfig().background_color(
            RGBColor{.r = 0xFD, .g = 0xF4, .b = 0xEF});
        Plotter plotter(range, config);

        constexpr int width = 800;
        constexpr int height = 600;
        Image image(height, width, CV_8UC3);
        plotter.write_background(image);

        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        CHECK(cv::imwrite(
            "plotter_test_write_background_at_top_left.png", image));

        // Check colors in the actual images.
    }

    SECTION("write a curve") {
        const auto range = PlotRange({-1.0, 1.0}, {-1.5, 1.5});
        const auto config = PlotConfig();
        Plotter plotter(range, config);

        constexpr int width = 800;
        constexpr int height = 600;
        Image image(height, width, CV_8UC3);
        plotter.write_background(image);

        const auto samples = std::vector{Point{.x = -1.0, .y = -1.0},
            Point{.x = 0.5, .y = 0.5}, Point{.x = 1.0, .y = -1.0}};
        const auto color = RGBColor{.r = 0xCA, .g = 0x76, .b = 0x39};
        plotter.write_curve(samples, color, image);

        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        CHECK(cv::imwrite("plotter_test_write_curve.png", image));
    }

    SECTION("write a curve with points outside the range") {
        const auto range = PlotRange({-1.0, 1.0}, {-1.5, 1.5});
        const auto config = PlotConfig();
        Plotter plotter(range, config);

        constexpr int width = 800;
        constexpr int height = 600;
        Image image(height, width, CV_8UC3);
        plotter.write_background(image);

        const auto samples =
            std::vector{Point{.x = -2.0, .y = -1.0}, Point{.x = 0.5, .y = 0.5},
                Point{.x = 1.0, .y = -std::numeric_limits<double>::infinity()}};
        const auto color = RGBColor{.r = 0xCA, .g = 0x76, .b = 0x39};
        plotter.write_curve(samples, color, image);

        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        CHECK(cv::imwrite(
            "plotter_test_write_curve_with_points_outside_the_range.png",
            image));
    }

    SECTION("write a curve with a line outside the range") {
        const auto range = PlotRange({-1.0, 1.0}, {-1.5, 1.5});
        const auto config = PlotConfig();
        Plotter plotter(range, config);

        constexpr int width = 800;
        constexpr int height = 600;
        Image image(height, width, CV_8UC3);
        plotter.write_background(image);

        const auto samples = std::vector{Point{.x = -1.0, .y = -1.0},
            Point{.x = -0.5, .y = 10.0}, Point{.x = 0.0, .y = -10.0},
            Point{.x = 0.5, .y = -1.0}, Point{.x = 1.0, .y = -1.0}};
        const auto color = RGBColor{.r = 0xCA, .g = 0x76, .b = 0x39};
        plotter.write_curve(samples, color, image);

        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        CHECK(cv::imwrite(
            "plotter_test_write_curve_with_a_line_outside_the_range.png",
            image));
    }

    SECTION("write a curve with NaN") {
        const auto range = PlotRange({-1.0, 1.0}, {-1.5, 1.5});
        const auto config = PlotConfig();
        Plotter plotter(range, config);

        constexpr int width = 800;
        constexpr int height = 600;
        Image image(height, width, CV_8UC3);
        plotter.write_background(image);

        const auto samples = std::vector{Point{.x = -1.0, .y = -1.0},
            Point{.x = -0.5, .y = 10.0},
            Point{.x = 0.0, .y = std::numeric_limits<double>::quiet_NaN()},
            Point{.x = 0.5, .y = -1.0}, Point{.x = 1.0, .y = -1.0}};
        const auto color = RGBColor{.r = 0xCA, .g = 0x76, .b = 0x39};
        plotter.write_curve(samples, color, image);

        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        CHECK(cv::imwrite("plotter_test_write_curve_with_NaN.png", image));
    }
}
