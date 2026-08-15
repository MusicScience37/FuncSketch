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
 * \brief Definition of PythonFunctionList struct.
 */
#pragma once

#include <functional>

#include "func_sketch/common_types.h"

namespace func_sketch::math {

/*!
 * \brief Struct of functions from Python.
 *
 * \note This struct holds functions from Python which are difficult to
 * implement in C++. Functions are inserted into this struct in the binding
 * code.
 */
struct PythonFunctionList {
    //! Gamma function for complex arguments.
    std::function<Complex(Complex)> complex_gamma;

    //! Cylindrical Bessel function of the first kind for complex arguments.
    std::function<Complex(Real, Complex)> complex_bessel_j;

    //! Cylindrical Bessel function of the second kind for complex arguments.
    std::function<Complex(Real, Complex)> complex_bessel_y;

    //! Cylindrical modified Bessel function of the first kind for complex arguments.
    std::function<Complex(Real, Complex)> complex_bessel_i;

    //! Cylindrical modified Bessel function of the second kind for complex arguments.
    std::function<Complex(Real, Complex)> complex_bessel_k;
};

}  // namespace func_sketch::math
