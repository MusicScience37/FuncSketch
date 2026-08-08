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
 * \brief Definition of BinaryOperatorType concept.
 */
#pragma once

#include <concepts>
#include <string_view>

#include "func_sketch/common_types.h"

namespace func_sketch::math {

/*!
 * \brief Concept of binary operator types.
 *
 * \tparam T Type of the operator object.
 */
template <typename T>
concept BinaryOperatorType = requires() {
    requires requires(const T& operator_object) {
        { operator_object.name() } -> std::convertible_to<std::string_view>;
    };

    requires requires(const T& operator_object, const Number& left,
        const Number& right, Number& result) {
        { operator_object(left, right, result) } -> std::same_as<void>;
    };
};

}  // namespace func_sketch::math
