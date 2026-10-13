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
 * \brief Definition of ParameterType enum.
 */
#pragma once

#include <cstdint>

namespace func_sketch {

/*!
 * \brief Type of parameters.
 */
enum class ParameterType : std::uint8_t {
    //! Parameter "x".
    x,

    //! Parameter "t".
    t,
};

}  // namespace func_sketch
