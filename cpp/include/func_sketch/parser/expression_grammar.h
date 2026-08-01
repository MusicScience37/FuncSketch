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
 * \brief Definition of ExpressionGrammar class.
 */
#pragma once

#include <string>

#include <boost/phoenix.hpp>
#include <boost/spirit/home/qi.hpp>

#include "func_sketch/parser/parsed_expression.h"

namespace func_sketch::parser {

/*!
 * \brief Class of grammar for parsing expressions.
 */
class ExpressionGrammar
    : public boost::spirit::qi::grammar<std::string::const_iterator,
          ParsedExpression(), boost::spirit::ascii::space_type> {
public:
    //! Type of iterator.
    using IteratorType = std::string::const_iterator;

    /*!
     * \brief Constructor.
     */
    ExpressionGrammar();

private:
    /*!
     * \brief Type of rules.
     *
     * \tparam T Type of the value of the rule.
     */
    template <typename T>
    using Rule = boost::spirit::qi::rule<IteratorType, T(),
        boost::spirit::ascii::space_type>;

    //! Rule of constants.
    Rule<ParsedConstant> constant_rule_;

    //! Rule of identifiers.
    Rule<ParsedIdentifier> identifier_rule_;

    //! Rule of function call expressions.
    Rule<ParsedFunctionCallExpression> function_call_expr_rule_;

    //! Rule of atomic value expressions.
    Rule<ParsedExpression> atomic_value_expr_rule_;

    //! Rule of value expressions.
    Rule<ParsedExpression> value_expr_rule_;

    //! Rule of factor expressions.
    Rule<ParsedExpression> factor_expr_rule_;

    //! Rule of unary expressions.
    Rule<ParsedExpression> unary_expr_rule_;

    //! Rule of term expressions.
    Rule<ParsedExpression> term_expr_rule_;

    //! Rule of sum expressions.
    Rule<ParsedExpression> sum_expr_rule_;
};

}  // namespace func_sketch::parser
