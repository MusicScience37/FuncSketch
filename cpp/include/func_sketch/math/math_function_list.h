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
 * \brief Definition of MathFunctionList class.
 */
#pragma once

#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

#include "func_sketch/math/math_function.h"
#include "func_sketch/math/math_function_type.h"

namespace func_sketch::math {

/*!
 * \brief Class of lists of mathematical functions.
 */
class MathFunctionList {
public:
    /*!
     * \brief Constructor.
     */
    MathFunctionList() = default;

    /*!
     * \brief Append a mathematical function to the list.
     *
     * \param[in] function Mathematical function to append.
     */
    template <MathFunctionType T>
    void emplace(T&& function) {
        functions_.emplace(function.name(), std::forward<T>(function));
    }

    /*!
     * \brief Get a mathematical function from the list.
     *
     * \param[in] name Name of the mathematical function.
     * \return Mathematical function if found, otherwise std::nullopt.
     */
    [[nodiscard]] std::optional<MathFunction> get(
        const std::string& name) const {
        const auto iter = functions_.find(name);
        if (iter != functions_.end()) {
            return iter->second;
        }
        return std::nullopt;
    }

private:
    //! List of mathematical functions.
    std::unordered_map<std::string, MathFunction> functions_;
};

}  // namespace func_sketch::math
