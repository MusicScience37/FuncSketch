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
 * \brief Declaration of functions to create functions of miscellaneous
 * floating-point operations.
 */
#pragma once

#include "func_sketch/math/math_function.h"

namespace func_sketch::math {

/*!
 * \brief Create `abs` function.
 *
 * \return Function.
 */
[[nodiscard]] MathFunction abs_function();

/*!
 * \brief Create `ceil` function.
 *
 * \return Function.
 */
[[nodiscard]] MathFunction ceil_function();

/*!
 * \brief Create `floor` function.
 *
 * \return Function.
 */
[[nodiscard]] MathFunction floor_function();

/*!
 * \brief Create `trunc` function.
 *
 * \return Function.
 */
[[nodiscard]] MathFunction trunc_function();

/*!
 * \brief Create `round` function.
 *
 * \return Function.
 */
[[nodiscard]] MathFunction round_function();

}  // namespace func_sketch::math
