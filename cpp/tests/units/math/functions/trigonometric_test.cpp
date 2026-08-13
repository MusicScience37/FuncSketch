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

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, 0.9092974268256817);

        test_single_variate_function<Real, Real>(
            function_object, 1.0, 0.8414709848078965);
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

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, -0.4161468365471424);

        test_single_variate_function<Real, Real>(
            function_object, 1.0, 0.5403023058681398);
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

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, -2.185039863261519);

        test_single_variate_function<Real, Real>(
            function_object, 1.0, 1.5574077246549023);
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

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(function_object, 0, 0.0);

        test_single_variate_function<Real, Real>(
            function_object, 0.5, 0.5235987755982989);
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

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 0, 1.5707963267948966);

        test_single_variate_function<Real, Real>(
            function_object, 0.5, 1.0471975511965979);
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

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, 1.1071487177940904);

        test_single_variate_function<Real, Real>(
            function_object, 1.0, 0.7853981633974483);
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

        constexpr Real expected = 0.4636476090008061;
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
