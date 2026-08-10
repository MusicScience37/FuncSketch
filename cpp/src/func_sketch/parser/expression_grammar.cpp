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
 * \brief Implementation of ExpressionGrammar class.
 */
#include "func_sketch/parser/expression_grammar.h"

#include <boost/bind.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/phoenix/bind.hpp>
#include <boost/phoenix/fusion/at.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include "func_sketch/exceptions.h"
#include "func_sketch/parser/parsed_expression.h"

BOOST_FUSION_ADAPT_STRUCT(
    func_sketch::parser::ParsedConstant, (func_sketch::Number, value))
BOOST_FUSION_ADAPT_STRUCT(
    func_sketch::parser::ParsedIdentifier, (std::string, name))
BOOST_FUSION_ADAPT_STRUCT(func_sketch::parser::ParsedFunctionCallExpression,
    (func_sketch::parser::ParsedIdentifier, function_name)(
        std::vector<func_sketch::parser::ParsedExpression>, arguments))
BOOST_FUSION_ADAPT_STRUCT(func_sketch::parser::ParsedUnaryExpression,
    (std::string, operator_str)(func_sketch::parser::ParsedExpression, operand))
BOOST_FUSION_ADAPT_STRUCT(func_sketch::parser::ParsedBinaryExpression,
    (std::string, operator_str)(func_sketch::parser::ParsedExpression,
        left_operand)(func_sketch::parser::ParsedExpression, right_operand))

namespace func_sketch::parser {

ExpressionGrammar::ExpressionGrammar()
    : ExpressionGrammar::base_type(expr_rule_) {
    using boost::phoenix::at_c;
    using boost::phoenix::bind;
    using boost::phoenix::push_back;
    using boost::spirit::qi::alpha;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::digit;
    using boost::spirit::qi::double_;
    using boost::spirit::qi::fail;
    using boost::spirit::qi::int_;
    using boost::spirit::qi::lexeme;
    using boost::spirit::qi::on_error;
    using boost::spirit::qi::real_parser;
    using boost::spirit::qi::strict_real_policies;
    using boost::spirit::qi::labels::_1;
    using boost::spirit::qi::labels::_2;
    using boost::spirit::qi::labels::_3;
    using boost::spirit::qi::labels::_4;
    using boost::spirit::qi::labels::_a;
    using boost::spirit::qi::labels::_val;

    // NOLINTBEGIN(bugprone-chained-comparison): This is a grammar definition, so the code is not a chained comparison.
#if defined(__clang__)
#pragma clang diagnostic ignored "-Woverloaded-shift-op-parentheses"
#endif

    // Almost all rules are defined using expectation (>).
    // Only function call expression rule has (>>) to allow parsing both
    // "exp(1.23)" (function call expression) and "x" (identifier only).

    const real_parser<double, strict_real_policies<double>> strict_double;
    constant_rule_ =
        strict_double[at_c<0>(_val) = _1] | int_[at_c<0>(_val) = _1];

    identifier_rule_ = lexeme[(alpha | char_('_'))[at_c<0>(_val) += _1] >
        *(alpha | char_('_') | digit)[at_c<0>(_val) += _1]];

    function_call_expr_rule_ = identifier_rule_[at_c<0>(_val) = _1] >> '(' >
        -(sum_expr_rule_[push_back(at_c<1>(_val), _1)] >
            *(',' > sum_expr_rule_[push_back(at_c<1>(_val), _1)])) > ')';

    atomic_value_expr_rule_ =
        function_call_expr_rule_ | constant_rule_ | identifier_rule_;

    value_expr_rule_ = atomic_value_expr_rule_ | '(' > sum_expr_rule_ > ')';

    const auto handle_power = [](ParsedExpression& left,
                                  const ParsedExpression& right) {
        left = ParsedBinaryExpression{
            .operator_str = "**", .left_operand = left, .right_operand = right};
    };
    factor_expr_rule_ = value_expr_rule_[_val = _1] >
        -("**" > factor_expr_rule_[bind(handle_power, _val, _1)]);

    const auto handle_unary_minus = [](ParsedExpression& result,
                                        const ParsedExpression& operand) {
        result = ParsedUnaryExpression{.operator_str = "-", .operand = operand};
    };
    unary_expr_rule_ =
        ('-' > factor_expr_rule_[bind(handle_unary_minus, _val, _1)]) |
        factor_expr_rule_[_val = _1];

    const auto handle_multiplication = [](ParsedExpression& left,
                                           const ParsedExpression& right) {
        left = ParsedBinaryExpression{
            .operator_str = "*", .left_operand = left, .right_operand = right};
    };
    const auto handle_division = [](ParsedExpression& left,
                                     const ParsedExpression& right) {
        left = ParsedBinaryExpression{
            .operator_str = "/", .left_operand = left, .right_operand = right};
    };
    term_expr_rule_ = unary_expr_rule_[_val = _1] >
        *('*' > unary_expr_rule_[bind(handle_multiplication, _val, _1)] |
            '/' > unary_expr_rule_[bind(handle_division, _val, _1)]);

    const auto handle_addition = [](ParsedExpression& left,
                                     const ParsedExpression& right) {
        left = ParsedBinaryExpression{
            .operator_str = "+", .left_operand = left, .right_operand = right};
    };
    const auto handle_subtraction = [](ParsedExpression& left,
                                        const ParsedExpression& right) {
        left = ParsedBinaryExpression{
            .operator_str = "-", .left_operand = left, .right_operand = right};
    };
    sum_expr_rule_ = term_expr_rule_[_val = _1] >
        *('+' > term_expr_rule_[bind(handle_addition, _val, _1)] |
            '-' > term_expr_rule_[bind(handle_subtraction, _val, _1)]);

    expr_rule_ = sum_expr_rule_[_val = _1];

    // NOLINTEND(bugprone-chained-comparison)

    constant_rule_.name("constant");
    identifier_rule_.name("identifier");
    // For error messages, we want to show all expressions as "expression"
    // instead of actual rule names, since almost users will not know about
    // those rules.
    function_call_expr_rule_.name("expression");
    atomic_value_expr_rule_.name("expression");
    value_expr_rule_.name("expression");
    factor_expr_rule_.name("expression");
    unary_expr_rule_.name("expression");
    term_expr_rule_.name("expression");
    sum_expr_rule_.name("expression");
    expr_rule_.name("expression");

    const auto handle_error = [this](const auto& first, const auto& /*last*/,
                                  const auto& error_pos, const auto& what) {
        error_message_ = fmt::format("Expected {} at position {}.",
            fmt::streamed(what), std::distance(first, error_pos));
    };
    on_error<fail>(expr_rule_, bind(handle_error, _1, _2, _3, _4));
}

const std::string& ExpressionGrammar::error_message() const noexcept {
    return error_message_;
}

void ExpressionGrammar::clear_error_message() noexcept {
    error_message_.clear();
}

ParsedExpression ExpressionGrammar::parse(const std::string& str) {
    ParsedExpression parsed_expression;
    auto iter = str.begin();
    clear_error_message();
    bool is_parsed = boost::spirit::qi::phrase_parse(
        iter, str.end(), *this, boost::spirit::ascii::space, parsed_expression);
    if (!is_parsed || iter != str.end()) {
        const auto& error_message = this->error_message();
        if (!error_message.empty()) {
            throw InvalidExpressionException(error_message);
        }
        if (iter != str.end()) {
            throw InvalidExpressionException(
                fmt::format("Unexpected token at position {}.",
                    // Output in 1-based index.
                    std::distance(str.begin(), iter) + 1));
        }
        throw InvalidExpressionException("Failed to parse expression.");
    }
    return parsed_expression;
}

}  // namespace func_sketch::parser
