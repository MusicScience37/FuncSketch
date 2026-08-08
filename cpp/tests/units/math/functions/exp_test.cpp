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
 * \brief Test of exponential functions.
 */
#include "func_sketch/math/functions/exp.h"

#include <cmath>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/math/math_function_type.h"

TEST_CASE("func_sketch::math::exp_function") {
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::exp_function;
    using func_sketch::math::MathFunctionType;

    SECTION("operate on a real number") {
        const auto args = std::vector<Number>{1.0};
        Number result = 0.0;

        const auto function_object = exp_function();
        function_object(args, result);

        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(std::exp(1.0)));
    }

    SECTION("operate on an integer") {
        const auto args = std::vector<Number>{2};
        Number result = 0.0;

        const auto function_object = exp_function();
        function_object(args, result);

        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(std::exp(2.0)));
    }

    SECTION("check the number of arguments") {
        const auto function_object = exp_function();
        Number result = 0.0;

        CHECK_THROWS(function_object(std::vector<Number>{}, result));
        CHECK_THROWS(function_object(std::vector<Number>{1.0, 2.0}, result));
    }
}
