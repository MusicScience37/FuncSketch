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
 * \brief Test of MathOperationList class.
 */
#include "func_sketch/expressions/math_operation_list.h"

#include <catch2/catch_test_macros.hpp>

#include "func_sketch/expressions/operations/integration_operation.h"

TEST_CASE("func_sketch::expressions::MathOperationList") {
    using func_sketch::expressions::integration_operation;
    using func_sketch::expressions::MathOperationList;

    SECTION("append and get an operation") {
        MathOperationList list;
        list.emplace(integration_operation());

        const auto operation = list.get("integrate");
        REQUIRE(operation.has_value());

        CHECK(operation->info().name() == "integrate");
    }

    SECTION("get an operation that does not exist") {
        MathOperationList list;

        const auto operation = list.get("integrate");
        CHECK(!operation.has_value());
    }
}
