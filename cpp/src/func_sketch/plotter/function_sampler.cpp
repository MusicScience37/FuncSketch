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

#include <cmath>
#include <cstddef>
#include <cstdlib>

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
    const std::vector<Point> initial_samples = sample_initial_points(function);
    return sample_adaptive_points(function, initial_samples);
}

std::vector<Point> FunctionSampler::sample_initial_points(
    const expressions::Expression& function) const {
    std::vector<Point> samples;
    const std::size_t num_points = config_.initial_num_sample_points();
    samples.reserve(num_points);
    for (std::size_t i = 0; i < num_points; ++i) {
        const Real x_ratio =
            static_cast<Real>(i) / static_cast<Real>(num_points - 1);
        const Real x_value = range_.x_range().first +
            x_ratio * (range_.x_range().second - range_.x_range().first);

        Real y_value;
        evaluator_(function, x_value, y_value);

        samples.push_back(Point{.x = x_value, .y = y_value});
    }
    return samples;
}

std::vector<Point> FunctionSampler::sample_adaptive_points(
    const expressions::Expression& function,
    const std::vector<Point>& initial_samples) const {
    std::vector<Point> samples;
    // Heuristic estimate for the number of the final sampled points.
    // 3 is determined by experiments. Memory reallocation did not occur in
    // most cases in our experiments.
    const std::size_t num_reserved_points = initial_samples.size() * 3;
    samples.reserve(num_reserved_points);

    auto initial_sample_iter = initial_samples.begin();
    std::size_t left_index = 0;
    while (true) {
        // Insert points to provide three points if possible.
        while (initial_sample_iter != initial_samples.end() &&
            samples.size() < left_index + 3) {
            samples.push_back(*initial_sample_iter);
            ++initial_sample_iter;
        }
        const std::size_t num_points_from_here = samples.size() - left_index;
        if (num_points_from_here < 2) {
            // Finished sampling all segments.
            break;
        }
        // At least two points are available.

        bool is_divided = false;
        if (divide_segment_according_to_y_change(
                function, samples, left_index)) {
            is_divided = true;
        }
        if (num_points_from_here >= 3) {
            if (divide_segment_according_to_slope_change(
                    function, samples, left_index)) {
                is_divided = true;
            }
        }
        if (divide_segment_when_one_end_is_not_finite(
                function, samples, left_index)) {
            is_divided = true;
        }
        if (!is_divided) {
            ++left_index;
        }

        if (samples.size() >= config_.max_num_sample_points()) {
            // Reached the maximum number of sample points. Insert remaining
            // initial sample points and finish sampling.
            samples.insert(
                samples.end(), initial_sample_iter, initial_samples.end());
            break;
        }
    }
    return samples;
}

bool FunctionSampler::divide_segment_according_to_y_change(
    const expressions::Expression& function, std::vector<Point>& samples,
    std::size_t left_index) const {
    const auto& left_point = samples[left_index];
    const auto& right_point = samples[left_index + 1];
    const double y_diff = std::abs(right_point.y - left_point.y);
    const double y_range = range_.y_range().second - range_.y_range().first;
    const double y_diff_rate = y_diff / y_range;
    if (std::isfinite(y_diff_rate) &&
        y_diff_rate > config_.max_coordinate_change_rate()) {
        return divide_segment(function, samples, left_index);
    }
    return false;
}

bool FunctionSampler::divide_segment_according_to_slope_change(
    const expressions::Expression& function, std::vector<Point>& samples,
    std::size_t left_index) const {
    const auto& left_point = samples[left_index];
    const auto& mid_point = samples[left_index + 1];
    const auto& right_point = samples[left_index + 2];
    const double slope_normalization_coeff =
        (range_.x_range().second - range_.x_range().first) /
        (range_.y_range().second - range_.y_range().first);
    const double left_slope = slope_normalization_coeff *
        (mid_point.y - left_point.y) / (mid_point.x - left_point.x);
    const double right_slope = slope_normalization_coeff *
        (right_point.y - mid_point.y) / (right_point.x - mid_point.x);
    const double slope_diff = std::abs(right_slope - left_slope);
    if (std::isfinite(slope_diff) &&
        slope_diff > config_.slope_change_threshold()) {
        // Divide the right segment first to avoid the change of the index of
        // the right segment before dividing the right segment.
        const bool is_right_divided =
            divide_segment(function, samples, left_index + 1);
        const bool is_left_divided =
            divide_segment(function, samples, left_index);
        return is_left_divided || is_right_divided;
    }
    return false;
}

bool FunctionSampler::divide_segment_when_one_end_is_not_finite(
    const expressions::Expression& function, std::vector<Point>& samples,
    std::size_t left_index) const {
    const auto& left_point = samples[left_index];
    const auto& right_point = samples[left_index + 1];
    const bool is_left_finite = std::isfinite(left_point.y);
    const bool is_right_finite = std::isfinite(right_point.y);
    if ((is_left_finite && is_right_finite) ||
        (!is_left_finite && !is_right_finite)) {
        return false;
    }
    return divide_segment(function, samples, left_index);
}

bool FunctionSampler::divide_segment(const expressions::Expression& function,
    std::vector<Point>& samples, std::size_t left_index) const {
    const std::size_t right_index = left_index + 1;
    const Point& left_point = samples[left_index];
    const Point& right_point = samples[right_index];
    if (is_sampling_should_be_skipped(left_point, right_point)) {
        return false;
    }
    const Point mid_point =
        sample_additional_point(function, left_point, right_point);
    samples.insert(
        samples.begin() + static_cast<std::ptrdiff_t>(right_index), mid_point);
    return true;
}

Point FunctionSampler::sample_additional_point(
    const expressions::Expression& function, const Point& left_point,
    const Point& right_point) const {
    Point mid_point{};
    mid_point.x = 0.5 * (left_point.x + right_point.x);
    evaluator_(function, mid_point.x, mid_point.y);
    return mid_point;
}

bool FunctionSampler::is_sampling_should_be_skipped(
    const Point& left_point, const Point& right_point) const {
    if (!range_.contains(left_point) && !range_.contains(right_point)) {
        // Both points are outside the range, so this segment may outside the
        // range or has a singularity.
        return true;
    }

    const double x_diff = std::abs(right_point.x - left_point.x);
    const double x_range = range_.x_range().second - range_.x_range().first;
    const double x_diff_rate = x_diff / x_range;
    if (x_diff_rate < config_.min_param_change_rate()) {
        // The change in the parameter is already small enough, this segment may
        // contain a discontinuity or a singularity.
        return true;  // NOLINT(readability-simplify-boolean-expr): for readability.
    }

    return false;
}

}  // namespace func_sketch::plotter
