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
 * \brief Definition of pow_number function.
 */
#pragma once

#include <cmath>

#include "func_sketch/common_types.h"

namespace func_sketch::math {

/*!
 * \brief Compute power for number types in this library.
 *
 * \tparam Base Type of base.
 * \tparam Exponent Type of exponent.
 * \param [in] base Base.
 * \param [in] exponent Exponent.
 * \return Result.
 */
template <typename Base, typename Exponent>
[[nodiscard]] inline auto pow_number(Base base, Exponent exponent) {
    return std::pow(base, exponent);
}

/*!
 * \brief Compute power for number types in this library.
 *
 * \tparam Exponent Type of exponent.
 * \param [in] base Base.
 * \param [in] exponent Exponent.
 * \return Result.
 */
template <typename Exponent>
[[nodiscard]] inline auto pow_number(Integer base, Exponent exponent) {
    return std::pow(static_cast<Real>(base), exponent);
}

/*!
 * \brief Compute power for number types in this library.
 *
 * \tparam Base Type of base.
 * \param [in] base Base.
 * \param [in] exponent Exponent.
 * \return Result.
 */
template <typename Base>
[[nodiscard]] inline auto pow_number(Base base, Integer exponent) {
    return std::pow(base, static_cast<Real>(exponent));
}

/*!
 * \brief Compute power for number types in this library.
 *
 * \param [in] base Base.
 * \param [in] exponent Exponent.
 * \return Result.
 */
inline auto pow_number(Integer base, Integer exponent) {
    return std::pow(static_cast<Real>(base), static_cast<Real>(exponent));
}

}  // namespace func_sketch::math
