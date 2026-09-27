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
 * \brief Test of orthogonal polynomials.
 */
#include "func_sketch/math/functions/orthogonal_polynomials.h"

#include <cmath>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"

TEST_CASE("func_sketch::math::hermite_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::hermite_function;

    const auto function_object = hermite_function();

    SECTION("operate on an integer order and a real argument") {
        constexpr Integer order = 3;
        constexpr Real argument = 0.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Real expected = -5.0;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on an integer order and an integer argument") {
        constexpr Integer order = 4;
        constexpr Integer argument = 2;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Real expected = 76.0;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("try to operate on a negative order") {
        constexpr Integer order = -1;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        CHECK(std::isnan(std::get<Real>(result)));
    }

    SECTION("try to operate on a real number order") {
        constexpr Real order = 2.5;
        constexpr Real argument = 1.5;

        Number result;
        CHECK_THROWS(
            function_object(std::vector<Number>{order, argument}, result));
    }

    SECTION("check the number of arguments") {
        Number result;
        const Number arg = 1;
        CHECK_THROWS(function_object(std::vector<Number>{}, result));
        CHECK_THROWS(function_object(std::vector<Number>{arg}, result));
        CHECK_THROWS(
            function_object(std::vector<Number>{arg, arg, arg}, result));
    }
}
