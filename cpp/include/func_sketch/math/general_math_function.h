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
 * \brief Definition of GeneralMathFunction class.
 */
#pragma once

#include <concepts>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <variant>
#include <vector>

#include <fmt/base.h>
#include <fmt/format.h>

#include "func_sketch/common_types.h"
#include "func_sketch/exceptions.h"
#include "func_sketch/math/acceptable_types.h"
#include "func_sketch/math/number_type_name.h"

namespace func_sketch::math {

/*!
 * \brief Class of general implementation of mathematical functions.
 *
 * \tparam FunctionType Type of the function object to compute numbers.
 * \tparam AcceptableTypesPerArgument \ref func_sketch::math::AcceptableTypes
 * types for each argument.
 */
template <typename FunctionType,
    AcceptableTypesSpec... AcceptableTypesPerArgument>
class GeneralMathFunction {
public:
    /*!
     * \brief Constructor.
     *
     * \tparam InputFunctionType Type of the function object to compute numbers.
     * \param[in] name Name of the function.
     * \param[in] function Function object to compute numbers.
     */
    template <typename InputFunctionType>
    GeneralMathFunction(std::string name, InputFunctionType&& function)
        : name_(std::move(name)),
          function_(std::forward<InputFunctionType>(function)) {}

    /*!
     * \brief Get the name of the function.
     *
     * \return Name of the function.
     */
    [[nodiscard]] std::string_view name() const noexcept { return name_; }

    /*!
     * \brief Operate on scalars.
     *
     * \param[in] args Arguments.
     * \param[out] result Result.
     */
    void operator()(const std::vector<Number>& args, Number& result) const {
        constexpr std::size_t num_args = sizeof...(AcceptableTypesPerArgument);
        if (args.size() != num_args) {
            throw InvalidExpressionException(fmt::format(
                "{} function requires exactly {} arguments. Actual: {}.", name_,
                num_args, args.size()));
        }
        operate_impl(args, result, std::make_index_sequence<num_args>{});
    }

private:
    //! Type of tuples of acceptable types.
    using AcceptableTypesTuples = std::tuple<AcceptableTypesPerArgument...>;

    /*!
     * \brief Operate on scalars (internal implementation).
     *
     * \tparam Indices Indices of arguments.
     * \param[in] args Arguments.
     * \param[out] result Result.
     */
    template <std::size_t... Indices>
    void operate_impl(const std::vector<Number>& args, Number& result,
        std::index_sequence<Indices...> /*indices*/) const {
        std::visit(
            [this, &result](const auto&... actual_args) {
                constexpr bool is_all_acceptable =
                    (is_acceptable<std::decay_t<decltype(actual_args)>,
                         Indices>() &&
                        ...);
                if constexpr (is_all_acceptable) {
                    result = function_(convert_to_acceptable_type<
                        std::decay_t<decltype(actual_args)>, Indices>(
                        actual_args)...);
                } else {
                    constexpr std::size_t first_unacceptable_index =
                        get_first_false(
                            is_acceptable<std::decay_t<decltype(actual_args)>,
                                Indices>()...);
                    using FirstUnacceptableType = std::decay_t<
                        decltype(std::get<first_unacceptable_index>(
                            std::forward_as_tuple(actual_args...)))>;
                    throw InvalidExpressionException(fmt::format(
                        "{} function can not accept {} for the {}-th argument.",
                        name_, number_type_name<FirstUnacceptableType>,
                        first_unacceptable_index + 1));
                }
            },
            args[Indices]...);
    }

    /*!
     * \brief Check whether the given type is acceptable for the argument at the
     * given index.
     *
     * \tparam GivenType Type of the given argument.
     * \tparam Index Index of the argument.
     * \retval true The given type is acceptable for the argument at the given
     * index.
     * \retval false The given type is not acceptable for the argument at the
     * given index.
     */
    template <typename GivenType, std::size_t Index>
    [[nodiscard]] static constexpr bool is_acceptable() {
        using AcceptableTypes =
            std::tuple_element_t<Index, AcceptableTypesTuples>;
        return !std::is_same_v<
            typename AcceptableTypes::template SelectTypeToUse<GivenType>,
            NoAcceptableType>;
    }

    /*!
     * \brief Convert the given value to an acceptable type for the argument at
     * the given index.
     *
     * \tparam GivenType Type of the given argument.
     * \tparam Index Index of the argument.
     * \param[in] value Value to convert.
     * \return Converted value.
     */
    template <typename GivenType, std::size_t Index>
    [[nodiscard]] static auto convert_to_acceptable_type(
        const GivenType& value) {
        using AcceptableTypes =
            std::tuple_element_t<Index, AcceptableTypesTuples>;
        return static_cast<
            AcceptableTypes::template SelectTypeToUse<GivenType>>(value);
    }

    /*!
     * \brief Get the index of the first false value.
     *
     * \tparam T Types of the remaining boolean values.
     * \param[in] first The first boolean value.
     * \param[in] remaining The remaining boolean values.
     * \return Index of the first false value. Returns the size of the list if
     * all values are true.
     */
    template <std::same_as<bool>... T>
    [[nodiscard]] static constexpr std::size_t get_first_false(
        bool first, T... remaining) {
        if (!first) {
            return 0;
        }
        return 1 + get_first_false(remaining...);
    }

    /*!
     * \brief Get the first false. (Variadic template base case)
     *
     * \return Index of the first false value. Returns 0 in this base case.
     */
    [[nodiscard]] static constexpr std::size_t get_first_false() { return 0; }

    //! Function name.
    std::string name_;

    //! Function object to compute numbers.
    FunctionType function_;
};

namespace details {

/*!
 * \brief Check whether a type is a tuple of \ref
 * func_sketch::math::AcceptableTypes.
 *
 * \tparam Type Type to check.
 */
template <typename Type>
struct IsAcceptableTypesTuple : std::false_type {};

/*!
 * \brief Check whether a type is a tuple of \ref
 * func_sketch::math::AcceptableTypes.
 *
 * \tparam Types Types to accept.
 */
template <AcceptableTypesSpec... Types>
struct IsAcceptableTypesTuple<std::tuple<Types...>> : std::true_type {};

/*!
 * \brief Concept to check whether a type is a tuple of
 * \ref func_sketch::math::AcceptableTypes.
 *
 * \tparam Type Type to check.
 */
template <typename Type>
concept AcceptableTypesTupleType = IsAcceptableTypesTuple<Type>::value;

/*!
 * \brief Make a general mathematical function.
 *
 * \tparam AcceptableTypesTuple Tuple of \ref func_sketch::math::AcceptableTypes
 * types for each argument.
 * \tparam FunctionType Type of the function object to compute numbers.
 * \tparam Indices Indices of arguments.
 * \param[in] name Name of the function.
 * \param[in] function Function object to compute numbers.
 * \return Created general mathematical function.
 */
template <details::AcceptableTypesTupleType AcceptableTypesTuple,
    typename FunctionType, std::size_t... Indices>
[[nodiscard]] auto make_general_math_function_impl(std::string name,
    FunctionType&& function, std::index_sequence<Indices...> /*indices*/) {
    return GeneralMathFunction<std::decay_t<FunctionType>,
        std::tuple_element_t<Indices, AcceptableTypesTuple>...>(
        std::move(name), std::forward<FunctionType>(function));
}

}  // namespace details

/*!
 * \brief Make a general mathematical function.
 *
 * \tparam AcceptableTypesTuple Tuple of \ref func_sketch::math::AcceptableTypes
 * types for each argument.
 * \tparam FunctionType Type of the function object to compute numbers.
 * \param[in] name Name of the function.
 * \param[in] function Function object to compute numbers.
 * \return Created general mathematical function.
 */
template <details::AcceptableTypesTupleType AcceptableTypesTuple,
    typename FunctionType>
[[nodiscard]] auto make_general_math_function(
    std::string name, FunctionType&& function) {
    return details::make_general_math_function_impl<AcceptableTypesTuple>(
        std::move(name), std::forward<FunctionType>(function),
        std::make_index_sequence<std::tuple_size_v<AcceptableTypesTuple>>{});
}

}  // namespace func_sketch::math
