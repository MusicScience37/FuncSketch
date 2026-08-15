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
 * \brief Test of functions to create Bessel functions and related
 * functions.
 */
#include "func_sketch/math/functions/bessel.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"

TEST_CASE("func_sketch::math::bessel_j_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::bessel_j_function;

    // Bessel function for complex arguments will be assigned in the binding
    // code, so empty function is used here. Tests for complex arguments will be
    // done in Python.
    const std::function<Complex(Real, Complex)> complex_bessel_j;
    const auto function_object = bessel_j_function(complex_bessel_j);

    SECTION("operate on an integer order and a real argument") {
        constexpr Integer order = 2;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Real expected = 0.23208767214421475;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on a real order and a real argument") {
        constexpr Real order = 2.5;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Real expected = 0.12444635979838772;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }
}

TEST_CASE("func_sketch::math::bessel_y_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::bessel_y_function;

    // Bessel function for complex arguments will be assigned in the binding
    // code, so empty function is used here. Tests for complex arguments will be
    // done in Python.
    const std::function<Complex(Real, Complex)> complex_bessel_y;
    const auto function_object = bessel_y_function(complex_bessel_y);

    SECTION("operate on an integer order and a real argument") {
        constexpr Integer order = 2;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Real expected = -0.9321937597629739;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on a real order and a real argument") {
        constexpr Real order = 2.5;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Real expected = -1.315037204805194;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }
}

TEST_CASE("func_sketch::math::bessel_i_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::bessel_i_function;

    // Bessel function for complex arguments will be assigned in the binding
    // code, so empty function is used here. Tests for complex arguments will be
    // done in Python.
    const std::function<Complex(Real, Complex)> complex_bessel_i;
    const auto function_object = bessel_i_function(complex_bessel_i);

    SECTION("operate on an integer order and a real argument") {
        constexpr Integer order = 2;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Real expected = 0.33783461833568074;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on a real order and a real argument") {
        constexpr Real order = 2.5;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Real expected = 0.17166202218829626;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }
}

TEST_CASE("func_sketch::math::bessel_k_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::bessel_k_function;

    // Bessel function for complex arguments will be assigned in the binding
    // code, so empty function is used here. Tests for complex arguments will be
    // done in Python.
    const std::function<Complex(Real, Complex)> complex_bessel_k;
    const auto function_object = bessel_k_function(complex_bessel_k);

    SECTION("operate on an integer order and a real argument") {
        constexpr Integer order = 2;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Real expected = 0.5836559632566507;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }

    SECTION("operate on a real order and a real argument") {
        constexpr Real order = 2.5;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Real expected = 0.9894518929891505;
        CHECK_THAT(
            std::get<Real>(result), Catch::Matchers::WithinRel(expected));
    }
}

TEST_CASE("func_sketch::math::hankel1_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::hankel1_function;

    // Bessel function for complex arguments will be assigned in the binding
    // code, so empty function is used here. Tests for complex arguments will be
    // done in Python.
    const std::function<Complex(Real, Complex)> complex_hankel1;
    const auto function_object = hankel1_function(complex_hankel1);

    SECTION("operate on an integer order and a real argument") {
        constexpr Integer order = 2;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Complex expected{0.23208767214421475, -0.9321937597629739};
        CHECK_THAT(std::get<Complex>(result).real(),
            Catch::Matchers::WithinRel(expected.real()));
        CHECK_THAT(std::get<Complex>(result).imag(),
            Catch::Matchers::WithinRel(expected.imag()));
    }

    SECTION("operate on a real order and a real argument") {
        constexpr Real order = 2.5;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Complex expected{0.12444635979838772, -1.315037204805194};
        CHECK_THAT(std::get<Complex>(result).real(),
            Catch::Matchers::WithinRel(expected.real()));
        CHECK_THAT(std::get<Complex>(result).imag(),
            Catch::Matchers::WithinRel(expected.imag()));
    }
}

TEST_CASE("func_sketch::math::hankel2_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::hankel2_function;

    // Bessel function for complex arguments will be assigned in the binding
    // code, so empty function is used here. Tests for complex arguments will be
    // done in Python.
    const std::function<Complex(Real, Complex)> complex_hankel2;
    const auto function_object = hankel2_function(complex_hankel2);

    SECTION("operate on an integer order and a real argument") {
        constexpr Integer order = 2;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Complex expected{0.23208767214421475, 0.9321937597629739};
        CHECK_THAT(std::get<Complex>(result).real(),
            Catch::Matchers::WithinRel(expected.real()));
        CHECK_THAT(std::get<Complex>(result).imag(),
            Catch::Matchers::WithinRel(expected.imag()));
    }

    SECTION("operate on a real order and a real argument") {
        constexpr Real order = 2.5;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Complex expected{0.12444635979838772, 1.315037204805194};
        CHECK_THAT(std::get<Complex>(result).real(),
            Catch::Matchers::WithinRel(expected.real()));
        CHECK_THAT(std::get<Complex>(result).imag(),
            Catch::Matchers::WithinRel(expected.imag()));
    }
}

TEST_CASE("func_sketch::math::spherical_bessel_j_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::spherical_bessel_j_function;

    // Bessel function for complex arguments will be assigned in the binding
    // code, so empty function is used here. Tests for complex arguments will be
    // done in Python.
    const std::function<Complex(unsigned, Complex)> complex_spherical_bessel_j;
    const auto function_object =
        spherical_bessel_j_function(complex_spherical_bessel_j);

    SECTION("operate on an integer order and a real argument") {
        constexpr Integer order = 2;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Real expected = 0.12734928368840834;
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
}

TEST_CASE("func_sketch::math::spherical_bessel_y_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::spherical_bessel_y_function;

    // Bessel function for complex arguments will be assigned in the binding
    // code, so empty function is used here. Tests for complex arguments will be
    // done in Python.
    const std::function<Complex(unsigned, Complex)> complex_spherical_bessel_y;
    const auto function_object =
        spherical_bessel_y_function(complex_spherical_bessel_y);

    SECTION("operate on an integer order and a real argument") {
        constexpr Integer order = 2;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Real expected = -1.3457126936204509;
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
}

TEST_CASE("func_sketch::math::spherical_hankel1_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::spherical_hankel1_function;

    // Bessel function for complex arguments will be assigned in the binding
    // code, so empty function is used here. Tests for complex arguments will be
    // done in Python.
    const std::function<Complex(unsigned, Complex)> complex_spherical_bessel_j;
    const std::function<Complex(unsigned, Complex)> complex_spherical_bessel_y;
    const auto function_object = spherical_hankel1_function(
        complex_spherical_bessel_j, complex_spherical_bessel_y);

    SECTION("operate on an integer order and a real argument") {
        constexpr Integer order = 2;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Complex expected{0.12734928368840834, -1.3457126936204509};
        CHECK_THAT(std::get<Complex>(result).real(),
            Catch::Matchers::WithinRel(expected.real()));
        CHECK_THAT(std::get<Complex>(result).imag(),
            Catch::Matchers::WithinRel(expected.imag()));
    }

    SECTION("try to operate on a negative order") {
        constexpr Integer order = -1;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        CHECK(std::isnan(std::get<Complex>(result).real()));
    }

    SECTION("try to operate on a real number order") {
        constexpr Real order = 2.5;
        constexpr Real argument = 1.5;

        Number result;
        CHECK_THROWS(
            function_object(std::vector<Number>{order, argument}, result));
    }
}

TEST_CASE("func_sketch::math::spherical_hankel2_function") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::spherical_hankel2_function;

    // Bessel function for complex arguments will be assigned in the binding
    // code, so empty function is used here. Tests for complex arguments will be
    // done in Python.
    const std::function<Complex(unsigned, Complex)> complex_spherical_bessel_j;
    const std::function<Complex(unsigned, Complex)> complex_spherical_bessel_y;
    const auto function_object = spherical_hankel2_function(
        complex_spherical_bessel_j, complex_spherical_bessel_y);

    SECTION("operate on an integer order and a real argument") {
        constexpr Integer order = 2;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        constexpr Complex expected{0.12734928368840834, 1.3457126936204509};
        CHECK_THAT(std::get<Complex>(result).real(),
            Catch::Matchers::WithinRel(expected.real()));
        CHECK_THAT(std::get<Complex>(result).imag(),
            Catch::Matchers::WithinRel(expected.imag()));
    }

    SECTION("try to operate on a negative order") {
        constexpr Integer order = -1;
        constexpr Real argument = 1.5;

        Number result;
        function_object(std::vector<Number>{order, argument}, result);

        CHECK(std::isnan(std::get<Complex>(result).real()));
    }

    SECTION("try to operate on a real number order") {
        constexpr Real order = 2.5;
        constexpr Real argument = 1.5;

        Number result;
        CHECK_THROWS(
            function_object(std::vector<Number>{order, argument}, result));
    }
}
