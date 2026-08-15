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
 * \brief Declaration of functions to create Bessel functions and related
 * functions.
 */
#pragma once

#include <functional>

#include "func_sketch/common_types.h"
#include "func_sketch/math/math_function.h"

namespace func_sketch::math {

/*!
 * \brief Create `bessel_j` function.
 *
 * \param[in] complex_bessel_j Function for complex arguments.
 * \return Function.
 */
[[nodiscard]] MathFunction bessel_j_function(
    std::function<Complex(Real, Complex)> complex_bessel_j);

/*!
 * \brief Create `bessel_y` function.
 *
 * \param[in] complex_bessel_y Function for complex arguments.
 * \return Function.
 */
[[nodiscard]] MathFunction bessel_y_function(
    std::function<Complex(Real, Complex)> complex_bessel_y);

/*!
 * \brief Create `bessel_i` function.
 *
 * \param[in] complex_bessel_i Function for complex arguments.
 * \return Function.
 */
[[nodiscard]] MathFunction bessel_i_function(
    std::function<Complex(Real, Complex)> complex_bessel_i);

/*!
 * \brief Create `bessel_k` function.
 *
 * \param[in] complex_bessel_k Function for complex arguments.
 * \return Function.
 */
[[nodiscard]] MathFunction bessel_k_function(
    std::function<Complex(Real, Complex)> complex_bessel_k);

/*!
 * \brief Create `hankel1` function.
 *
 * \param[in] complex_hankel1 Function for complex arguments.
 * \return Function.
 */
[[nodiscard]] MathFunction hankel1_function(
    std::function<Complex(Real, Complex)> complex_hankel1);

/*!
 * \brief Create `hankel2` function.
 *
 * \param[in] complex_hankel2 Function for complex arguments.
 * \return Function.
 */
[[nodiscard]] MathFunction hankel2_function(
    std::function<Complex(Real, Complex)> complex_hankel2);

/*!
 * \brief Create `spherical_bessel_j` function.
 *
 * \param[in] complex_spherical_bessel_j Function for complex arguments.
 * \return Function.
 */
[[nodiscard]] MathFunction spherical_bessel_j_function(
    std::function<Complex(unsigned, Complex)> complex_spherical_bessel_j);

/*!
 * \brief Create `spherical_bessel_y` function.
 *
 * \param[in] complex_spherical_bessel_y Function for complex arguments.
 * \return Function.
 */
[[nodiscard]] MathFunction spherical_bessel_y_function(
    std::function<Complex(unsigned, Complex)> complex_spherical_bessel_y);

}  // namespace func_sketch::math
