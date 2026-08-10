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
 * \brief Declaration of functions to create hyperbolic functions.
 */
#pragma once

#include "func_sketch/math/math_function.h"

namespace func_sketch::math {

/*!
 * \brief Create `sinh` function.
 *
 * \return Function.
 */
[[nodiscard]] MathFunction sinh_function();

/*!
 * \brief Create `cosh` function.
 *
 * \return Function.
 */
[[nodiscard]] MathFunction cosh_function();

/*!
 * \brief Create `tanh` function.
 *
 * \return Function.
 */
[[nodiscard]] MathFunction tanh_function();

/*!
 * \brief Create `asinh` function.
 *
 * \return Function.
 */
[[nodiscard]] MathFunction asinh_function();

/*!
 * \brief Create `acosh` function.
 *
 * \return Function.
 */
[[nodiscard]] MathFunction acosh_function();

/*!
 * \brief Create `atanh` function.
 *
 * \return Function.
 */
[[nodiscard]] MathFunction atanh_function();

}  // namespace func_sketch::math
