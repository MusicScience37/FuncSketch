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
 * \brief Test of CommonType type.
 */
#include "func_sketch/math/common_type.h"

#include <type_traits>

#include <catch2/catch_test_macros.hpp>

#include "func_sketch/common_types.h"

TEST_CASE("func_sketch::math::CommonType") {
    using func_sketch::Complex;
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::CommonType;

    SECTION("get common types") {
        // Check all cases because number types in this project are limited.
        STATIC_REQUIRE(std::is_same_v<CommonType<Integer, Integer>, Integer>);
        STATIC_REQUIRE(std::is_same_v<CommonType<Integer, Real>, Real>);
        STATIC_REQUIRE(std::is_same_v<CommonType<Integer, Complex>, Complex>);
        STATIC_REQUIRE(std::is_same_v<CommonType<Real, Integer>, Real>);
        STATIC_REQUIRE(std::is_same_v<CommonType<Real, Real>, Real>);
        STATIC_REQUIRE(std::is_same_v<CommonType<Real, Complex>, Complex>);
        STATIC_REQUIRE(std::is_same_v<CommonType<Complex, Integer>, Complex>);
        STATIC_REQUIRE(std::is_same_v<CommonType<Complex, Real>, Complex>);
        STATIC_REQUIRE(std::is_same_v<CommonType<Complex, Complex>, Complex>);
    }
}
