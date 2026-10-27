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
 * \brief Definition of ParameterValueDict class.
 */
#pragma once

#include <array>
#include <cstddef>
#include <optional>

#include "func_sketch/common_types.h"
#include "func_sketch/exceptions.h"
#include "func_sketch/parameter_type.h"

namespace func_sketch::expressions {

/*!
 * \brief Class of dictionaries of values of parameters.
 */
class ParameterValueDict {
public:
    /*!
     * \brief Constructor.
     *
     * All parameters have no value after construction.
     */
    ParameterValueDict() = default;

    /*!
     * \brief Class of proxies to set values of parameters.
     */
    class MutableParameterProxy {
    public:
        /*!
         * \brief Constructor.
         *
         * \param[in] value Reference to the value of the parameter.
         */
        explicit MutableParameterProxy(std::optional<Number>& value)
            : value_(value) {}

        /*!
         * \brief Set the value of the parameter.
         *
         * \param[in] new_value New value.
         * \return Reference to this object.
         */
        MutableParameterProxy& operator=(const Number& new_value) {
            value_ = new_value;
            return *this;
        }

    private:
        //! Reference to the value of the parameter.
        std::optional<Number>& value_;
    };

    /*!
     * \brief Access to the value of a parameter to set it.
     *
     * \param[in] type Type of the parameter.
     * \return Proxy to set the value of the parameter.
     * \throw InvalidArgumentException If the type of the parameter is
     * invalid.
     */
    MutableParameterProxy operator[](ParameterType type) {
        return MutableParameterProxy(values_[to_index(type)]);
    }

    /*!
     * \brief Get the value of a parameter.
     *
     * \param[in] type Type of the parameter.
     * \return Value of the parameter, or `std::nullopt` if no value is set.
     * \throw InvalidArgumentException If the type of the parameter is
     * invalid.
     */
    const std::optional<Number>& operator[](ParameterType type) const {
        return values_[to_index(type)];
    }

private:
    //! Number of types of parameters.
    static constexpr std::size_t num_parameter_types = 3;

    /*!
     * \brief Convert a type of parameters to the index in the array.
     *
     * \param[in] type Type of the parameter.
     * \return Index.
     * \throw InvalidArgumentException If the type of the parameter is
     * invalid.
     */
    static std::size_t to_index(ParameterType type) {
        const auto index = static_cast<std::size_t>(type);
        if (index >= num_parameter_types) {
            throw InvalidArgumentException("Invalid parameter type.");
        }
        return index;
    }

    //! Values of parameters.
    std::array<std::optional<Number>, num_parameter_types> values_{};
};

}  // namespace func_sketch::expressions
