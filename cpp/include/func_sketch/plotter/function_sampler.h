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
 * \brief Definition of FunctionSampler class.
 */
#pragma once

#include <vector>

#include "func_sketch/expressions/expression.h"
#include "func_sketch/expressions/expression_evaluator.h"
#include "func_sketch/plotter/plot_config.h"
#include "func_sketch/plotter/plot_range.h"
#include "func_sketch/plotter/point.h"

namespace func_sketch::plotter {

/*!
 * \brief Class to sample functions for plotting.
 */
class FunctionSampler {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] range Range of plots.
     * \param[in] config Configuration of plots.
     */
    FunctionSampler(const PlotRange& range, const PlotConfig& config);

    /*!
     * \brief Set the range of plots.
     *
     * \param[in] value Range of plots.
     * \return Reference to this object.
     */
    FunctionSampler& range(const PlotRange& value);

    /*!
     * \brief Set the configuration of plots.
     *
     * \param[in] value Configuration of plots.
     * \return Reference to this object.
     */
    FunctionSampler& config(const PlotConfig& value);

    /*!
     * \brief Sample a function for plotting.
     *
     * \param[in] function Function to sample.
     * \return Sampled points of the function.
     */
    [[nodiscard]] std::vector<Point> operator()(
        const expressions::Expression& function) const;

private:
    //! Range of plots.
    PlotRange range_;

    //! Configuration of plots.
    PlotConfig config_;

    //! Evaluator of expressions.
    expressions::ExpressionEvaluator evaluator_;
};

}  // namespace func_sketch::plotter
