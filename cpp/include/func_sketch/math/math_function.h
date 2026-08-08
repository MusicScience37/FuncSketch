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
 * \brief Definition of MathFunction class.
 */
#pragma once

#include <string_view>
#include <utility>
#include <vector>

#include "func_sketch/common_types.h"
#include "func_sketch/math/math_function_type.h"
#include "func_sketch/utilities/any.h"

namespace func_sketch::math {

/*!
 * \brief Class of mathematical functions.
 */
class MathFunction {
public:
    /*!
     * \brief Constructor.
     *
     * \tparam T Type of the function object.
     * \param[in] function Function object.
     */
    template <MathFunctionType T>
    explicit MathFunction(T function)
        : function_(std::move(function)),
          get_name_([](const utilities::Any& obj) -> std::string_view {
              return obj.get<T>().name();
          }),
          scalar_operator_(
              [](const utilities::Any& obj, const std::vector<Real>& args,
                  Real& result) { obj.get<T>()(args, result); }) {}

    /*!
     * \brief Get the name of the function.
     *
     * \return Name of the function.
     */
    [[nodiscard]] std::string_view name() const { return get_name_(function_); }

    /*!
     * \brief Operate on scalars.
     *
     * \param[in] args Arguments.
     * \param[out] result Result.
     */
    void operator()(const std::vector<Real>& args, Real& result) const {
        scalar_operator_(function_, args, result);
    }

private:
    //! Signature of function to get the name of the function.
    using GetNameSignature = std::string_view(
        const utilities::Any& /*function_object*/);

    //! Signature of function to operate on scalars.
    using ScalarOperatorSignature = void(
        const utilities::Any& /*function_object*/,
        const std::vector<Real>& /*args*/, Real& /*result*/);

    //! Function object.
    utilities::Any function_;

    //! Function to get the name of the function.
    GetNameSignature* get_name_;

    //! Function to operate on scalars.
    ScalarOperatorSignature* scalar_operator_;
};

}  // namespace func_sketch::math
