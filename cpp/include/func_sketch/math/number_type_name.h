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
 * \brief Definition of number_type_name constant.
 */
#pragma once

#include <string_view>

#include "func_sketch/common_types.h"

namespace func_sketch::math {

namespace details {

/*!
 * \brief Traits struct to get name of number type.
 *
 * \tparam T Type of number.
 *
 * \note Specializations of this struct must define static constexpr member
 * variable "name" of type std::string_view, which is name of number type.
 * The name is used in error messages for users and assumed to end with
 * "number".
 */
template <typename T>
struct NumberTypeNameTraits;

/*!
 * \brief Specialization of NumberTypeNameTraits for Real.
 */
template <>
struct NumberTypeNameTraits<Real> {
    /*!
     * \brief Name of number type.
     */
    static constexpr std::string_view name = "real number";
};

/*!
 * \brief Specialization of NumberTypeNameTraits for Integer.
 */
template <>
struct NumberTypeNameTraits<Integer> {
    /*!
     * \brief Name of number type.
     */
    static constexpr std::string_view name = "integer number";
};

/*!
 * \brief Specialization of NumberTypeNameTraits for Complex.
 */
template <>
struct NumberTypeNameTraits<Complex> {
    /*!
     * \brief Name of number type.
     */
    static constexpr std::string_view name = "complex number";
};

}  // namespace details

/*!
 * \brief Name of the number type.
 *
 * \tparam T Type of number.
 *
 * \note This constant is used in error messages for users and assumed to end
 * with "number".
 */
template <typename T>
constexpr std::string_view number_type_name =
    details::NumberTypeNameTraits<T>::name;

}  // namespace func_sketch::math
