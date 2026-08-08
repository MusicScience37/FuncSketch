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
 * \brief Definition of ExpFunction class.
 */
#pragma once

#include <cmath>
#include <string_view>
#include <vector>

#include "func_sketch/common_types.h"
#include "func_sketch/exceptions.h"

namespace func_sketch::math {

/*!
 * \brief Class of exponential function.
 */
class ExpFunction {
public:
    /*!
     * \brief Get the name of the function.
     *
     * \return Name of the function.
     */
    [[nodiscard]] static std::string_view name() noexcept { return "exp"; }

    /*!
     * \brief Operate on scalars.
     *
     * \param[in] args Arguments.
     * \param[out] result Result.
     */
    static void operator()(const std::vector<Number>& args, Number& result) {
        if (args.size() != 1) {
            throw InvalidExpressionException(
                "exp function requires exactly one argument.");
        }
        result = std::visit(
            [](const auto& arg) { return std::exp(static_cast<Real>(arg)); },
            args[0]);
    }
};

}  // namespace func_sketch::math
