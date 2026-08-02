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
 * \brief Implementation of FunctionSampler class.
 */
#include "func_sketch/plotter/function_sampler.h"

namespace func_sketch::plotter {

FunctionSampler::FunctionSampler(
    // NOLINTNEXTLINE(*-pass-by-value): Wrong warning for small objects.
    const PlotRange& range, const PlotConfig& config)
    : range_(range), config_(config) {}

FunctionSampler& FunctionSampler::range(const PlotRange& value) {
    range_ = value;
    return *this;
}

FunctionSampler& FunctionSampler::config(const PlotConfig& value) {
    config_ = value;
    return *this;
}

std::vector<Point> FunctionSampler::operator()(
    const expressions::Expression& function) const {
    std::vector<Point> samples;
    samples.reserve(config_.num_sample_points());
    for (std::size_t i = 0; i < config_.num_sample_points(); ++i) {
        const Scalar x_ratio =
            static_cast<Scalar>(i) / (config_.num_sample_points() - 1);
        const Scalar x_value = range_.x_range().first +
            x_ratio * (range_.x_range().second - range_.x_range().first);

        Scalar y_value;
        evaluator_(function, x_value, y_value);

        samples.push_back(Point{.x = x_value, .y = y_value});
    }
    return samples;
}

}  // namespace func_sketch::plotter
