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
 * \brief Implementation of functions to create gamma functions.
 */
#include "func_sketch/math/functions/gamma.h"

#include <limits>
#include <utility>

#include <boost/math/special_functions/digamma.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/polygamma.hpp>
#include <boost/math/special_functions/trigamma.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/math/acceptable_types.h"
#include "func_sketch/math/functions/boost_math_policy.h"
#include "func_sketch/math/general_math_function.h"
#include "func_sketch/math/math_function.h"

namespace func_sketch::math {

MathFunction gamma_function(std::function<Complex(Complex)> complex_gamma) {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Real, Complex>>>(
            "gamma", [complex_gamma = std::move(complex_gamma)](auto arg) {
                using ArgType = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<ArgType, Complex>) {
                    return complex_gamma(arg);
                } else {
                    return boost::math::tgamma(arg, BoostMathPolicy());
                }
            }));
}

MathFunction lgamma_function() {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Real>>>(
            "lgamma", [](Real arg) {
                return boost::math::lgamma(arg, BoostMathPolicy());
            }));
}

MathFunction digamma_function() {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Real>>>(
            "digamma", [](Real arg) {
                return boost::math::digamma(arg, BoostMathPolicy());
            }));
}

MathFunction trigamma_function() {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Real>>>(
            "trigamma", [](Real arg) {
                return boost::math::trigamma(arg, BoostMathPolicy());
            }));
}

MathFunction polygamma_function() {
    return MathFunction(make_general_math_function<
        std::tuple<AcceptableTypes<Integer>, AcceptableTypes<Real>>>(
        "polygamma", [](Integer order, Real arg) {
            if (order < 0) {
                return std::numeric_limits<Real>::quiet_NaN();
            }
            return boost::math::polygamma(order, arg, BoostMathPolicy());
        }));
}

MathFunction igamma_function() {
    return MathFunction(make_general_math_function<
        std::tuple<AcceptableTypes<Real>, AcceptableTypes<Real>>>(
        "igamma", [](Real param_a, Real x) {
            return boost::math::gamma_p(param_a, x, BoostMathPolicy());
        }));
}

MathFunction igammac_function() {
    return MathFunction(make_general_math_function<
        std::tuple<AcceptableTypes<Real>, AcceptableTypes<Real>>>(
        "igammac", [](Real param_a, Real x) {
            return boost::math::gamma_q(param_a, x, BoostMathPolicy());
        }));
}

}  // namespace func_sketch::math
