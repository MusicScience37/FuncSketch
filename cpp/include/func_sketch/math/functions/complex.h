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
 * \brief Declaration of functions for complex numbers.
 */
#pragma once

#include "func_sketch/math/math_function.h"

namespace func_sketch::math {

/*!
 * \brief Create `real` function.
 *
 * \return Function.
 */
[[nodiscard]] MathFunction real_function();

/*!
 * \brief Create `imag` function.
 *
 * \return Function.
 */
[[nodiscard]] MathFunction imag_function();

/*!
 * \brief Create `arg` function.
 *
 * \return Function.
 */
[[nodiscard]] MathFunction arg_function();

/*!
 * \brief Create `conj` function.
 *
 * \return Function.
 */
[[nodiscard]] MathFunction conj_function();

}  // namespace func_sketch::math
