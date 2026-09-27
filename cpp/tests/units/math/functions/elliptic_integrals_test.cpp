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
 * \brief Test of elliptic integrals.
 */
#include "func_sketch/math/functions/elliptic_integrals.h"

#include <cmath>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"

TEST_CASE("func_sketch::math::elliptic_f_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::elliptic_f_function;

    const auto function_object = elliptic_f_function();

    SECTION("operate on integers") {
        constexpr Integer phi = 1;
        constexpr Integer modulus = 0;

        Number result;
        function_object(std::vector<Number>{phi, modulus}, result);

        constexpr Real expected = 1.0;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers") {
        constexpr Real phi = 0.8;
        constexpr Real modulus = 0.5;

        Number result;
        function_object(std::vector<Number>{phi, modulus}, result);

        constexpr Real expected = 0.8199924351269172;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with phi larger than pi / 2") {
        constexpr Real phi = 2.5;
        constexpr Real modulus = 0.8;

        Number result;
        function_object(std::vector<Number>{phi, modulus}, result);

        constexpr Real expected = 3.3198755177924326;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("try to operate on arguments out of the domain") {
        constexpr Real phi = 1.0;
        constexpr Real modulus = 2.0;

        Number result;
        function_object(std::vector<Number>{phi, modulus}, result);

        CHECK(std::isnan(std::get<Real>(result)));
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

TEST_CASE("func_sketch::math::comp_elliptic_k_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::comp_elliptic_k_function;

    const auto function_object = comp_elliptic_k_function();

    SECTION("operate on an integer") {
        constexpr Integer modulus = 0;

        Number result;
        function_object(std::vector<Number>{modulus}, result);

        constexpr Real expected = 1.5707963267948966;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on a real number") {
        constexpr Real modulus = 0.5;

        Number result;
        function_object(std::vector<Number>{modulus}, result);

        constexpr Real expected = 1.685750354812596;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on a pole") {
        constexpr Real modulus = 1.0;

        Number result;
        function_object(std::vector<Number>{modulus}, result);

        CHECK(std::isinf(std::get<Real>(result)));
    }

    SECTION("try to operate on an argument out of the domain") {
        constexpr Real modulus = 2.0;

        Number result;
        function_object(std::vector<Number>{modulus}, result);

        CHECK(std::isnan(std::get<Real>(result)));
    }

    SECTION("check the number of arguments") {
        Number result;
        const Number arg = 1;
        CHECK_THROWS(function_object(std::vector<Number>{}, result));
        CHECK_THROWS(function_object(std::vector<Number>{arg, arg}, result));
    }
}

TEST_CASE("func_sketch::math::elliptic_e_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::elliptic_e_function;

    const auto function_object = elliptic_e_function();

    SECTION("operate on integers") {
        constexpr Integer phi = 1;
        constexpr Integer modulus = 0;

        Number result;
        function_object(std::vector<Number>{phi, modulus}, result);

        constexpr Real expected = 1.0;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers") {
        constexpr Real phi = 0.8;
        constexpr Real modulus = 0.5;

        Number result;
        function_object(std::vector<Number>{phi, modulus}, result);

        constexpr Real expected = 0.780840498315241;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with phi larger than pi / 2") {
        constexpr Real phi = 2.5;
        constexpr Real modulus = 0.8;

        Number result;
        function_object(std::vector<Number>{phi, modulus}, result);

        constexpr Real expected = 1.9380487553436576;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with modulus 1") {
        constexpr Real phi = 2.0;
        constexpr Real modulus = 1.0;

        Number result;
        function_object(std::vector<Number>{phi, modulus}, result);

        constexpr Real expected = 1.0907025731743185;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("try to operate on arguments out of the domain") {
        constexpr Real phi = 1.0;
        constexpr Real modulus = 2.0;

        Number result;
        function_object(std::vector<Number>{phi, modulus}, result);

        CHECK(std::isnan(std::get<Real>(result)));
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

TEST_CASE("func_sketch::math::comp_elliptic_e_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::comp_elliptic_e_function;

    const auto function_object = comp_elliptic_e_function();

    SECTION("operate on an integer") {
        constexpr Integer modulus = 0;

        Number result;
        function_object(std::vector<Number>{modulus}, result);

        constexpr Real expected = 1.5707963267948966;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on a real number") {
        constexpr Real modulus = 0.5;

        Number result;
        function_object(std::vector<Number>{modulus}, result);

        constexpr Real expected = 1.4674622093394272;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on modulus 1") {
        constexpr Real modulus = 1.0;

        Number result;
        function_object(std::vector<Number>{modulus}, result);

        constexpr Real expected = 1.0;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("try to operate on an argument out of the domain") {
        constexpr Real modulus = 2.0;

        Number result;
        function_object(std::vector<Number>{modulus}, result);

        CHECK(std::isnan(std::get<Real>(result)));
    }

    SECTION("check the number of arguments") {
        Number result;
        const Number arg = 1;
        CHECK_THROWS(function_object(std::vector<Number>{}, result));
        CHECK_THROWS(function_object(std::vector<Number>{arg, arg}, result));
    }
}

TEST_CASE("func_sketch::math::elliptic_pi_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::elliptic_pi_function;

    const auto function_object = elliptic_pi_function();

    SECTION("operate on integers") {
        constexpr Integer characteristic = 0;
        constexpr Integer phi = 1;
        constexpr Integer modulus = 0;

        Number result;
        function_object(
            std::vector<Number>{characteristic, phi, modulus}, result);

        constexpr Real expected = 1.0;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers") {
        constexpr Real characteristic = 0.5;
        constexpr Real phi = 0.8;
        constexpr Real modulus = 0.5;

        Number result;
        function_object(
            std::vector<Number>{characteristic, phi, modulus}, result);

        constexpr Real expected = 0.9140029423777822;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with phi larger than pi / 2") {
        constexpr Real characteristic = 0.5;
        constexpr Real phi = 3.0;
        constexpr Real modulus = 0.5;

        Number result;
        function_object(
            std::vector<Number>{characteristic, phi, modulus}, result);

        constexpr Real expected = 4.685157506763253;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with a negative characteristic") {
        constexpr Real characteristic = -2.0;
        constexpr Real phi = 0.8;
        constexpr Real modulus = 0.5;

        Number result;
        function_object(
            std::vector<Number>{characteristic, phi, modulus}, result);

        constexpr Real expected = 0.6243182588678945;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with a characteristic larger than 1") {
        constexpr Real characteristic = 2.0;
        constexpr Real phi = 0.5;
        constexpr Real modulus = 0.5;

        Number result;
        function_object(
            std::vector<Number>{characteristic, phi, modulus}, result);

        constexpr Real expected = 0.6203696923884856;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("try to operate on arguments with n sin^2(phi) > 1") {
        constexpr Real characteristic = 2.0;
        constexpr Real phi = 1.0;
        constexpr Real modulus = 0.5;

        Number result;
        function_object(
            std::vector<Number>{characteristic, phi, modulus}, result);

        CHECK(std::isnan(std::get<Real>(result)));
    }

    SECTION("try to operate on arguments with n > 1 and phi > pi / 2") {
        constexpr Real characteristic = 2.0;
        constexpr Real phi = 3.0;
        constexpr Real modulus = 0.5;

        Number result;
        function_object(
            std::vector<Number>{characteristic, phi, modulus}, result);

        CHECK(std::isnan(std::get<Real>(result)));
    }

    SECTION("try to operate on arguments with k^2 sin^2(phi) > 1") {
        constexpr Real characteristic = 0.5;
        constexpr Real phi = 1.0;
        constexpr Real modulus = 2.0;

        Number result;
        function_object(
            std::vector<Number>{characteristic, phi, modulus}, result);

        CHECK(std::isnan(std::get<Real>(result)));
    }

    SECTION("check the number of arguments") {
        Number result;
        const Number arg = 1;
        CHECK_THROWS(function_object(std::vector<Number>{arg, arg}, result));
        CHECK_THROWS(
            function_object(std::vector<Number>{arg, arg, arg, arg}, result));
    }
}

TEST_CASE("func_sketch::math::comp_elliptic_pi_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::comp_elliptic_pi_function;

    const auto function_object = comp_elliptic_pi_function();

    SECTION("operate on integers") {
        constexpr Integer characteristic = 0;
        constexpr Integer modulus = 0;

        Number result;
        function_object(std::vector<Number>{characteristic, modulus}, result);

        constexpr Real expected = 1.5707963267948966;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers") {
        constexpr Real characteristic = 0.5;
        constexpr Real modulus = 0.5;

        Number result;
        function_object(std::vector<Number>{characteristic, modulus}, result);

        constexpr Real expected = 2.4136715042011945;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with a negative characteristic") {
        constexpr Real characteristic = -2.0;
        constexpr Real modulus = 0.5;

        Number result;
        function_object(std::vector<Number>{characteristic, modulus}, result);

        constexpr Real expected = 0.9547988196277867;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("try to operate on a characteristic larger than 1") {
        constexpr Real characteristic = 2.0;
        constexpr Real modulus = 0.5;

        Number result;
        function_object(std::vector<Number>{characteristic, modulus}, result);

        CHECK(std::isnan(std::get<Real>(result)));
    }

    SECTION("try to operate on a modulus larger than 1") {
        constexpr Real characteristic = 0.5;
        constexpr Real modulus = 2.0;

        Number result;
        function_object(std::vector<Number>{characteristic, modulus}, result);

        CHECK(std::isnan(std::get<Real>(result)));
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
