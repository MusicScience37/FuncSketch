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
 * \brief Definition of ConstantList class.
 */
#pragma once

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "func_sketch/common_types.h"
#include "func_sketch/math/constant_info.h"

namespace func_sketch::math {

/*!
 * \brief Class of lists of constants.
 */
class ConstantList {
public:
    /*!
     * \brief Constructor.
     */
    ConstantList() = default;

    /*!
     * \brief Append a constant to the list.
     *
     * \param[in] name Name of the constant.
     * \param[in] value Value of the constant.
     */
    void emplace(const std::string& name, Number value) {
        constants_.try_emplace(name, value);
    }

    /*!
     * \brief Get a constant from the list.
     *
     * \param[in] name Name of the constant.
     * \return Constant value if found, otherwise std::nullopt.
     */
    [[nodiscard]] std::optional<Number> get(const std::string& name) const {
        const auto iter = constants_.find(name);
        if (iter == constants_.end()) {
            return std::nullopt;
        }
        return iter->second;
    }

    /*!
     * \brief Create a list of information of constants.
     *
     * \return List of information of constants.
     */
    [[nodiscard]] std::vector<ConstantInfo> create_constant_info_list() const {
        std::vector<ConstantInfo> info_list;
        info_list.reserve(constants_.size());
        for (const auto& [name, value] : constants_) {
            info_list.emplace_back(name);
        }
        return info_list;
    }

private:
    //! List of constants.
    std::unordered_map<std::string, Number> constants_;
};

/*!
 * \brief Generate a list of built-in constants.
 *
 * \return List of built-in constants.
 */
[[nodiscard]] ConstantList generate_constant_list();

}  // namespace func_sketch::math
