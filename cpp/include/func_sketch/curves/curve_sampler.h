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
 * \brief Definition of CurveSampler class.
 */
#pragma once

#include "func_sketch/curves/explicit_curve_spec.h"
#include "func_sketch/curves/sampled_curve.h"
#include "func_sketch/math/functions/python_function_list.h"
#include "func_sketch/math/math_function_list.h"
#include "func_sketch/parser/expression_parser.h"
#include "func_sketch/plotter/plot_range.h"
#include "func_sketch/sampling/function_sampler.h"
#include "func_sketch/sampling/sampling_config.h"

namespace func_sketch::curves {

/*!
 * \brief Class to sample curves.
 */
class CurveSampler {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] range Range of plots.
     * \param[in] config Configuration of sampling.
     * \param[in] python_functions List of Python functions.
     */
    CurveSampler(const plotter::PlotRange& range,
        const sampling::SamplingConfig& config,
        const math::PythonFunctionList& python_functions);

    /*!
     * \brief Set the range of plots.
     *
     * \param[in] value Range of plots.
     * \return Reference to this object.
     */
    CurveSampler& range(const plotter::PlotRange& value);

    /*!
     * \brief Set the configuration of sampling.
     *
     * \param[in] value Configuration of sampling.
     * \return Reference to this object.
     */
    CurveSampler& config(const sampling::SamplingConfig& value);

    /*!
     * \brief Sample a curve.
     *
     * \param[in] spec Specification of the curve.
     * \return Sampled curve.
     */
    [[nodiscard]] SampledCurve operator()(const ExplicitCurveSpec& spec) const;

    /*!
     * \brief Get the list of mathematical functions.
     *
     * \return List of mathematical functions.
     */
    [[nodiscard]] const math::MathFunctionList& math_function_list()
        const noexcept;

    /*!
     * \brief Get the list of constants.
     *
     * \return List of constants.
     */
    [[nodiscard]] const math::ConstantList& constant_list() const noexcept;

private:
    //! Parser of expressions.
    parser::ExpressionParser expression_parser_;

    //! Sampler of functions.
    sampling::FunctionSampler function_sampler_;
};

}  // namespace func_sketch::curves
