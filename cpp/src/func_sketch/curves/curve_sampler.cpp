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
 * \brief Implementation of CurveSampler class.
 */
#include "func_sketch/curves/curve_sampler.h"

namespace func_sketch::curves {

CurveSampler::CurveSampler(const plotter::PlotRange& range,
    const sampling::SamplingConfig& config,
    const math::PythonFunctionList& python_functions)
    : expression_parser_(python_functions), function_sampler_(range, config) {}

CurveSampler& CurveSampler::range(const plotter::PlotRange& value) {
    function_sampler_.range(value);
    return *this;
}

CurveSampler& CurveSampler::config(const sampling::SamplingConfig& value) {
    function_sampler_.config(value);
    return *this;
}

SampledCurve CurveSampler::operator()(const ExplicitCurveSpec& spec) const {
    return SampledCurve{.name = spec.name,
        .points = function_sampler_(
            *expression_parser_(spec.function_expression_str)),
        .color = spec.color};
}

}  // namespace func_sketch::curves
