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
 * \brief Definition of BinaryOperator class.
 */
#pragma once

#include <string_view>
#include <utility>

#include "func_sketch/common_types.h"
#include "func_sketch/math/binary_operator_type.h"
#include "func_sketch/utilities/any.h"

namespace func_sketch::math {

/*!
 * \brief Class of binary operators.
 */
class BinaryOperator {
public:
    /*!
     * \brief Constructor.
     *
     * \tparam T Type of the operator object.
     * \param[in] operator_object Operator object.
     */
    template <BinaryOperatorType T>
    explicit BinaryOperator(T operator_object)
        : operator_(std::move(operator_object)),
          get_name_([](const utilities::Any& obj) -> std::string_view {
              return obj.get<T>().name();
          }),
          scalar_operator_(
              [](const utilities::Any& obj, const Real& left, const Real& right,
                  Real& result) { obj.get<T>()(left, right, result); }) {}

    /*!
     * \brief Get the name of the operator.
     *
     * \return Name of the operator.
     */
    [[nodiscard]] std::string_view name() const { return get_name_(operator_); }

    /*!
     * \brief Operate on a pair of scalars.
     *
     * \param[in] left Left scalar.
     * \param[in] right Right scalar.
     * \param[out] result Result scalar.
     */
    void operator()(const Real& left, const Real& right, Real& result) const {
        scalar_operator_(operator_, left, right, result);
    }

private:
    //! Signature of function to get the name of the operator.
    using GetNameSignature = std::string_view(
        const utilities::Any& /*operator_object*/);

    //! Signature of function to operate on a pair of scalars.
    using ScalarOperatorSignature = void(
        const utilities::Any& /*operator_object*/, const Real& /*left*/,
        const Real& /*right*/, Real& /*result*/);

    //! Operator object.
    utilities::Any operator_;

    //! Function to get the name of the operator.
    GetNameSignature* get_name_;

    //! Function to operate on a pair of scalars.
    ScalarOperatorSignature* scalar_operator_;
};

}  // namespace func_sketch::math
