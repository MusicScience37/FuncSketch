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
 * \brief Definition of UnaryOperator class.
 */
#pragma once

#include <string_view>
#include <utility>

#include "func_sketch/common_types.h"
#include "func_sketch/math/unary_operator_type.h"
#include "func_sketch/utilities/any.h"

namespace func_sketch::math {

/*!
 * \brief Class of unary operators.
 */
class UnaryOperator {
public:
    /*!
     * \brief Constructor.
     *
     * \tparam T Type of the operator object.
     * \param[in] operator_object Operator object.
     */
    template <UnaryOperatorType T>
    explicit UnaryOperator(T operator_object)
        : operator_(std::move(operator_object)),
          get_name_([](const utilities::Any& obj) -> std::string_view {
              return obj.get<T>().name();
          }),
          scalar_operator_([](const utilities::Any& obj, const Number& arg,
                               Number& result) { obj.get<T>()(arg, result); }) {
    }

    /*!
     * \brief Get the name of the operator.
     *
     * \return Name of the operator.
     */
    [[nodiscard]] std::string_view name() const { return get_name_(operator_); }

    /*!
     * \brief Operate on a scalar.
     *
     * \param[in] arg Argument.
     * \param[out] result Result.
     */
    void operator()(const Number& arg, Number& result) const {
        scalar_operator_(operator_, arg, result);
    }

private:
    //! Signature of function to get the name of the operator.
    using GetNameSignature = std::string_view(
        const utilities::Any& /*operator_object*/);

    //! Signature of function to operate on a scalar.
    using ScalarOperatorSignature = void(
        const utilities::Any& /*operator_object*/, const Number& /*arg*/,
        Number& /*result*/);

    //! Operator object.
    utilities::Any operator_;

    //! Function to get the name of the operator.
    GetNameSignature* get_name_;

    //! Function to operate on a scalar.
    ScalarOperatorSignature* scalar_operator_;
};

}  // namespace func_sketch::math
