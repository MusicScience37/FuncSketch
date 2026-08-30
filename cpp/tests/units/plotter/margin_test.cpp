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
 * \brief Test of Margin class.
 */
#include "func_sketch/plotter/margin.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("func_sketch::plotter::Margin") {
    using func_sketch::plotter::Margin;

    SECTION("construct with values") {
        const Margin margin{7, 10, 20, 25};

        CHECK(margin.left() == 7);
        CHECK(margin.right() == 10);
        CHECK(margin.top() == 20);
        CHECK(margin.bottom() == 25);
    }

    SECTION("construct with an invalid value") {
        CHECK_THROWS(Margin(-1, 10, 20, 25));
    }

    SECTION("set and get left margin") {
        Margin margin;

        CHECK(margin.left() == func_sketch::plotter::default_margin);

        CHECK_NOTHROW(margin.left(7));
        CHECK(margin.left() == 7);

        CHECK_THROWS(margin.left(-1));
        CHECK(margin.left() == 7);

        CHECK_NOTHROW(margin.left(0));
        CHECK(margin.left() == 0);

        CHECK_NOTHROW(margin.left(1));
        CHECK(margin.left() == 1);
    }

    SECTION("set and get right margin") {
        Margin margin;

        CHECK(margin.right() == func_sketch::plotter::default_margin);

        CHECK_NOTHROW(margin.right(10));
        CHECK(margin.right() == 10);

        CHECK_THROWS(margin.right(-1));
        CHECK(margin.right() == 10);

        CHECK_NOTHROW(margin.right(0));
        CHECK(margin.right() == 0);

        CHECK_NOTHROW(margin.right(1));
        CHECK(margin.right() == 1);
    }

    SECTION("set and get top margin") {
        Margin margin;

        CHECK(margin.top() == func_sketch::plotter::default_margin);

        CHECK_NOTHROW(margin.top(20));
        CHECK(margin.top() == 20);

        CHECK_THROWS(margin.top(-1));
        CHECK(margin.top() == 20);

        CHECK_NOTHROW(margin.top(0));
        CHECK(margin.top() == 0);

        CHECK_NOTHROW(margin.top(1));
        CHECK(margin.top() == 1);
    }

    SECTION("set and get bottom margin") {
        Margin margin;

        CHECK(margin.bottom() == func_sketch::plotter::default_margin);

        CHECK_NOTHROW(margin.bottom(25));
        CHECK(margin.bottom() == 25);

        CHECK_THROWS(margin.bottom(-1));
        CHECK(margin.bottom() == 25);

        CHECK_NOTHROW(margin.bottom(0));
        CHECK(margin.bottom() == 0);

        CHECK_NOTHROW(margin.bottom(1));
        CHECK(margin.bottom() == 1);
    }
}
