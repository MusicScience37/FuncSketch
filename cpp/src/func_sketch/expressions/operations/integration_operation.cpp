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
 * \brief Implementation of IntegrationOperation class.
 */
#include "func_sketch/expressions/operations/integration_operation.h"

#include <span>
#include <type_traits>
#include <variant>

#include "func_sketch/common_types.h"
#include "func_sketch/exceptions.h"
#include "func_sketch/expressions/expression.h"
#include "func_sketch/expressions/expression_decl.h"
#include "func_sketch/expressions/expression_evaluator.h"
#include "func_sketch/expressions/expression_evaluator_decl.h"
#include "func_sketch/expressions/math_operation_info.h"
#include "func_sketch/expressions/parameter_value_dict.h"
#include "func_sketch/math/operations/numerical_integrator.h"
#include "func_sketch/parameter_type.h"

namespace func_sketch::expressions {

/*!
 * \brief Class of the operation of numerical integration.
 */
class IntegrationOperation {
public:
    /*!
     * \brief Constructor.
     */
    IntegrationOperation()
        : info_("integrate", {"function", "left", "right"}) {}

    /*!
     * \brief Get the information about the mathematical operation.
     *
     * \return Information about the mathematical operation.
     */
    [[nodiscard]] const MathOperationInfo& info() const noexcept {
        return info_;
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
        if (args.size() != 3) {
            throw InvalidExpressionException(fmt::format(
                "integrate function requires exactly 3 arguments. Actual: {}.",
                args.size()));
        }

        Number left_as_number;
        evaluator(*args[1], parameters, left_as_number);
        Number right_as_number;
        evaluator(*args[2], parameters, right_as_number);

        const Real left = std::visit(
            [](const auto& value) -> Real {
                using ValueType = std::decay_t<decltype(value)>;
                if constexpr (std::is_same_v<ValueType, Complex>) {
                    throw InvalidExpressionException(
                        "A left endpoint of an integration is not a real "
                        "number.");
                } else {
                    return static_cast<Real>(value);
                }
            },
            left_as_number);
        const Real right = std::visit(
            [](const auto& value) -> Real {
                using ValueType = std::decay_t<decltype(value)>;
                if constexpr (std::is_same_v<ValueType, Complex>) {
                    throw InvalidExpressionException(
                        "A right endpoint of an integration is not a real "
                        "number.");
                } else {
                    return static_cast<Real>(value);
                }
            },
            right_as_number);

        ParameterValueDict parameters_of_expression = parameters;
        result = integrator_(
            [expression = args[0], &evaluator, &parameters_of_expression](
                Real arg) {
                parameters_of_expression[ParameterType::s] = arg;
                Number value;
                evaluator(*expression, parameters_of_expression, value);
                return value;
            },
            left, right);
    }

private:
    //! Information about this mathematical operation.
    MathOperationInfo info_;

    //! Integrator.
    math::NumericalIntegrator integrator_;
};

MathOperation integration_operation() {
    return MathOperation(IntegrationOperation());
}

}  // namespace func_sketch::expressions
