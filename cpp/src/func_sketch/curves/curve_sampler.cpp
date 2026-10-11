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

#include "func_sketch/common_types.h"
#include "func_sketch/point.h"

namespace func_sketch::curves {

CurveSampler::CurveSampler(const plotter::PlotRange& range,
    const sampling::SamplingConfig& config,
    const math::PythonFunctionList& python_functions)
    : expression_parser_(python_functions),
      range_(range),
      point_sampler_(range, config) {}

CurveSampler& CurveSampler::range(const plotter::PlotRange& value) {
    range_ = value;
    point_sampler_.range(value);
    return *this;
}

CurveSampler& CurveSampler::config(const sampling::SamplingConfig& value) {
    point_sampler_.config(value);
    return *this;
}

SampledCurve CurveSampler::operator()(const ExplicitCurveSpec& spec) const {
    const auto expression = expression_parser_(spec.function_expression_str);
    return SampledCurve{.name = spec.name,
        .points = point_sampler_(
            [&expression, this](Real parameter) {
                Real value;
                evaluator_(*expression, parameter, value);
                return Point{.x = parameter, .y = value};
            },
            range_.x_range()),
        .color = spec.color};
}

const math::MathFunctionList& CurveSampler::math_function_list()
    const noexcept {
    return expression_parser_.math_function_list();
}

const math::ConstantList& CurveSampler::constant_list() const noexcept {
    return expression_parser_.constant_list();
}

}  // namespace func_sketch::curves
