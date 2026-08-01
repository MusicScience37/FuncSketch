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
 * \brief Test of ExpressionGrammar class.
 */
#include "func_sketch/parser/expression_grammar.h"

#include <iterator>

#include <catch2/catch_test_macros.hpp>
#include <fmt/base.h>
#include <fmt/format.h>

#include "include_approval_tests.h"
#include "parser_test_strings.h"

TEST_CASE("func_sketch::parser::ExpressionGrammar") {
    using func_sketch::parser::ExpressionGrammar;
    using func_sketch::parser::ParsedExpression;

    SECTION("parse") {
        ExpressionGrammar grammar;
        fmt::memory_buffer results;
        for (const auto& str : parser_test_strings()) {
            fmt::format_to(std::back_inserter(results), "Input: {}\n", str);
            try {
                ParsedExpression parsed_expression;
                auto iter = str.begin();
                bool is_parsed =
                    boost::spirit::qi::phrase_parse(iter, str.end(), grammar,
                        boost::spirit::ascii::space, parsed_expression);

                CHECK(is_parsed);
                CHECK(iter == str.end());

                fmt::format_to(std::back_inserter(results), "Parsed: {}\n",
                    parsed_expression);
            } catch (const std::exception& e) {
                fmt::format_to(
                    std::back_inserter(results), "Exception: {}\n", e.what());
            }
            results.push_back('\n');
        }

        ApprovalTests::Approvals::verify(
            std::string(results.data(), results.size()));
    }
}
