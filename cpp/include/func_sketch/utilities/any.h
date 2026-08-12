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
 * \brief Definition of Any class.
 */
#pragma once

#include <any>
#include <type_traits>
#include <utility>

namespace func_sketch::utilities {

/*!
 * \brief Class to store any type of value.
 *
 * \note This class is a wrapper of std::any.
 */
class Any {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] value Value to store.
     */
    template <typename T>
        requires(!std::is_same_v<std::decay_t<T>, Any>)
    explicit Any(T&& value) : value_(std::forward<T>(value)) {}

    /*!
     * \brief Get the stored value.
     *
     * \tparam T Type of the stored value.
     * \return Stored value.
     */
    template <typename T>
    [[nodiscard]] const T& get() const {
        return std::any_cast<const T&>(value_);
    }

private:
    //! Stored value.
    std::any value_;
};

}  // namespace func_sketch::utilities
