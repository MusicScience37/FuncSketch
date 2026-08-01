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
 * \brief Implementation of ExpressionParser class.
 */
#include "func_sketch/parser/expression_parser.h"

#include <memory>

#include <boost/variant.hpp>

#include "func_sketch/parser/convert_expression.h"
#include "func_sketch/parser/expression_grammar.h"
#include "func_sketch/parser/parsed_expression.h"

namespace func_sketch::parser {

struct ExpressionParser::Impl {
    //! Grammar for parsing expressions.
    ExpressionGrammar grammar;
};

ExpressionParser::ExpressionParser() : pimpl_(std::make_unique<Impl>()) {}

ExpressionParser::~ExpressionParser() = default;

expressions::ExpressionPtr ExpressionParser::operator()(
    const std::string& expression_str) const {
    ParsedExpression parsed_expression;
    auto iter = expression_str.begin();
    bool is_parsed = boost::spirit::qi::phrase_parse(iter, expression_str.end(),
        pimpl_->grammar, boost::spirit::ascii::space, parsed_expression);
    if (!is_parsed || iter != expression_str.end()) {
        throw std::runtime_error(
            "Failed to parse expression: " + expression_str);
    }
    return convert_expression(parsed_expression);
}

}  // namespace func_sketch::parser
