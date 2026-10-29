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
#include "func_sketch/expressions/parameter_value_dict.h"
#include "func_sketch/parameter_type.h"
#include "func_sketch/point.h"

namespace func_sketch::curves {

CurveSampler::CurveSampler(const plotter::PlotRange& range,
    const sampling::SamplingConfig& config,
    const math::PythonFunctionList& python_functions)
    : expression_parser_(python_functions),
      range_(range),
      point_sampler_(range, config),
      parameterized_point_sampler_(range, config) {}

CurveSampler& CurveSampler::range(const plotter::PlotRange& value) {
    range_ = value;
    point_sampler_.range(value);
    parameterized_point_sampler_.range(value);
    return *this;
}

CurveSampler& CurveSampler::config(const sampling::SamplingConfig& value) {
    point_sampler_.config(value);
    parameterized_point_sampler_.config(value);
    return *this;
}

SampledExplicitCurve CurveSampler::operator()(
    const ExplicitCurveSpec& spec) const {
    const auto expression = expression_parser_(spec.function_expression_str);
    expressions::ParameterValueDict parameters;
    return SampledExplicitCurve{.name = spec.name,
        .points = point_sampler_(
            [&expression, &parameters, this](Real parameter) {
                parameters[ParameterType::x] = parameter;
                Real value;
                evaluator_(*expression, parameters, value);
                return Point{.x = parameter, .y = value};
            },
            range_.x_range()),
        .color = spec.color};
}

SampledParameterizedCurve CurveSampler::operator()(
    const ParameterizedCurveSpec& spec) const {
    const auto x_expression = expression_parser_(spec.x_expression_str);
    const auto y_expression = expression_parser_(spec.y_expression_str);
    expressions::ParameterValueDict parameters;
    return SampledParameterizedCurve{.name = spec.name,
        .points = parameterized_point_sampler_(
            [&x_expression, &y_expression, &parameters, this](Real parameter) {
                parameters[ParameterType::t] = parameter;
                Real x_value;
                Real y_value;
                evaluator_(*x_expression, parameters, x_value);
                evaluator_(*y_expression, parameters, y_value);
                return ParameterizedPoint{
                    .t = parameter, .x = x_value, .y = y_value};
            },
            spec.parameter_range),
        .color = spec.color};
}

const math::MathFunctionList& CurveSampler::math_function_list()
    const noexcept {
    return expression_parser_.math_function_list();
}

const expressions::MathOperationList& CurveSampler::math_operation_list()
    const noexcept {
    return expression_parser_.math_operation_list();
}

const math::ConstantList& CurveSampler::constant_list() const noexcept {
    return expression_parser_.constant_list();
}

}  // namespace func_sketch::curves
