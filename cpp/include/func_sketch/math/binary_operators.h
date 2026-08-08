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
 * \brief Definition of binary operators.
 */
#pragma once

#include <string_view>

#include "func_sketch/common_types.h"

namespace func_sketch::math {

/*!
 * \brief Class of addition operator.
 */
class AdditionOperator {
public:
    /*!
     * \brief Get the name of the operator.
     *
     * \return Name of the operator.
     */
    [[nodiscard]] static std::string_view name() noexcept { return "add"; }

    /*!
     * \brief Operate on a pair of scalars.
     *
     * \param[in] left Left scalar.
     * \param[in] right Right scalar.
     * \param[out] result Result scalar.
     */
    static void operator()(
        const Number& left, const Number& right, Number& result) noexcept {
        std::visit(
            [&result](const auto& left_value, const auto& right_value) {
                result = left_value + right_value;
            },
            left, right);
    }
};

/*!
 * \brief Class of subtraction operator.
 */
class SubtractionOperator {
public:
    /*!
     * \brief Get the name of the operator.
     *
     * \return Name of the operator.
     */
    [[nodiscard]] static std::string_view name() noexcept { return "sub"; }

    /*!
     * \brief Operate on a pair of scalars.
     *
     * \param[in] left Left scalar.
     * \param[in] right Right scalar.
     * \param[out] result Result scalar.
     */
    static void operator()(
        const Number& left, const Number& right, Number& result) noexcept {
        std::visit(
            [&result](const auto& left_value, const auto& right_value) {
                result = left_value - right_value;
            },
            left, right);
    }
};

/*!
 * \brief Class of multiplication operator.
 */
class MultiplicationOperator {
public:
    /*!
     * \brief Get the name of the operator.
     *
     * \return Name of the operator.
     */
    [[nodiscard]] static std::string_view name() noexcept { return "mul"; }

    /*!
     * \brief Operate on a pair of scalars.
     *
     * \param[in] left Left scalar.
     * \param[in] right Right scalar.
     * \param[out] result Result scalar.
     */
    static void operator()(
        const Number& left, const Number& right, Number& result) noexcept {
        std::visit(
            [&result](const auto& left_value, const auto& right_value) {
                result = left_value * right_value;
            },
            left, right);
    }
};

/*!
 * \brief Class of division operator.
 */
class DivisionOperator {
public:
    /*!
     * \brief Get the name of the operator.
     *
     * \return Name of the operator.
     */
    [[nodiscard]] static std::string_view name() noexcept { return "div"; }

    /*!
     * \brief Operate on a pair of scalars.
     *
     * \param[in] left Left scalar.
     * \param[in] right Right scalar.
     * \param[out] result Result scalar.
     */
    static void operator()(
        const Number& left, const Number& right, Number& result) noexcept {
        std::visit(
            [&result](const auto& left_value, const auto& right_value) {
                result = left_value / right_value;
            },
            left, right);
    }
};

}  // namespace func_sketch::math
