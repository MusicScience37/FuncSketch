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
 * \brief Test of miscellaneous floating-point operations.
 */
#include "func_sketch/math/functions/misc_float_operations.h"

#include <cmath>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"
#include "single_variate_function_util.h"

TEST_CASE("func_sketch::math::abs_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::abs_function;

    const auto function_object = abs_function();
    const auto reference_function = [](auto arg) { return std::abs(arg); };

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, reference_function);

        test_single_variate_function<Real, Real>(
            function_object, 1.0, reference_function);

        test_single_variate_function<Complex, Real>(
            function_object, Complex(1.0, 2.0), reference_function);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::ceil_function") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::ceil_function;

    const auto function_object = ceil_function();
    const auto reference_function = [](Real arg) { return std::ceil(arg); };

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, reference_function);

        test_single_variate_function<Real, Real>(
            function_object, 1.5, reference_function);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::floor_function") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::floor_function;

    const auto function_object = floor_function();
    const auto reference_function = [](Real arg) { return std::floor(arg); };

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, reference_function);

        test_single_variate_function<Real, Real>(
            function_object, 1.5, reference_function);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::trunc_function") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::trunc_function;

    const auto function_object = trunc_function();
    const auto reference_function = [](Real arg) { return std::trunc(arg); };

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, reference_function);

        test_single_variate_function<Real, Real>(
            function_object, 1.5, reference_function);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::round_function") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::round_function;

    const auto function_object = round_function();
    const auto reference_function = [](Real arg) { return std::round(arg); };

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, reference_function);

        test_single_variate_function<Real, Real>(
            function_object, 1.5, reference_function);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}
