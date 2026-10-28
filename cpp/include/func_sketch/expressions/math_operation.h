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
 * \brief Definition of MathOperation class.
 */
#pragma once

#include <span>

#include "func_sketch/common_types.h"
#include "func_sketch/expressions/expression_decl.h"
#include "func_sketch/expressions/expression_evaluator_decl.h"
#include "func_sketch/expressions/math_operation_info.h"
#include "func_sketch/expressions/parameter_value_dict.h"
#include "func_sketch/utilities/any.h"

namespace func_sketch::expressions {

/*!
 * \brief Class of mathematical operations.
 */
class MathOperation {
public:
    /*!
     * \brief Constructor.
     *
     * \tparam T Type of the operation object.
     * \param[in] operation Operation object.
     */
    template <typename T>
    explicit MathOperation(T operation)
        : operation_(std::move(operation)),
          get_info_([](const utilities::Any& obj) -> const MathOperationInfo& {
              return obj.get<T>().info();
          }),
          evaluate_([](const utilities::Any& obj,
                        std::span<const Expression* const> args,
                        const ExpressionEvaluator& evaluator,
                        const ParameterValueDict& parameters, Number& result) {
              obj.get<T>()(args, evaluator, parameters, result);
          }) {}

    /*!
     * \brief Get the information about the mathematical operation.
     *
     * \return Information about the mathematical operation.
     */
    [[nodiscard]] const MathOperationInfo& info() const noexcept {
        return get_info_(operation_);
    }

    /*!
     * \brief Evaluate a numerical integral.
     *
     * \param[in] args Arguments of the operation.
     * \param[in] evaluator Expression evaluator.
     * \param[in] parameters Parameter values.
     * \param[out] result Result of the integration.
     */
    void operator()(std::span<const Expression* const> args,
        const ExpressionEvaluator& evaluator,
        const ParameterValueDict& parameters, Number& result) const {
        evaluate_(operation_, args, evaluator, parameters, result);
    }

private:
    //! Signature of the function to get the information about the operation.
    using GetInfoSignature = const MathOperationInfo&(
        const utilities::Any& /*operation_object*/);

    //! Signature of the function to evaluate the operation.
    using EvaluateSignature = void(const utilities::Any& /*operation_object*/,
        std::span<const Expression* const> /*args*/,
        const ExpressionEvaluator& /*evaluator*/,
        const ParameterValueDict& /*parameters*/, Number& /*result*/);

    //! Operation object.
    utilities::Any operation_;

    //! Function to get the information about the operation.
    GetInfoSignature* get_info_;

    //! Function to evaluate the operation.
    EvaluateSignature* evaluate_;
};

}  // namespace func_sketch::expressions
