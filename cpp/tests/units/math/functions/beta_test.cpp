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
 * \brief Test of beta functions.
 */
#include "func_sketch/math/functions/beta.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"

TEST_CASE("func_sketch::math::beta_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::beta_function;

    const auto function_object = beta_function();

    SECTION("operate on integers") {
        constexpr Integer x = 2;
        constexpr Integer y = 3;

        Number result;
        function_object(std::vector<Number>{x, y}, result);

        constexpr Real expected = 1.0 / 12.0;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers") {
        constexpr Real x = 1.5;
        constexpr Real y = 2.5;

        Number result;
        function_object(std::vector<Number>{x, y}, result);

        constexpr Real expected = 0.19634954084936204;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
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

TEST_CASE("func_sketch::math::lbeta_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::lbeta_function;

    // Actual function will be assigned in the binding code, so a dummy function
    // is used here. Tests of values will be done in Python.
    const auto dummy_real_lbeta =
        lbeta_function([](Real x, Real y) { return x - (2.0 * y); });

    SECTION("check the number of arguments") {
        Number result;
        const Number arg = 1;
        CHECK_THROWS(dummy_real_lbeta(std::vector<Number>{}, result));
        CHECK_THROWS(dummy_real_lbeta(std::vector<Number>{arg}, result));
        CHECK_THROWS(
            dummy_real_lbeta(std::vector<Number>{arg, arg, arg}, result));
    }
}

TEST_CASE("func_sketch::math::ibeta_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::ibeta_function;

    const auto function_object = ibeta_function();

    SECTION("operate on integers") {
        constexpr Integer param_a = 2;
        constexpr Integer param_b = 3;
        constexpr Integer x = 1;

        Number result;
        function_object(std::vector<Number>{param_a, param_b, x}, result);

        constexpr Real expected = 1.0;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers") {
        constexpr Real param_a = 1.5;
        constexpr Real param_b = 2.5;
        constexpr Real x = 0.3;

        Number result;
        function_object(std::vector<Number>{param_a, param_b, x}, result);

        constexpr Real expected = 0.41568785229802524;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("check the number of arguments") {
        Number result;
        const Number arg = 1;
        CHECK_THROWS(function_object(std::vector<Number>{arg, arg}, result));
        CHECK_THROWS(
            function_object(std::vector<Number>{arg, arg, arg, arg}, result));
    }
}

TEST_CASE("func_sketch::math::ibetac_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::ibetac_function;

    const auto function_object = ibetac_function();

    SECTION("operate on integers") {
        constexpr Integer param_a = 2;
        constexpr Integer param_b = 3;
        constexpr Integer x = 0;

        Number result;
        function_object(std::vector<Number>{param_a, param_b, x}, result);

        constexpr Real expected = 1.0;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers") {
        constexpr Real param_a = 1.5;
        constexpr Real param_b = 2.5;
        constexpr Real x = 0.3;

        Number result;
        function_object(std::vector<Number>{param_a, param_b, x}, result);

        constexpr Real expected = 0.5843121477019747;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("check the number of arguments") {
        Number result;
        const Number arg = 1;
        CHECK_THROWS(function_object(std::vector<Number>{arg, arg}, result));
        CHECK_THROWS(
            function_object(std::vector<Number>{arg, arg, arg, arg}, result));
    }
}
