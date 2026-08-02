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

#include <catch2/catch_test_macros.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "func_sketch/plotter/image.h"
#include "func_sketch/plotter/rgb_color.h"

TEST_CASE("func_sketch::plotter::Plotter") {
    using func_sketch::plotter::Image;
    using func_sketch::plotter::PlotConfig;
    using func_sketch::plotter::PlotRange;
    using func_sketch::plotter::Plotter;
    using func_sketch::plotter::RGBColor;

    SECTION("write_background") {
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

    SECTION("write_background_at_bottom_right") {
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

    SECTION("write_background_at_top_left") {
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
}
