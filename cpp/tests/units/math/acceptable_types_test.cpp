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
 * \brief Test of AcceptableTypes struct.
 */
#include "func_sketch/math/acceptable_types.h"

#include <type_traits>

#include <catch2/catch_test_macros.hpp>

#include "func_sketch/common_types.h"

TEST_CASE("func_sketch::math::details::SelectTypeToUseImpl") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::NoAcceptableType;
    using func_sketch::math::details::SelectTypeToUseImpl;

    SECTION("select types") {
        // Acceptable cases.
        STATIC_REQUIRE(
            std::is_same_v<SelectTypeToUseImpl<Integer, Integer>::Type,
                Integer>);
        STATIC_REQUIRE(
            std::is_same_v<SelectTypeToUseImpl<Integer, Integer, Real>::Type,
                Integer>);
        STATIC_REQUIRE(
            std::is_same_v<SelectTypeToUseImpl<Integer, Real>::Type, Real>);

        // Non-acceptable cases.
        STATIC_REQUIRE(std::is_same_v<SelectTypeToUseImpl<Real, Integer>::Type,
            NoAcceptableType>);
    }
}

TEST_CASE("func_sketch::math::AcceptableTypes") {
    using func_sketch::Integer;
    using func_sketch::Real;
    using func_sketch::math::AcceptableTypes;
    using func_sketch::math::NoAcceptableType;

    SECTION("get acceptable types") {
        // Acceptable cases.
        STATIC_REQUIRE(
            std::is_same_v<AcceptableTypes<Integer>::SelectTypeToUse<Integer>,
                Integer>);
        STATIC_REQUIRE(std::is_same_v<
            AcceptableTypes<Integer, Real>::SelectTypeToUse<Integer>, Integer>);
        STATIC_REQUIRE(
            std::is_same_v<AcceptableTypes<Real>::SelectTypeToUse<Integer>,
                Real>);

        // Non-acceptable cases.
        STATIC_REQUIRE(
            std::is_same_v<AcceptableTypes<Integer>::SelectTypeToUse<Real>,
                NoAcceptableType>);
    }
}
