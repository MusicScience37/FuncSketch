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
 * \brief Implementation of functions to create Bessel functions and related
 * functions.
 */
#include "func_sketch/math/functions/bessel.h"

#include <utility>

#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/hankel.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/math/acceptable_types.h"
#include "func_sketch/math/general_math_function.h"
#include "func_sketch/math/math_function.h"

namespace func_sketch::math {

MathFunction bessel_j_function(
    std::function<Complex(Real, Complex)> complex_bessel_j) {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Integer, Real>,
            AcceptableTypes<Real, Complex>>>("bessel_j",
            [complex_bessel_j = std::move(complex_bessel_j)](
                auto order, auto arg) {
                using ArgType = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<ArgType, Complex>) {
                    return complex_bessel_j(static_cast<Real>(order), arg);
                } else {
                    try {
                        return boost::math::cyl_bessel_j(order, arg);
                    } catch (const std::exception& e) {
                        return std::numeric_limits<Real>::quiet_NaN();
                    }
                }
            }));
}

MathFunction bessel_y_function(
    std::function<Complex(Real, Complex)> complex_bessel_y) {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Integer, Real>,
            AcceptableTypes<Real, Complex>>>("bessel_y",
            [complex_bessel_y = std::move(complex_bessel_y)](
                auto order, auto arg) {
                using ArgType = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<ArgType, Complex>) {
                    return complex_bessel_y(static_cast<Real>(order), arg);
                } else {
                    try {
                        return boost::math::cyl_neumann(order, arg);
                    } catch (const std::exception& e) {
                        return std::numeric_limits<Real>::quiet_NaN();
                    }
                }
            }));
}

MathFunction bessel_i_function(
    std::function<Complex(Real, Complex)> complex_bessel_i) {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Integer, Real>,
            AcceptableTypes<Real, Complex>>>("bessel_i",
            [complex_bessel_i = std::move(complex_bessel_i)](
                auto order, auto arg) {
                using ArgType = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<ArgType, Complex>) {
                    return complex_bessel_i(static_cast<Real>(order), arg);
                } else {
                    try {
                        return boost::math::cyl_bessel_i(order, arg);
                    } catch (const std::exception& e) {
                        return std::numeric_limits<Real>::quiet_NaN();
                    }
                }
            }));
}

MathFunction bessel_k_function(
    std::function<Complex(Real, Complex)> complex_bessel_k) {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Integer, Real>,
            AcceptableTypes<Real, Complex>>>("bessel_k",
            [complex_bessel_k = std::move(complex_bessel_k)](
                auto order, auto arg) {
                using ArgType = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<ArgType, Complex>) {
                    return complex_bessel_k(static_cast<Real>(order), arg);
                } else {
                    try {
                        return boost::math::cyl_bessel_k(order, arg);
                    } catch (const std::exception& e) {
                        return std::numeric_limits<Real>::quiet_NaN();
                    }
                }
            }));
}

MathFunction hankel1_function(
    std::function<Complex(Real, Complex)> complex_hankel1) {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Integer, Real>,
            AcceptableTypes<Real, Complex>>>("hankel1",
            [complex_hankel1 = std::move(complex_hankel1)](
                auto order, auto arg) -> Complex {
                using ArgType = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<ArgType, Complex>) {
                    return complex_hankel1(static_cast<Real>(order), arg);
                } else {
                    try {
                        return boost::math::cyl_hankel_1(order, arg);
                    } catch (const std::exception& e) {
                        return std::numeric_limits<Real>::quiet_NaN();
                    }
                }
            }));
}

MathFunction hankel2_function(
    std::function<Complex(Real, Complex)> complex_hankel2) {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Integer, Real>,
            AcceptableTypes<Real, Complex>>>("hankel2",
            [complex_hankel2 = std::move(complex_hankel2)](
                auto order, auto arg) -> Complex {
                using ArgType = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<ArgType, Complex>) {
                    return complex_hankel2(static_cast<Real>(order), arg);
                } else {
                    try {
                        return boost::math::cyl_hankel_2(order, arg);
                    } catch (const std::exception& e) {
                        return std::numeric_limits<Real>::quiet_NaN();
                    }
                }
            }));
}

}  // namespace func_sketch::math
