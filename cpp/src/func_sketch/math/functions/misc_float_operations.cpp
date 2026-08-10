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
 * \brief Implementation of functions to create functions of miscellaneous
 * floating-point operations.
 */
#include "func_sketch/math/functions/misc_float_operations.h"

#include <cmath>

#include "func_sketch/common_types.h"
#include "func_sketch/math/acceptable_types.h"
#include "func_sketch/math/general_math_function.h"
#include "func_sketch/math/math_function.h"

namespace func_sketch::math {

MathFunction abs_function() {
    return MathFunction(
        make_general_math_function<std::tuple<AcceptableTypes<Real>>>(
            "abs", [](Real arg) { return std::abs(arg); }));
}

}  // namespace func_sketch::math
