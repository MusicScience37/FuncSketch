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
 * \brief Definition of ExpressionEvaluator class.
 */
#pragma once

#include "func_sketch/common_types.h"
#include "func_sketch/expressions/expression.h"
#include "func_sketch/expressions/parameter_expression.h"
#include "func_sketch/expressions/parameter_value_dict.h"

namespace func_sketch::expressions {

/*!
 * \brief Class to evaluate expressions.
 */
class ExpressionEvaluator {
public:
    /*!
     * \brief Evaluate an expression.
     *
     * \param[in] expression Expression.
     * \param[in] parameters Values of parameters.
     * \param[out] result Result.
     */
    static void operator()(const Expression& expression,
        const ParameterValueDict& parameters, Real& result);

    /*!
     * \brief Evaluate an expression.
     *
     * \param[in] expression Expression.
     * \param[in] parameters Values of parameters.
     * \param[out] result Result.
     */
    static void operator()(const Expression& expression,
        const ParameterValueDict& parameters, Number& result);

private:
    /*!
     * \brief Evaluate an expression.
     *
     * \param[in] expression Expression.
     * \param[in] parameters Values of parameters.
     * \param[out] result Result.
     */
    static void evaluate(const Expression& expression,
        const ParameterValueDict& parameters, Number& result);

    /*!
     * \brief Evaluate an expression.
     *
     * \param[in] expression Expression.
     * \param[out] result Result.
     */
    static void evaluate(const ConstantExpression& expression,
        const ParameterValueDict& /*parameters*/, Number& result);

    /*!
     * \brief Evaluate an expression.
     *
     * \param[in] expression Expression.
     * \param[in] parameters Values of parameters.
     * \param[out] result Result.
     */
    static void evaluate(const ParameterExpression& expression,
        const ParameterValueDict& parameters, Number& result);

    /*!
     * \brief Evaluate an expression.
     *
     * \param[in] expression Expression.
     * \param[in] parameters Values of parameters.
     * \param[out] result Result.
     */
    static void evaluate(const UnaryExpression& expression,
        const ParameterValueDict& parameters, Number& result);

    /*!
     * \brief Evaluate an expression.
     *
     * \param[in] expression Expression.
     * \param[in] parameters Values of parameters.
     * \param[out] result Result.
     */
    static void evaluate(const BinaryExpression& expression,
        const ParameterValueDict& parameters, Number& result);

    /*!
     * \brief Evaluate an expression.
     *
     * \param[in] expression Expression.
     * \param[in] parameters Values of parameters.
     * \param[out] result Result.
     */
    static void evaluate(const FunctionCallExpression& expression,
        const ParameterValueDict& parameters, Number& result);
};

}  // namespace func_sketch::expressions
