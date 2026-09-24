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
 * \brief Definition of ConstantInfo class.
 */
#pragma once

#include <string>
#include <utility>

namespace func_sketch::math {

/*!
 * \brief Class to store information about a constant.
 *
 * \note Future implementation may include additional information about the
 * constant.
 */
class ConstantInfo {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] name Name of the constant.
     */
    explicit ConstantInfo(std::string name) : name_(std::move(name)) {}

    /*!
     * \brief Get the name of the constant.
     *
     * \return Name of the constant.
     */
    [[nodiscard]] const std::string& name() const noexcept { return name_; }

private:
    //! Name of the constant.
    std::string name_;
};

}  // namespace func_sketch::math
