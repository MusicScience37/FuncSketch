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

#include "func_sketch/parser/parsed_expression.h"

BOOST_FUSION_ADAPT_STRUCT(
    func_sketch::parser::ParsedConstant, (func_sketch::Scalar, value))
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
    : ExpressionGrammar::base_type(sum_expr_rule_) {
    using boost::phoenix::at_c;
    using boost::phoenix::bind;
    using boost::spirit::qi::alpha;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::digit;
    using boost::spirit::qi::double_;
    using boost::spirit::qi::lexeme;
    using boost::spirit::qi::labels::_1;
    using boost::spirit::qi::labels::_a;
    using boost::spirit::qi::labels::_val;

    constant_rule_ = double_;

    identifier_rule_ = lexeme[(alpha | char_('_'))[at_c<0>(_val) += _1] >>
        *(alpha | char_('_') | digit)[at_c<0>(_val) += _1]];

    function_call_expr_rule_ = identifier_rule_ >> '(' >> sum_expr_rule_ >>
        *(',' >> sum_expr_rule_) >> ')';

    atomic_value_expr_rule_ =
        function_call_expr_rule_ | constant_rule_ | identifier_rule_;

    value_expr_rule_ = atomic_value_expr_rule_ | '(' >> sum_expr_rule_ >> ')';

    const auto handle_power = [](ParsedExpression& left,
                                  const ParsedExpression& right) {
        left = ParsedBinaryExpression{
            .operator_str = "**", .left_operand = left, .right_operand = right};
    };
    factor_expr_rule_ = value_expr_rule_[_val = _1] >>
        *("**" >> value_expr_rule_[bind(handle_power, _val, _1)]);

    const auto handle_unary_minus = [](ParsedExpression& result,
                                        const ParsedExpression& operand) {
        result = ParsedUnaryExpression{.operator_str = "-", .operand = operand};
    };
    unary_expr_rule_ =
        ('-' >> factor_expr_rule_[bind(handle_unary_minus, _val, _1)]) |
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
    term_expr_rule_ = unary_expr_rule_[_val = _1] >>
        *('*' >> unary_expr_rule_[bind(handle_multiplication, _val, _1)] |
            '/' >> unary_expr_rule_[bind(handle_division, _val, _1)]);

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
    sum_expr_rule_ = term_expr_rule_[_val = _1] >>
        *('+' >> term_expr_rule_[bind(handle_addition, _val, _1)] |
            '-' >> term_expr_rule_[bind(handle_subtraction, _val, _1)]);
}

}  // namespace func_sketch::parser
