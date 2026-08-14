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
 * \brief Test of functions to create Bessel functions and related
 * functions.
 */
#include "func_sketch/math/functions/bessel.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"

TEST_CASE("func_sketch::math::bessel_j_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::bessel_j_function;

    // Gamma function for complex arguments will be assigned in the binding
    // code, so empty function is used here. Tests for complex arguments will be
    // done in Python.
    const std::function<Complex(Real, Complex)> complex_bessel_j;
    const auto function_object = bessel_j_function(complex_bessel_j);

    SECTION("operate on an integer order and a real argument") {
        constexpr Integer order = 2;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Real expected = 0.23208767214421475;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on a real order and a real argument") {
        constexpr Real order = 2.5;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Real expected = 0.12444635979838772;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }
}
