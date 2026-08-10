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
 * \brief Test of trigonometric functions.
 */
#include "func_sketch/math/functions/trigonometric.h"

#include <cmath>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"
#include "single_variate_function_util.h"

TEST_CASE("func_sketch::math::sin_function") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::sin_function;

    const auto function_object = sin_function();
    const auto reference_function = [](Real arg) { return std::sin(arg); };

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, reference_function);

        test_single_variate_function<Real, Real>(
            function_object, 1.0, reference_function);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::cos_function") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::cos_function;

    const auto function_object = cos_function();
    const auto reference_function = [](Real arg) { return std::cos(arg); };

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, reference_function);

        test_single_variate_function<Real, Real>(
            function_object, 1.0, reference_function);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::tan_function") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::tan_function;

    const auto function_object = tan_function();
    const auto reference_function = [](Real arg) { return std::tan(arg); };

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, reference_function);

        test_single_variate_function<Real, Real>(
            function_object, 1.0, reference_function);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::asin_function") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::asin_function;

    const auto function_object = asin_function();
    const auto reference_function = [](Real arg) { return std::asin(arg); };

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 0, reference_function);

        test_single_variate_function<Real, Real>(
            function_object, 0.5, reference_function);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::acos_function") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::acos_function;

    const auto function_object = acos_function();
    const auto reference_function = [](Real arg) { return std::acos(arg); };

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 0, reference_function);

        test_single_variate_function<Real, Real>(
            function_object, 0.5, reference_function);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::atan_function") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::atan_function;

    const auto function_object = atan_function();
    const auto reference_function = [](Real arg) { return std::atan(arg); };

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, reference_function);

        test_single_variate_function<Real, Real>(
            function_object, 1.0, reference_function);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::atan2_function") {
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::atan2_function;

    const auto function_object = atan2_function();

    SECTION("operate on numbers") {
        constexpr Real y_value = 1.0;
        constexpr Real x_value = 2.0;

        Number result;
        function_object(std::vector<Number>{y_value, x_value}, result);

        const Real expected = std::atan2(y_value, x_value);
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
