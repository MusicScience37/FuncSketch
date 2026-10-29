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
 * \brief Definition of NumericalIntegrator class.
 */
#pragma once

#include <type_traits>
#include <variant>

#include "func_sketch/common_types.h"
#include "func_sketch/exceptions.h"
#include "func_sketch/math/operations/gauss_legendre_kronrod_integrator.h"

namespace func_sketch::math {

/*!
 * \brief Class to perform numerical integration.
 *
 * This class integrates functions returning \ref Number,
 * using real or complex numbers depending on the type of the function values.
 */
class NumericalIntegrator {
public:
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
        std::is_same_v<std::invoke_result_t<Function, Real>, Number>
    [[nodiscard]] Number operator()(
        const Function& function, Real left, Real right) const {
        const Real center = (left + right) * 0.5;
        const Number center_value = function(center);
        if (std::holds_alternative<Complex>(center_value)) {
            return integrate_complex(function, left, right);
        }
        return integrate_real(function, left, right);
    }

private:
    /*!
     * \brief Perform numerical integration of a real-valued function.
     *
     * \tparam Function Type of the function.
     * \param[in] function Function to integrate.
     * \param[in] left Left endpoint of the integration interval.
     * \param[in] right Right endpoint of the integration interval.
     * \return Result.
     */
    template <typename Function>
    [[nodiscard]] Number integrate_real(
        const Function& function, Real left, Real right) const {
        const auto real_integrand = [&function](Real arg) {
            return std::visit(
                [](const auto& value) -> Real {
                    using ValueType = std::decay_t<decltype(value)>;
                    if constexpr (std::is_same_v<ValueType, Complex>) {
                        throw AlgorithmFailureException(
                            "The integrand returned an inconsistent type.");
                    } else {
                        return static_cast<Real>(value);
                    }
                },
                function(arg));
        };
        return real_gauss_legendre_kronrod_integrator_(
            real_integrand, left, right);
    }

    /*!
     * \brief Perform numerical integration of a complex-valued function.
     *
     * \tparam Function Type of the function.
     * \param[in] function Function to integrate.
     * \param[in] left Left endpoint of the integration interval.
     * \param[in] right Right endpoint of the integration interval.
     * \return Result.
     */
    template <typename Function>
    [[nodiscard]] Number integrate_complex(
        const Function& function, Real left, Real right) const {
        const auto complex_integrand = [&function](Real arg) {
            return std::visit(
                [](const auto& value) -> Complex {
                    return static_cast<Complex>(value);
                },
                function(arg));
        };
        return complex_gauss_legendre_kronrod_integrator_(
            complex_integrand, left, right);
    }

    //! Integrator using the Gauss-Legendre-Kronrod method for real numbers.
    GaussLegendreKronrodIntegrator<Real>
        real_gauss_legendre_kronrod_integrator_;

    //! Integrator using the Gauss-Legendre-Kronrod method for complex numbers.
    GaussLegendreKronrodIntegrator<Complex>
        complex_gauss_legendre_kronrod_integrator_;
};

}  // namespace func_sketch::math
