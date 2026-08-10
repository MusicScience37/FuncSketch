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
 * \brief Definition of utility functions for tests of single-variate functions.
 */
#pragma once

#include <functional>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"
#include "func_sketch/math/math_function.h"

/*!
 * \brief Test a single-variate function.
 *
 * \tparam ArgType Type of the argument.
 * \tparam ResultType Type of the result.
 * \param[in] function Single-variate function to test.
 * \param[in] arg Argument to pass to the function.
 * \param[in] reference_function Reference function to compare the result with.
 */
template <typename ArgType, typename ResultType>
inline void test_single_variate_function(
    const func_sketch::math::MathFunction& function, const ArgType& arg,
    const std::function<ResultType(ArgType)>& reference_function) {
    const auto args = std::vector<func_sketch::Number>{arg};
    func_sketch::Number result;

    function(args, result);

    CHECK_THAT(std::get<ResultType>(result),
        Catch::Matchers::WithinRel(reference_function(arg)));
}

/*!
 * \brief Test errors of a single-variate function.
 *
 * \tparam ArgType Type of the argument.
 * \param[in] function Single-variate function to test.
 */
template <typename ArgType>
inline void test_single_variate_function_errors(
    const func_sketch::math::MathFunction& function) {
    func_sketch::Number result;

    const func_sketch::Number arg = static_cast<ArgType>(1);
    CHECK_THROWS(function(std::vector<func_sketch::Number>{}, result));
    CHECK_THROWS(function(std::vector<func_sketch::Number>{arg, arg}, result));
}
