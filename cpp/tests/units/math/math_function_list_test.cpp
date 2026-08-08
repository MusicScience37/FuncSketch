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
 * \brief Definition of MathFunctionList class.
 */
#include "func_sketch/math/math_function_list.h"

#include <catch2/catch_test_macros.hpp>

#include "func_sketch/math/functions/exp.h"

TEST_CASE("func_sketch::math::MathFunctionList") {
    using func_sketch::math::exp_function;
    using func_sketch::math::MathFunction;
    using func_sketch::math::MathFunctionList;

    SECTION("append and get a function") {
        MathFunctionList list;
        list.emplace(exp_function());

        const auto function = list.get("exp");
        REQUIRE(function.has_value());

        CHECK(function->name() == "exp");
    }

    SECTION("get a function that does not exist") {
        MathFunctionList list;

        const auto function = list.get("exp");
        CHECK(!function.has_value());
    }
}
