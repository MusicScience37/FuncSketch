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
 * \brief Definitions of common types.
 */
#pragma once

#include <complex>
#include <cstdint>
#include <variant>

namespace func_sketch {

//! Type of real numbers in this project.
using Real = double;

//! Type of integer numbers in this project.
using Integer = std::int32_t;

//! Type of complex numbers in this project.
using Complex = std::complex<Real>;

/*!
 * \brief Type of numbers.
 *
 * \note Integer is written before Real to avoid implicit conversion from
 * Integer to Real.
 */
using Number = std::variant<Integer, Real, Complex>;

}  // namespace func_sketch
