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
 * \brief Implementation of functions to create elliptic integrals.
 */
#include "func_sketch/math/functions/elliptic_integrals.h"

#include <cmath>
#include <limits>
#include <numbers>

#include <boost/math/special_functions/ellint_1.hpp>
#include <boost/math/special_functions/ellint_2.hpp>
#include <boost/math/special_functions/ellint_3.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/math/acceptable_types.h"
#include "func_sketch/math/functions/boost_math_policy.h"
#include "func_sketch/math/general_math_function.h"
#include "func_sketch/math/math_function.h"

namespace func_sketch::math {

MathFunction elliptic_f_function() {
    return MathFunction(make_general_math_function<
        std::tuple<AcceptableTypes<Real>, AcceptableTypes<Real>>>(
        "elliptic_f", [](Real phi, Real modulus) {
            return boost::math::ellint_1(modulus, phi, BoostMathPolicy());
        }));
}

MathFunction comp_elliptic_k_function() {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Real>>>(
            "comp_elliptic_k", [](Real modulus) {
                return boost::math::ellint_1(modulus, BoostMathPolicy());
            }));
}

MathFunction elliptic_e_function() {
    return MathFunction(make_general_math_function<
        std::tuple<AcceptableTypes<Real>, AcceptableTypes<Real>>>(
        "elliptic_e", [](Real phi, Real modulus) {
            return boost::math::ellint_2(modulus, phi, BoostMathPolicy());
        }));
}

MathFunction comp_elliptic_e_function() {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Real>>>(
            "comp_elliptic_e", [](Real modulus) {
                return boost::math::ellint_2(modulus, BoostMathPolicy());
            }));
}

MathFunction elliptic_pi_function() {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Real>,
            AcceptableTypes<Real>, AcceptableTypes<Real>>>(
            "elliptic_pi", [](Real characteristic, Real phi, Real modulus) {
                // Limit to the range where no pole exists.
                if (characteristic >= 1.0 &&
                    std::abs(phi) > 0.5 * std::numbers::pi) {
                    return std::numeric_limits<Real>::quiet_NaN();
                }
                return boost::math::ellint_3(
                    modulus, characteristic, phi, BoostMathPolicy());
            }));
}

}  // namespace func_sketch::math
