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
 * \brief Definition of BoostMathPolicy type.
 */
#pragma once

#include <boost/math/policies/policy.hpp>

namespace func_sketch::math {

/*!
 * \brief Type of the policy of Boost.Math functions.
 *
 * \note Applying this policy to Boost.Math functions prevents them from
 * throwing exceptions on errors.
 */
using BoostMathPolicy = boost::math::policies::policy<
    boost::math::policies::domain_error<boost::math::policies::ignore_error>,
    boost::math::policies::pole_error<boost::math::policies::ignore_error>,
    boost::math::policies::overflow_error<boost::math::policies::ignore_error>,
    boost::math::policies::underflow_error<boost::math::policies::ignore_error>,
    boost::math::policies::denorm_error<boost::math::policies::ignore_error>,
    boost::math::policies::rounding_error<boost::math::policies::ignore_error>,
    boost::math::policies::evaluation_error<
        boost::math::policies::ignore_error>,
    boost::math::policies::indeterminate_result_error<
        boost::math::policies::ignore_error>>;

}  // namespace func_sketch::math
