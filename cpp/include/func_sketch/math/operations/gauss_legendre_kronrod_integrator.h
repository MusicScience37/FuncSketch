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
 * \brief Definition of GaussLegendreKronrodIntegrator class.
 */
#pragma once

#include <type_traits>

#include <num_collect/integration/gauss_legendre_kronrod_integrator.h>

#include "func_sketch/common_types.h"

namespace func_sketch::math {

/*!
 * \brief Class to perform numerical integration using the
 * Gauss-Legendre-Kronrod method.
 *
 * \tparam Value Type of the function values.
 * \ref Real or \ref Complex can be used.
 *
 * \note This class is a wrapper of
 * `num_collect::integration::gauss_legendre_kronrod_integrator`
 * with parameters tuned for rough accuracy and fast computation.
 */
template <typename Value>
    requires std::is_same_v<Value, Real> || std::is_same_v<Value, Complex>
class GaussLegendreKronrodIntegrator {
public:
    /*!
     * \brief Constructor.
     */
    GaussLegendreKronrodIntegrator() {
        integrator_.tol_abs_error(1e-4);
        integrator_.tol_rel_error(1e-4);
        integrator_.min_div_rate(0.05);
    }

    /*!
     * \brief Perform numerical integration of a function.
     *
     * \tparam Function Type of the function.
     * \param[in] function Function to integrate.
     * \param[in] left Left endpoint of the integration interval.
     * \param[in] right Right endpoint of the integration interval.
     * \return Result.
     *
     * \note This supports the case of `left > right`.
     */
    template <typename Function>
        requires std::is_invocable_v<Function, Real> &&
        std::is_convertible_v<std::invoke_result_t<Function, Real>, Value>
    [[nodiscard]] Value operator()(
        const Function& function, Real left, Real right) const {
        if (left == right) {
            return static_cast<Value>(0);
        }
        if (left > right) {
            return -operator()(function, right, left);
        }
        return integrator_.integrate(function, left, right);
    }

private:
    //! Actual integrator.
    num_collect::integration::gauss_legendre_kronrod_integrator<Value(Real)>
        integrator_;
};

}  // namespace func_sketch::math
