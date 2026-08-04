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
 * \brief Test of ExpFunction class.
 */
#include "func_sketch/math/functions/exp.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/math/math_function_type.h"

TEST_CASE("func_sketch::math::ExpFunction") {
    using func_sketch::Scalar;
    using func_sketch::math::ExpFunction;
    using func_sketch::math::MathFunctionType;

    SECTION("check concept") { STATIC_REQUIRE(MathFunctionType<ExpFunction>); }

    SECTION("operate on a scalar") {
        const auto args = std::vector<Scalar>{1.0};
        Scalar result = 0.0;

        ExpFunction function_object;
        function_object(args, result);

        CHECK_THAT(result, Catch::Matchers::WithinRel(std::exp(1.0)));
    }

    SECTION("check the number of arguments") {
        ExpFunction function_object;
        Scalar result = 0.0;

        CHECK_THROWS(function_object(std::vector<Scalar>{}, result));
        CHECK_THROWS(function_object(std::vector<Scalar>{1.0, 2.0}, result));
    }
}
