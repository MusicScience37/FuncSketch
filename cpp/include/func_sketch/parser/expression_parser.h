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
 * \brief Definition of ExpressionParser class.
 */
#pragma once

#include <memory>
#include <string>

#include "func_sketch/expressions/expression_ptr.h"
#include "func_sketch/math/functions/python_function_list.h"

namespace func_sketch::parser {

/*!
 * \brief Class of parser for expressions.
 */
class ExpressionParser {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] python_functions List of Python functions.
     */
    explicit ExpressionParser(const math::PythonFunctionList& python_functions);

    ExpressionParser(const ExpressionParser&) = delete;
    ExpressionParser& operator=(const ExpressionParser&) = delete;

    /*!
     * \brief Move constructor.
     */
    ExpressionParser(ExpressionParser&& /*other*/) noexcept;

    /*!
     * \brief Move assignment operator.
     *
     * \return This object.
     */
    ExpressionParser& operator=(ExpressionParser&& /*other*/) noexcept;

    /*!
     * \brief Destructor.
     */
    ~ExpressionParser();

    /*!
     * \brief Parse an expression.
     *
     * \param[in] expression_str String to parse.
     * \return Parsed expression.
     */
    [[nodiscard]] expressions::ExpressionPtr operator()(
        const std::string& expression_str) const;

private:
    // Separate implementation to avoid including Boost.Spirit headers in this
    // header file for faster compilation.

    //! Struct of the internal data.
    struct Impl;

    //! Internal data.
    std::unique_ptr<Impl> pimpl_;
};

}  // namespace func_sketch::parser
