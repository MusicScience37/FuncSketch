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
 * \brief Definition of AcceptableTypes struct.
 */
#pragma once

#include <type_traits>

#include "func_sketch/math/common_type.h"

namespace func_sketch::math {

/*!
 * \brief Struct to indicate that there is no acceptable type.
 */
struct NoAcceptableType {};

namespace details {

/*!
 * \brief Internal implementation to select a type to use from a list of
 * acceptable types.
 *
 * \tparam ReceivedType Type of the received argument.
 * \tparam AcceptableTypes List of acceptable types.
 */
template <typename ReceivedType, typename... AcceptableTypes>
struct SelectTypeToUseImpl;

/*!
 * \brief Internal implementation to select a type to use from a list of
 * acceptable types.
 *
 * \tparam ReceivedType Type of the received argument.
 * \tparam FirstAcceptableType First acceptable type.
 * \tparam RemainingAcceptableTypes Remaining acceptable types.
 */
template <typename ReceivedType, typename FirstAcceptableType,
    typename... RemainingAcceptableTypes>
struct SelectTypeToUseImpl<ReceivedType, FirstAcceptableType,
    RemainingAcceptableTypes...> {
    //! Selected type. NoAcceptableType if there is no acceptable type.
    using Type = std::conditional_t<
        std::is_same_v<CommonType<ReceivedType, FirstAcceptableType>,
            FirstAcceptableType>,
        FirstAcceptableType,
        typename SelectTypeToUseImpl<ReceivedType,
            RemainingAcceptableTypes...>::Type>;
};

/*!
 * \brief Internal implementation to select a type to use from a list of
 * acceptable types.
 *
 * \tparam ReceivedType Type of the received argument.
 */
template <typename ReceivedType>
struct SelectTypeToUseImpl<ReceivedType> {
    //! Selected type. NoAcceptableType if there is no acceptable type.
    using Type = NoAcceptableType;
};

}  // namespace details

/*!
 * \brief Traits struct to handle acceptable number types.
 *
 * \tparam Types Types to accept.
 */
template <typename... Types>
struct AcceptableTypes {
    /*!
     * \brief Select a type to use from the list of acceptable types.
     *
     * \tparam ReceivedType Type of the received argument.
     *
     * \note This type alias becomes the first type in the list of acceptable
     * types that can be used to convert a number of the received type without
     * loss of information. Actual check is done by
     * `std::is_same_v<CommonType<ReceivedType, AcceptableType>,
     * AcceptableType>`.
     * \note This type alias becomes \ref func_sketch::math::NoAcceptableType if
     * there is no acceptable type.
     * \note A number is given to a function after converting to the type
     * selected using this type alias.
     */
    template <typename ReceivedType>
    using SelectTypeToUse =
        details::SelectTypeToUseImpl<ReceivedType, Types...>::Type;
};

namespace details {

/*!
 * \brief Check whether a type is \ref func_sketch::math::AcceptableTypes.
 *
 * \tparam Type Type to check.
 */
template <typename Type>
struct IsAcceptableTypes : std::false_type {};

/*!
 * \brief Check whether a type is \ref func_sketch::math::AcceptableTypes.
 *
 * \tparam Types Types to accept.
 */
template <typename... Types>
struct IsAcceptableTypes<AcceptableTypes<Types...>> : std::true_type {};

}  // namespace details

/*!
 * \brief Concept to check whether a type is
 * \ref func_sketch::math::AcceptableTypes.
 *
 * \tparam Type Type to check.
 */
template <typename Type>
concept AcceptableTypesSpec = details::IsAcceptableTypes<Type>::value;

}  // namespace func_sketch::math
