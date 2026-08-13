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

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"
#include "single_variate_function_util.h"

TEST_CASE("func_sketch::math::exp_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::exp_function;

    const auto function_object = exp_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, 7.38905609893065);

        test_single_variate_function<Real, Real>(function_object, 1.0,
            2.718281828459045);  // NOLINT(modernize-use-std-numbers)

        test_single_variate_function<Complex, Complex>(function_object,
            Complex(1.0, 2.0),
            Complex(-1.1312043837568135, 2.4717266720048188));
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::exp2_function") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::exp2_function;

    const auto function_object = exp2_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(function_object, 2, 4.0);

        test_single_variate_function<Real, Real>(function_object, 1.0, 2.0);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::expm1_function") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::expm1_function;

    const auto function_object = expm1_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, 6.38905609893065);

        test_single_variate_function<Real, Real>(
            function_object, 1.0, 1.718281828459045);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}
