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
 * \brief Definition of MathFunctionType concept.
 */
#pragma once

#include <concepts>
#include <string_view>
#include <vector>

#include "func_sketch/common_types.h"

namespace func_sketch::math {

/*!
 * \brief Concept of mathematical function types.
 *
 * \tparam T Type of the function object.
 */
template <typename T>
concept MathFunctionType = requires() {
    requires requires(const T& function_object) {
        { function_object.name() } -> std::convertible_to<std::string_view>;
    };

    requires requires(const T& function_object, const std::vector<Number>& args,
        Number& result) {
        { function_object(args, result) } -> std::same_as<void>;
    };
};

}  // namespace func_sketch::math
