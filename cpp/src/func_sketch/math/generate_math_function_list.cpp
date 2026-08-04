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

#include "func_sketch/math/functions/exp.h"

namespace func_sketch::math {

MathFunctionList generate_math_function_list() {
    MathFunctionList list;
    list.emplace(ExpFunction());
    return list;
}

}  // namespace func_sketch::math
