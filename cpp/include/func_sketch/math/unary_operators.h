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
 * \brief Definition of unary operators.
 */
#pragma once

#include <string_view>

#include "func_sketch/common_types.h"

namespace func_sketch::math {

/*!
 * \brief Class of unary plus operator.
 */
class UnaryPlusOperator {
public:
    /*!
     * \brief Get the name of the operator.
     *
     * \return Name of the operator.
     */
    [[nodiscard]] static std::string_view name() noexcept { return "identity"; }

    /*!
     * \brief Operate on a scalar.
     *
     * \param[in] arg Argument.
     * \param[out] result Result.
     */
    static void operator()(const Number& arg, Number& result) noexcept {
        result = arg;
    }
};

/*!
 * \brief Class of unary minus operator.
 */
class UnaryMinusOperator {
public:
    /*!
     * \brief Get the name of the operator.
     *
     * \return Name of the operator.
     */
    [[nodiscard]] static std::string_view name() noexcept { return "negate"; }

    /*!
     * \brief Operate on a scalar.
     *
     * \param[in] arg Argument.
     * \param[out] result Result.
     */
    static void operator()(const Number& arg, Number& result) {
        std::visit([&result](const auto& value) { result = -value; }, arg);
    }
};

}  // namespace func_sketch::math
