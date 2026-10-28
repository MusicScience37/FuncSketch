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
 * \brief Definition of MathOperationInfo class.
 */
#pragma once

#include <string>
#include <utility>
#include <vector>

namespace func_sketch::expressions {

/*!
 * \brief Class to store information about a mathematical operation.
 *
 * \note Argument names should be same as the names in documentation.
 */
class MathOperationInfo {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] name Name of the mathematical operation.
     * \param[in] argument_names Names of the arguments of the mathematical
     * operation.
     */
    MathOperationInfo(std::string name, std::vector<std::string> argument_names)
        : name_(std::move(name)), argument_names_(std::move(argument_names)) {}

    /*!
     * \brief Get the name of the mathematical operation.
     *
     * \return Name of the mathematical operation.
     */
    [[nodiscard]] const std::string& name() const noexcept { return name_; }

    /*!
     * \brief Get the argument names of the mathematical operation.
     *
     * \return Argument names of the mathematical operation.
     */
    [[nodiscard]] const std::vector<std::string>& argument_names()
        const noexcept {
        return argument_names_;
    }

private:
    //! Name of the mathematical operation.
    std::string name_;

    //! Argument names.
    std::vector<std::string> argument_names_;
};

}  // namespace func_sketch::expressions
