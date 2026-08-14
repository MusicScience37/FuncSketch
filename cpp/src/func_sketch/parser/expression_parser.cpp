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

#include "func_sketch/math/generate_math_function_list.h"
#include "func_sketch/math/math_function_list.h"
#include "func_sketch/parser/convert_expression.h"
#include "func_sketch/parser/expression_grammar.h"

namespace func_sketch::parser {

//! Internal data of ExpressionParser class.
struct ExpressionParser::Impl {
    //! Grammar for parsing expressions.
    ExpressionGrammar grammar;

    //! List of mathematical functions.
    math::MathFunctionList math_function_list;

    //! List of constants.
    math::ConstantList constant_list{math::generate_constant_list()};

    /*!
     * \brief Constructor.
     *
     * \param[in] python_functions List of Python functions.
     */
    explicit Impl(const math::PythonFunctionList& python_functions)
        : math_function_list{
              math::generate_math_function_list(python_functions)} {}
};

ExpressionParser::ExpressionParser(
    const math::PythonFunctionList& python_functions)
    : pimpl_(std::make_unique<Impl>(python_functions)) {}

ExpressionParser::ExpressionParser(
    ExpressionParser&& /*other*/) noexcept = default;

ExpressionParser& ExpressionParser::operator=(
    ExpressionParser&& /*other*/) noexcept = default;

ExpressionParser::~ExpressionParser() = default;

expressions::ExpressionPtr ExpressionParser::operator()(
    const std::string& expression_str) const {
    const auto parsed_expression = pimpl_->grammar.parse(expression_str);
    return convert_expression(
        parsed_expression, pimpl_->math_function_list, pimpl_->constant_list);
}

}  // namespace func_sketch::parser
