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
 * \brief Test of Jacobi elliptic functions.
 */
#include "func_sketch/math/functions/jacobi_elliptic.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"

TEST_CASE("func_sketch::math::jacobi_sn_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::jacobi_sn_function;

    const auto function_object = jacobi_sn_function();

    SECTION("operate on integers") {
        constexpr Integer argument = 1;
        constexpr Integer modulus = 0;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 0.8414709848078965;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers") {
        constexpr Real argument = 0.8;
        constexpr Real modulus = 0.5;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 0.7042121415471675;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with a large argument") {
        constexpr Real argument = 3.0;
        constexpr Real modulus = 0.9;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 0.9442446608129369;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with a negative modulus") {
        constexpr Real argument = 0.8;
        constexpr Real modulus = -0.5;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 0.7042121415471675;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with modulus 1") {
        constexpr Real argument = 1.5;
        constexpr Real modulus = 1.0;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 0.9051482536448664;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with a modulus larger than 1") {
        constexpr Real argument = 0.8;
        constexpr Real modulus = 2.0;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 0.4986210795513635;
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

TEST_CASE("func_sketch::math::jacobi_cn_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::jacobi_cn_function;

    const auto function_object = jacobi_cn_function();

    SECTION("operate on integers") {
        constexpr Integer argument = 1;
        constexpr Integer modulus = 0;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 0.5403023058681398;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers") {
        constexpr Real argument = 0.8;
        constexpr Real modulus = 0.5;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 0.7099896194294337;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with a large argument") {
        constexpr Real argument = 3.0;
        constexpr Real modulus = 0.9;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = -0.3292446211045241;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with a negative modulus") {
        constexpr Real argument = 0.8;
        constexpr Real modulus = -0.5;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 0.7099896194294337;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with modulus 1") {
        constexpr Real argument = 1.5;
        constexpr Real modulus = 1.0;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 0.4250960349422805;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with a modulus larger than 1") {
        constexpr Real argument = 0.8;
        constexpr Real modulus = 2.0;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 0.866820061504712;
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

TEST_CASE("func_sketch::math::jacobi_dn_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::jacobi_dn_function;

    const auto function_object = jacobi_dn_function();

    SECTION("operate on integers") {
        constexpr Integer argument = 1;
        constexpr Integer modulus = 0;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 1.0;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers") {
        constexpr Real argument = 0.8;
        constexpr Real modulus = 0.5;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 0.9359601032759827;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with a large argument") {
        constexpr Real argument = 3.0;
        constexpr Real modulus = 0.9;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 0.5270727052563734;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with a negative modulus") {
        constexpr Real argument = 0.8;
        constexpr Real modulus = -0.5;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 0.9359601032759827;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with modulus 1") {
        constexpr Real argument = 1.5;
        constexpr Real modulus = 1.0;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 0.4250960349422805;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers with a modulus larger than 1") {
        constexpr Real argument = 0.8;
        constexpr Real modulus = 2.0;

        Number result;
        function_object(std::vector<Number>{argument, modulus}, result);

        constexpr Real expected = 0.07421641400749103;
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
