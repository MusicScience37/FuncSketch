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
 * \brief Definition of MathOperationList class.
 */
#pragma once

#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "func_sketch/expressions/math_operation.h"

namespace func_sketch::expressions {

/*!
 * \brief Class of lists of mathematical operations.
 */
class MathOperationList {
public:
    /*!
     * \brief Constructor.
     */
    MathOperationList() = default;

    /*!
     * \brief Add a mathematical operation to the list.
     *
     * \param[in] operation Mathematical operation to add.
     */
    void emplace(MathOperation
            operation) {  // NOLINT(performance-unnecessary-value-param)
                          // The object is moved.
        std::string name = operation.info().name();
        operations_.try_emplace(std::move(name), std::move(operation));
    }

    /*!
     * \brief Get a mathematical operation from the list.
     *
     * \param[in] name Name of the mathematical operation.
     * \return Mathematical operation if found, otherwise std::nullopt.
     */
    [[nodiscard]] std::optional<MathOperation> get(
        const std::string& name) const {
        const auto iter = operations_.find(name);
        if (iter != operations_.end()) {
            return iter->second;
        }
        return std::nullopt;
    }

private:
    //! List of mathematical operations.
    std::unordered_map<std::string, MathOperation> operations_;
};

}  // namespace func_sketch::expressions
