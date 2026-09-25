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
 * \brief Implementation of MathFunctionList class.
 */
#include "func_sketch/math/math_function_list.h"

namespace func_sketch::math {

std::vector<MathFunctionInfo> MathFunctionList::create_function_info_list()
    const {
    std::vector<MathFunctionInfo> info_list;
    info_list.reserve(functions_.size());
    for (const auto& [name, function] : functions_) {
        info_list.emplace_back(name);
    }
    return info_list;
}

}  // namespace func_sketch::math
