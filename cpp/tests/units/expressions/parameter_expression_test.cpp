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
 * \brief Test of ParameterExpression structure.
 */
#include "func_sketch/expressions/parameter_expression.h"

#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>

TEST_CASE("ParameterExpression") {
    SECTION("format") {
        func_sketch::expressions::ParameterExpression expr;

        CHECK(fmt::format("{}", expr) == "x");
    }
}
