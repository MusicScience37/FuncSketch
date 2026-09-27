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
 * \brief Test of gamma functions.
 */
#include "func_sketch/math/functions/gamma.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"
#include "single_variate_function_util.h"

TEST_CASE("func_sketch::math::gamma_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::gamma_function;

    // Gamma function for complex arguments will be assigned in the binding
    // code, so empty function is used here. Tests for complex arguments will be
    // done in Python.
    const std::function<Complex(Complex)> complex_gamma;
    const auto function_object = gamma_function(complex_gamma);

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(function_object, 3, 2.0);

        test_single_variate_function<Real, Real>(
            function_object, 0.5, 1.7724538509055159);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::lgamma_function") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::lgamma_function;

    const auto function_object = lgamma_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(function_object, 3,
            0.6931471805599453);  // NOLINT(modernize-use-std-numbers)

        test_single_variate_function<Real, Real>(
            function_object, 0.5, 0.5723649429247004);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::digamma_function") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::digamma_function;

    const auto function_object = digamma_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(function_object, 1,
            -0.5772156649015329);  // NOLINT(modernize-use-std-numbers)

        test_single_variate_function<Real, Real>(
            function_object, 0.5, -1.9635100260214235);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::trigamma_function") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::trigamma_function;

    const auto function_object = trigamma_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 1, 1.6449340668482264);

        test_single_variate_function<Real, Real>(
            function_object, 0.5, 4.934802200544679);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::polygamma_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::polygamma_function;

    const auto function_object = polygamma_function();

    SECTION("operate on an integer order and a real argument") {
        constexpr Integer order = 2;
        constexpr Real argument = 0.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Real expected = -16.828796644234316;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on an integer order and an integer argument") {
        constexpr Integer order = 2;
        constexpr Integer argument = 1;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Real expected = -2.404113806319188;
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

TEST_CASE("func_sketch::math::igamma_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::igamma_function;

    const auto function_object = igamma_function();

    SECTION("operate on integers") {
        constexpr Integer param_a = 2;
        constexpr Integer x = 1;

        Number result;
        function_object(std::vector<Number>{param_a, x}, result);

        constexpr Real expected = 0.2642411176571153;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers") {
        constexpr Real param_a = 1.5;
        constexpr Real x = 2.0;

        Number result;
        function_object(std::vector<Number>{param_a, x}, result);

        constexpr Real expected = 0.7385358700508888;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("check the number of arguments") {
        Number result;
        const Number arg = 1;
        CHECK_THROWS(function_object(std::vector<Number>{arg}, result));
        CHECK_THROWS(
            function_object(std::vector<Number>{arg, arg, arg}, result));
    }
}

TEST_CASE("func_sketch::math::igammac_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::igammac_function;

    const auto function_object = igammac_function();

    SECTION("operate on integers") {
        constexpr Integer param_a = 2;
        constexpr Integer x = 1;

        Number result;
        function_object(std::vector<Number>{param_a, x}, result);

        constexpr Real expected = 0.7357588823428847;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on real numbers") {
        constexpr Real param_a = 1.5;
        constexpr Real x = 2.0;

        Number result;
        function_object(std::vector<Number>{param_a, x}, result);

        constexpr Real expected = 0.26146412994911117;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("check the number of arguments") {
        Number result;
        const Number arg = 1;
        CHECK_THROWS(function_object(std::vector<Number>{arg}, result));
        CHECK_THROWS(
            function_object(std::vector<Number>{arg, arg, arg}, result));
    }
}
