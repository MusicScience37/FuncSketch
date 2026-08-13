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
 * \brief Test of functions for complex numbers.
 */
#include "func_sketch/math/functions/complex.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"
#include "single_variate_function_util.h"

TEST_CASE("func_sketch::math::real_function") {
    using func_sketch::Complex;
    using func_sketch::Real;
    using func_sketch::math::real_function;

    const auto function_object = real_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Complex, Real>(
            function_object, Complex(1.23, 2.34), 1.23);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Complex>(function_object);
    }
}

TEST_CASE("func_sketch::math::imag_function") {
    using func_sketch::Complex;
    using func_sketch::Real;
    using func_sketch::math::imag_function;

    const auto function_object = imag_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Complex, Real>(
            function_object, Complex(1.23, 2.34), 2.34);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Complex>(function_object);
    }
}

TEST_CASE("func_sketch::math::arg_function") {
    using func_sketch::Complex;
    using func_sketch::Real;
    using func_sketch::math::arg_function;

    const auto function_object = arg_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Complex, Real>(
            function_object, Complex(1.23, 2.34), 1.086846938934872);
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Complex>(function_object);
    }
}

TEST_CASE("func_sketch::math::conj_function") {
    using func_sketch::Complex;
    using func_sketch::Real;
    using func_sketch::math::conj_function;

    const auto function_object = conj_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Complex, Complex>(
            function_object, Complex(1.23, 2.34), Complex(1.23, -2.34));
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Complex>(function_object);
    }
}
