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
 * \brief Test of IntegrationOperation class.
 */
#include "func_sketch/expressions/operations/integration_operation.h"

#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/expressions/expression.h"
#include "func_sketch/expressions/expression_evaluator.h"
#include "func_sketch/expressions/parameter_value_dict.h"
#include "func_sketch/math/functions/python_function_list.h"
#include "func_sketch/parameter_type.h"
#include "func_sketch/parser/expression_parser.h"

TEST_CASE("func_sketch::expressions::IntegrationOperation") {
    using func_sketch::Number;
    using func_sketch::ParameterType;
    using func_sketch::Real;
    using func_sketch::expressions::Expression;
    using func_sketch::expressions::integration_operation;
    using func_sketch::expressions::ParameterValueDict;
    using func_sketch::math::PythonFunctionList;
    using func_sketch::parser::ExpressionParser;

    const auto operation_object = integration_operation();
    ExpressionParser parser{PythonFunctionList{}};
    func_sketch::expressions::ExpressionEvaluator evaluator;

    SECTION("get information") {
        const auto& info = operation_object.info();

        CHECK(info.name() == "integrate");
        CHECK(info.argument_names() ==
            std::vector<std::string>{"function", "left", "right"});
    }

    SECTION("integrate a function") {
        const auto function_expression = parser("s");
        const auto left_expression = parser("0");
        const auto right_expression = parser("x");
        const auto args =
            std::vector<const Expression*>{function_expression.get(),
                left_expression.get(), right_expression.get()};

        ParameterValueDict parameters;
        parameters[ParameterType::x] = 1.0;
        Number result;
        REQUIRE_NOTHROW(operation_object(args, evaluator, parameters, result));

        CHECK_THAT(std::get<Real>(result), Catch::Matchers::WithinRel(0.5));
    }

    SECTION("try to integrate with wrong number of arguments") {
        const auto function_expression = parser("s");
        const auto left_expression = parser("0");
        const auto args = std::vector<const Expression*>{
            function_expression.get(), left_expression.get()};

        ParameterValueDict parameters;
        Number result;
        CHECK_THROWS_WITH(operation_object(args, evaluator, parameters, result),
            Catch::Matchers::ContainsSubstring(
                "integrate function requires exactly 3 arguments"));
    }

    SECTION("try to integrate with a complex left endpoint") {
        const auto function_expression = parser("s");
        const auto left_expression = parser("i");
        const auto right_expression = parser("1");
        const auto args =
            std::vector<const Expression*>{function_expression.get(),
                left_expression.get(), right_expression.get()};

        ParameterValueDict parameters;
        Number result;
        CHECK_THROWS_WITH(operation_object(args, evaluator, parameters, result),
            Catch::Matchers::ContainsSubstring(
                "A left endpoint of an integration is not a real number"));
    }

    SECTION("try to integrate with a complex right endpoint") {
        const auto function_expression = parser("s");
        const auto left_expression = parser("0");
        const auto right_expression = parser("i");
        const auto args =
            std::vector<const Expression*>{function_expression.get(),
                left_expression.get(), right_expression.get()};

        ParameterValueDict parameters;
        Number result;
        CHECK_THROWS_WITH(operation_object(args, evaluator, parameters, result),
            Catch::Matchers::ContainsSubstring(
                "A right endpoint of an integration is not a real number"));
    }
}
