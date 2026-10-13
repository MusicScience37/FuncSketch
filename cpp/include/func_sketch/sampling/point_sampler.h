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
 * \brief Definition of PointSampler class.
 */
#pragma once

#include <functional>
#include <utility>
#include <vector>

#include "func_sketch/common_types.h"
#include "func_sketch/parameterized_point.h"
#include "func_sketch/plotter/plot_range.h"
#include "func_sketch/point.h"
#include "func_sketch/sampling/sampling_config.h"

namespace func_sketch::sampling {

/*!
 * \brief Class to sample points.
 *
 * \tparam PointType Type of the point.
 */
template <typename PointType>
class PointSampler {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] range Range of the plot.
     * \param[in] config Configuration of sampling.
     */
    PointSampler(const plotter::PlotRange& range, const SamplingConfig& config);

    /*!
     * \brief Set the range of the plot.
     *
     * \param[in] value Range of the plot.
     * \return Reference to this object.
     */
    PointSampler& range(const plotter::PlotRange& value);

    /*!
     * \brief Set the configuration of sampling.
     *
     * \param[in] value Configuration of sampling.
     * \return Reference to this object.
     */
    PointSampler& config(const SamplingConfig& value);

    /*!
     * \brief Sample points.
     *
     * \param[in] function Function to sample.
     * This function calculates a point for a parameter value.
     * \param[in] parameter_range Range of the parameter.
     * \return Sampled points.
     *
     * \throw InvalidArgumentException If the range of the parameter is invalid.
     */
    [[nodiscard]] std::vector<PointType> operator()(
        const std::function<PointType(Real)>& function,
        const std::pair<Real, Real>& parameter_range) const;

private:
    //! Range of the plot.
    plotter::PlotRange range_;

    //! Configuration of sampling.
    SamplingConfig config_;
};

extern template class PointSampler<func_sketch::Point>;
extern template class PointSampler<func_sketch::ParameterizedPoint>;

}  // namespace func_sketch::sampling
