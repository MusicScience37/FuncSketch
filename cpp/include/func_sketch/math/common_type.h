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
 * \brief Definition of CommonType type.
 */
#pragma once

#include <type_traits>

namespace func_sketch::math {

/*!
 * \brief Get common type of two types.
 *
 * \note This type alias is written for use with number types in
 * \ref func_sketch::Number type. Although current implementation is just
 * std::common_type_t, this type alias can change in the future.
 */
template <typename T1, typename T2>
using CommonType = std::common_type_t<T1, T2>;

}  // namespace func_sketch::math
