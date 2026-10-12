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
 * \brief Test of validate_bounds function.
 */
#include "func_sketch/utilities/validate_bounds.h"

#include <cmath>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("func_sketch::utilities::validate_bounds") {
    using func_sketch::utilities::validate_bounds;

    SECTION("accept valid ranges") {
        CHECK_NOTHROW(validate_bounds({0.0, 1.0}, "test"));
        CHECK_NOTHROW(validate_bounds({-8e+307, 8e+307}, "test"));
        CHECK_NOTHROW(validate_bounds({0.0, 1.01e-300}, "test"));
        CHECK_NOTHROW(validate_bounds({1e+15, 1e+15 + 1.01e+3}, "test"));
        CHECK_NOTHROW(validate_bounds({-1e+15 - 1.01e+3, -1e+15}, "test"));
    }

    SECTION("reject invalid ranges") {
        CHECK_THROWS(validate_bounds({NAN, 1.0}, "test"));
        CHECK_THROWS(validate_bounds({0.0, NAN}, "test"));
        CHECK_THROWS(validate_bounds({-INFINITY, 1.0}, "test"));
        CHECK_THROWS(validate_bounds({0.0, INFINITY}, "test"));
        CHECK_THROWS(validate_bounds({0.0, 0.0}, "test"));
        CHECK_THROWS(validate_bounds({0.0, -1.0}, "test"));
        CHECK_THROWS(validate_bounds({-1e+308, 1e+308}, "test"));
        CHECK_THROWS(validate_bounds({0.0, 0.99e-300}, "test"));
        CHECK_THROWS(validate_bounds({1e+15, 1e+15 + 0.99e+3}, "test"));
        CHECK_THROWS(validate_bounds({-1e+15 - 0.99e+3, -1e+15}, "test"));
    }
}
