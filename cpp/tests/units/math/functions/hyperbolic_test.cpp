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
 * \brief Test of hyperbolic functions.
 */
#include "func_sketch/math/functions/hyperbolic.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"
#include "single_variate_function_util.h"

TEST_CASE("func_sketch::math::sinh_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::sinh_function;

    const auto function_object = sinh_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, 3.626860407847019);

        test_single_variate_function<Real, Real>(
            function_object, 1.0, 1.1752011936438014);

        test_single_variate_function<Complex, Complex>(function_object,
            Complex(1.0, 2.0),
            Complex(-0.4890562590412937, 1.4031192506220405));
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::cosh_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::cosh_function;

    const auto function_object = cosh_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, 3.7621956910836314);

        test_single_variate_function<Real, Real>(
            function_object, 1.0, 1.5430806348152437);

        test_single_variate_function<Complex, Complex>(function_object,
            Complex(1.0, 2.0), Complex(-0.64214812471552, 1.0686074213827783));
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::tanh_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::tanh_function;

    const auto function_object = tanh_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, 0.9640275800758169);

        test_single_variate_function<Real, Real>(
            function_object, 1.0, 0.7615941559557649);

        test_single_variate_function<Complex, Complex>(function_object,
            Complex(1.0, 2.0), Complex(1.16673625724092, -0.24345820118572534));
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::asinh_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::asinh_function;

    const auto function_object = asinh_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(function_object, 2,
            1.4436354751788103);  // NOLINT(modernize-use-std-numbers)

        test_single_variate_function<Real, Real>(
            function_object, 1.0, 0.881373587019543);

        test_single_variate_function<Complex, Complex>(function_object,
            Complex(1.0, 2.0), Complex(1.4693517443681854, 1.063440023577752));
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::acosh_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::acosh_function;

    const auto function_object = acosh_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(
            function_object, 2, 1.3169578969248168);

        test_single_variate_function<Real, Real>(
            function_object, 1.5, 0.9624236501192069);

        test_single_variate_function<Complex, Complex>(function_object,
            Complex(1.0, 2.0), Complex(1.5285709194809982, 1.1437177404024204));
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}

TEST_CASE("func_sketch::math::atanh_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::atanh_function;

    const auto function_object = atanh_function();

    SECTION("operate on numbers") {
        test_single_variate_function<Integer, Real>(function_object, 0, 0.0);

        test_single_variate_function<Real, Real>(
            function_object, 0.5, 0.5493061443340549);

        test_single_variate_function<Complex, Complex>(function_object,
            Complex(1.0, 2.0),
            Complex(0.17328679513998632, 1.1780972450961724));
    }

    SECTION("check the number of arguments") {
        test_single_variate_function_errors<Real>(function_object);
    }
}
