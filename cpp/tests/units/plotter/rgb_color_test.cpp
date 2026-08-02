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
 * \brief Test of RGBColor struct.
 */
#include "func_sketch/plotter/rgb_color.h"

#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

TEST_CASE("func_sketch::plotter::RGBColor") {
    using func_sketch::plotter::RGBColor;

    SECTION("format") {
        const RGBColor color{.r = static_cast<std::uint8_t>(123),
            .g = static_cast<std::uint8_t>(45),
            .b = static_cast<std::uint8_t>(67)};

        CHECK(fmt::format("{}", color) == "RGBColor(123, 45, 67)");
    }
}
