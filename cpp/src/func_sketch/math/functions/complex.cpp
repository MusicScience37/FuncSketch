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
 * \brief Implementation of functions for complex numbers.
 */
#include "func_sketch/math/functions/complex.h"

#include "func_sketch/common_types.h"
#include "func_sketch/math/acceptable_types.h"
#include "func_sketch/math/general_math_function.h"
#include "func_sketch/math/math_function.h"

namespace func_sketch::math {

MathFunction real_function() {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Complex>>>(
            "real", [](Complex arg) { return std::real(arg); }));
}

MathFunction imag_function() {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Complex>>>(
            "imag", [](Complex arg) { return std::imag(arg); }));
}

MathFunction arg_function() {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Complex>>>(
            "arg", [](Complex arg) { return std::arg(arg); }));
}

MathFunction conj_function() {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Complex>>>(
            "conj", [](Complex arg) { return std::conj(arg); }));
}

}  // namespace func_sketch::math
