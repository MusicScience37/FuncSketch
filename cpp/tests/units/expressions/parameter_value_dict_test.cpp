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
 * \brief Test of ParameterValueDict class.
 */
#include "func_sketch/expressions/parameter_value_dict.h"

#include <cstdint>
#include <variant>

#include <catch2/catch_test_macros.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/exceptions.h"
#include "func_sketch/expressions/parameter_expression.h"

TEST_CASE("func_sketch::expressions::ParameterValueDict") {
    using func_sketch::InvalidArgumentException;
    using func_sketch::Real;
    using func_sketch::expressions::ParameterType;
    using func_sketch::expressions::ParameterValueDict;

    SECTION("no value after construction") {
        const ParameterValueDict parameters;

        CHECK_FALSE(parameters[ParameterType::x].has_value());
        CHECK_FALSE(parameters[ParameterType::t].has_value());
    }

    SECTION("set values") {
        ParameterValueDict parameters;
        constexpr Real x_value = 1.23;
        constexpr Real t_value = 4.56;

        parameters[ParameterType::x] = x_value;
        parameters[ParameterType::t] = t_value;

        const auto& const_parameters = parameters;
        REQUIRE(const_parameters[ParameterType::x].has_value());
        CHECK(std::get<Real>(*const_parameters[ParameterType::x]) == x_value);
        REQUIRE(const_parameters[ParameterType::t].has_value());
        CHECK(std::get<Real>(*const_parameters[ParameterType::t]) == t_value);
    }

    SECTION("set a value of only one parameter") {
        ParameterValueDict parameters;
        constexpr Real t_value = 4.56;

        parameters[ParameterType::t] = t_value;

        const auto& const_parameters = parameters;
        CHECK_FALSE(const_parameters[ParameterType::x].has_value());
        REQUIRE(const_parameters[ParameterType::t].has_value());
        CHECK(std::get<Real>(*const_parameters[ParameterType::t]) == t_value);
    }

    SECTION("number of parameter types") {
        // Check that the size of the internal array matches the number of
        // elements in ParameterType.
        ParameterValueDict parameters;
        const auto& const_parameters = parameters;
        constexpr auto last_type = ParameterType::t;
        // NOLINTNEXTLINE(clang-analyzer-optin.core.EnumCastOutOfRange)
        const auto invalid_type = static_cast<ParameterType>(
            static_cast<std::uint8_t>(last_type) + 1U);

        CHECK_NOTHROW(parameters[last_type] = 1.0);
        CHECK_NOTHROW((void)const_parameters[last_type]);
        CHECK_THROWS_AS(parameters[invalid_type], InvalidArgumentException);
        CHECK_THROWS_AS(
            (void)const_parameters[invalid_type], InvalidArgumentException);
    }
}
