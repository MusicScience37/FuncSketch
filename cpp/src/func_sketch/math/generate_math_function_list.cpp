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
 * \brief Implementation of generate_math_function_list function.
 */
#include "func_sketch/math/generate_math_function_list.h"

#include "func_sketch/math/functions/bessel.h"
#include "func_sketch/math/functions/complex.h"
#include "func_sketch/math/functions/erf.h"
#include "func_sketch/math/functions/exp.h"
#include "func_sketch/math/functions/gamma.h"
#include "func_sketch/math/functions/hyperbolic.h"
#include "func_sketch/math/functions/log.h"
#include "func_sketch/math/functions/misc_float_operations.h"
#include "func_sketch/math/functions/pow.h"
#include "func_sketch/math/functions/trigonometric.h"

namespace func_sketch::math {

MathFunctionList generate_math_function_list(
    const PythonFunctionList& python_functions) {
    MathFunctionList list;

    // In exp.h
    list.emplace(exp_function());
    list.emplace(exp2_function());
    list.emplace(expm1_function());

    // In log.h
    list.emplace(log_function());
    list.emplace(log1p_function());
    list.emplace(log10_function());
    list.emplace(log2_function());

    // In pow.h
    list.emplace(pow_function());
    list.emplace(sqrt_function());
    list.emplace(cbrt_function());

    // In trigonometric.h
    list.emplace(sin_function());
    list.emplace(cos_function());
    list.emplace(tan_function());
    list.emplace(asin_function());
    list.emplace(acos_function());
    list.emplace(atan_function());
    list.emplace(atan2_function());

    // In hyperbolic.h
    list.emplace(sinh_function());
    list.emplace(cosh_function());
    list.emplace(tanh_function());
    list.emplace(asinh_function());
    list.emplace(acosh_function());
    list.emplace(atanh_function());

    // In misc_float_operations.h
    list.emplace(abs_function());
    list.emplace(ceil_function());
    list.emplace(floor_function());
    list.emplace(trunc_function());
    list.emplace(round_function());

    // In complex.h
    list.emplace(real_function());
    list.emplace(imag_function());
    list.emplace(arg_function());
    list.emplace(conj_function());

    // In bessel.h
    list.emplace(bessel_j_function(python_functions.complex_bessel_j));
    list.emplace(bessel_y_function(python_functions.complex_bessel_y));
    list.emplace(bessel_i_function(python_functions.complex_bessel_i));
    list.emplace(bessel_k_function(python_functions.complex_bessel_k));
    list.emplace(hankel1_function(python_functions.complex_hankel1));
    list.emplace(hankel2_function(python_functions.complex_hankel2));
    list.emplace(spherical_bessel_j_function(
        python_functions.complex_spherical_bessel_j));
    list.emplace(spherical_bessel_y_function(
        python_functions.complex_spherical_bessel_y));

    // In erf.h
    list.emplace(erf_function());
    list.emplace(erfc_function());

    // In gamma.h
    list.emplace(gamma_function(python_functions.complex_gamma));
    list.emplace(lgamma_function());

    return list;
}

}  // namespace func_sketch::math
