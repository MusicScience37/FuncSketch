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
 * \brief Implementation of PointSampler class.
 */
#include "func_sketch/sampling/point_sampler.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <forward_list>
#include <iterator>
#include <limits>
#include <memory_resource>
#include <numbers>
#include <utility>

#include "func_sketch/plotter/plot_range.h"
#include "func_sketch/utilities/validate_bounds.h"

namespace func_sketch::sampling {

PointSampler::PointSampler(
    // NOLINTNEXTLINE(*-pass-by-value): Wrong warning for small objects.
    const plotter::PlotRange& range, const SamplingConfig& config)
    : range_(range), config_(config) {}

PointSampler& PointSampler::range(const plotter::PlotRange& value) {
    range_ = value;
    return *this;
}

PointSampler& PointSampler::config(const SamplingConfig& value) {
    config_ = value;
    return *this;
}

namespace {

/*!
 * \brief Determine the interval of initial sampling.
 *
 * \param[in] parameter_range Range of the parameter.
 * \param[in] num_points Number of points.
 * \return A pair of the mantissa and the exponent of the interval.
 */
[[nodiscard]] std::pair<Real, int> determine_initial_sample_interval(
    const std::pair<Real, Real>& parameter_range, std::size_t num_points) {
    const Real range_size = parameter_range.second - parameter_range.first;
    const Real approx_interval = range_size / static_cast<Real>(num_points - 1);
    auto interval_digits =
        static_cast<int>(std::floor(std::log10(approx_interval)));
    Real interval_number = approx_interval / std::pow(10.0, interval_digits);
    // Round down the interval to "nice numbers" (1, 2, 5, 10, ...).
    if (interval_number < 1.0) {
        interval_number = 5.0;
        --interval_digits;
    } else if (interval_number < 2.0) {
        interval_number = 1.0;
    } else if (interval_number < 5.0) {
        interval_number = 2.0;
    } else if (interval_number < 10.0) {
        interval_number = 5.0;
    } else {
        interval_number = 1.0;
        ++interval_digits;
    }
    return std::make_pair(interval_number, interval_digits);
}

/*!
 * \brief Fallback implementation for sampling initial points.
 *
 * \param[in] function Function to sample.
 * \param[in] parameter_range Range of the parameter.
 * \param[in] num_points Approximate number of points.
 * \param[out] samples List of sampled parameters and corresponding points.
 * \return Number of sampled points.
 */
[[nodiscard]] std::size_t sample_initial_points_fallback(
    const std::function<Point(Real)>& function,
    const std::pair<Real, Real>& parameter_range, std::size_t num_points,
    std::pmr::forward_list<std::pair<Real, Point>>& samples) {
    std::size_t actual_num_points = 0;
    auto iter = samples.before_begin();
    {
        // First point.
        const Real parameter = parameter_range.first;
        iter = samples.insert_after(
            iter, std::make_pair(parameter, function(parameter)));
        ++actual_num_points;
    }
    Real prev_parameter = parameter_range.first;
    for (std::size_t i = 1; i < num_points; ++i) {
        const Real ratio =
            static_cast<Real>(i) / static_cast<Real>(num_points - 1);
        const Real parameter = parameter_range.first +
            ratio * (parameter_range.second - parameter_range.first);
        if (parameter == prev_parameter) {
            // Skip the parameter if it exactly duplicates the previous one.
            continue;
        }
        iter = samples.insert_after(
            iter, std::make_pair(parameter, function(parameter)));
        prev_parameter = parameter;
        ++actual_num_points;
    }
    return actual_num_points;
}

/*!
 * \brief Sample initial points.
 *
 * \param[in] function Function to sample.
 * This function calculates a point for a parameter value.
 * \param[in] parameter_range Range of the parameter.
 * \param[in] num_points Approximate number of points.
 * \param[in] min_param_change_rate Minimum rate of parameter change.
 * \param[out] samples List of sampled parameters and corresponding points.
 * \return Number of sampled points.
 */
[[nodiscard]] std::size_t sample_initial_points(
    const std::function<Point(Real)>& function,
    const std::pair<Real, Real>& parameter_range, std::size_t num_points,
    Real min_param_change_rate,
    std::pmr::forward_list<std::pair<Real, Point>>& samples) {
    const auto [interval_number, interval_digits] =
        determine_initial_sample_interval(parameter_range, num_points);
    const Real interval_order = std::pow(10.0, interval_digits);

    // Exclude points too close to the end points
    // to prevent sampling the same point or points too close to each other.
    const Real min_param_change = min_param_change_rate *
        (parameter_range.second - parameter_range.first);
    const Real min_intermediate_param_index_real =
        std::floor((parameter_range.first + min_param_change) / interval_order /
            interval_number) +
        1.0;
    const Real max_intermediate_param_index_real =
        std::ceil((parameter_range.second - min_param_change) / interval_order /
            interval_number) -
        1.0;

    // Indices with large absolute values cause overflow in conversions to
    // integers and loss of precision in calculation of parameters.
    constexpr Real max_abs_index = 1e+10;
    // Negated comparisons are used to handle NaN values.
    if (!(std::abs(min_intermediate_param_index_real) <= max_abs_index) ||
        !(std::abs(max_intermediate_param_index_real) <= max_abs_index)) {
        return sample_initial_points_fallback(
            function, parameter_range, num_points, samples);
    }

    using IndexType = std::int64_t;
    const auto min_intermediate_param_index =
        static_cast<IndexType>(min_intermediate_param_index_real);
    const auto max_intermediate_param_index =
        static_cast<IndexType>(max_intermediate_param_index_real);

    std::size_t num_sampled_points = 0;
    auto iter = samples.before_begin();
    // Minimum parameter.
    {
        const Real parameter = parameter_range.first;
        iter = samples.insert_after(
            iter, std::make_pair(parameter, function(parameter)));
        ++num_sampled_points;
    }
    // Intermediate parameters.
    for (IndexType index = min_intermediate_param_index;
        index <= max_intermediate_param_index; ++index) {
        const Real parameter =
            static_cast<Real>(index) * interval_number * interval_order;
        iter = samples.insert_after(
            iter, std::make_pair(parameter, function(parameter)));
        ++num_sampled_points;
    }
    // Maximum parameter.
    {
        const Real parameter = parameter_range.second;
        iter = samples.insert_after(
            iter, std::make_pair(parameter, function(parameter)));
        ++num_sampled_points;
    }

    return num_sampled_points;
}

/*!
 * \brief Determine whether to divide a segment between two points.
 *
 * \param[in] cur_next_param_diff Difference in parameter between current and
 * next points.
 * \param[in] cur_next_point_diff Difference in point coordinates between
 * current and next points.
 * \param[in] is_cur_point_in_range Whether the current point is within the
 * range.
 * \param[in] is_next_point_in_range Whether the next point is within the range.
 * \param[in] param_diff_min Minimum difference in parameter.
 * \param[in] x_diff_max Maximum difference in x-coordinate.
 * \param[in] y_diff_max Maximum difference in y-coordinate.
 * \retval true The segment should be divided.
 * \retval false The segment should not be divided.
 */
[[nodiscard]] bool should_divide_two_points(Real cur_next_param_diff,
    const Point& cur_next_point_diff, bool is_cur_point_in_range,
    bool is_next_point_in_range, Real param_diff_min, Real x_diff_max,
    Real y_diff_max) {
    if (cur_next_param_diff < param_diff_min) {
        // The change in the parameter is already small enough, so this segment
        // may contain a discontinuity or a singularity.
        return false;
    }
    if (!is_cur_point_in_range && !is_next_point_in_range) {
        // Both points are outside the range, so this segment may be outside the
        // range or may contain a singularity.
        return false;
    }

    if (!is_cur_point_in_range || !is_next_point_in_range) {
        // Near the boundary of the range or a singularity.
        return true;
    }

    // Both points are within the range, so check the difference in coordinates.
    return (std::abs(cur_next_point_diff.x) > x_diff_max ||
        std::abs(cur_next_point_diff.y) > y_diff_max);
}

/*!
 * \brief Determine whether to divide the segments between three points.
 *
 * \param[in] left_param_diff Difference in parameter between the left and
 * center points.
 * \param[in] right_param_diff Difference in parameter between the center and
 * right points.
 * \param[in] left_point_diff Difference in point coordinates between the left
 * and center points.
 * \param[in] right_point_diff Difference in point coordinates between the
 * center and right points.
 * \param[in] is_left_point_in_range Whether the left point is within the range.
 * \param[in] is_center_point_in_range Whether the center point is within the
 * range.
 * \param[in] is_right_point_in_range Whether the right point is within the
 * range.
 * \param[in] param_diff_min Minimum difference in parameter.
 * \param[in] x_normalization_coeff Normalization coefficient for x-coordinate.
 * \param[in] y_normalization_coeff Normalization coefficient for y-coordinate.
 * \param[in] angle_change_cos_threshold Threshold of the cosine of the angle
 * change between the left and right segments.
 * \return A pair of booleans indicating whether to divide the left and right
 * segments, respectively.
 */
[[nodiscard]] std::pair<bool, bool> should_divide_three_points(
    Real left_param_diff, Real right_param_diff, const Point& left_point_diff,
    const Point& right_point_diff, bool is_left_point_in_range,
    bool is_center_point_in_range, bool is_right_point_in_range,
    Real param_diff_min, Real x_normalization_coeff, Real y_normalization_coeff,
    Real angle_change_cos_threshold) {
    if (!std::isfinite(left_point_diff.x) ||
        !std::isfinite(left_point_diff.y) ||
        !std::isfinite(right_point_diff.x) ||
        !std::isfinite(right_point_diff.y)) {
        // In this case, skip the check of angle changes.
        return {false, false};
    }

    const Point left_normalized_diff{
        .x = left_point_diff.x * x_normalization_coeff,
        .y = left_point_diff.y * y_normalization_coeff};
    const Point right_normalized_diff{
        .x = right_point_diff.x * x_normalization_coeff,
        .y = right_point_diff.y * y_normalization_coeff};
    const Real left_squared_distance =
        left_normalized_diff.x * left_normalized_diff.x +
        left_normalized_diff.y * left_normalized_diff.y;
    const Real right_squared_distance =
        right_normalized_diff.x * right_normalized_diff.x +
        right_normalized_diff.y * right_normalized_diff.y;
    const Real diff_dot_product =
        left_normalized_diff.x * right_normalized_diff.x +
        left_normalized_diff.y * right_normalized_diff.y;
    const bool has_large_angle_change =
        diff_dot_product < angle_change_cos_threshold *
            std::sqrt(left_squared_distance * right_squared_distance);

    bool should_divide_left = has_large_angle_change;
    if (left_param_diff < param_diff_min) {
        // The change in the parameter is already small enough, so this segment
        // may contain a discontinuity or a singularity.
        should_divide_left = false;
    }
    if (!is_left_point_in_range && !is_center_point_in_range) {
        // Both points are outside the range, so this segment may be outside the
        // range or may contain a singularity.
        should_divide_left = false;
    }

    bool should_divide_right = has_large_angle_change;
    if (right_param_diff < param_diff_min) {
        // The change in the parameter is already small enough, so this segment
        // may contain a discontinuity or a singularity.
        should_divide_right = false;
    }
    if (!is_center_point_in_range && !is_right_point_in_range) {
        // Both points are outside the range, so this segment may be outside the
        // range or may contain a singularity.
        should_divide_right = false;
    }

    return {should_divide_left, should_divide_right};
}

/*!
 * \brief Divide a segment.
 *
 * \param[in,out] samples List of sampled parameters and corresponding points.
 * \param[in] left_iter Iterator to the left point of the segment.
 * \param[in] left_param Parameter value of the left point.
 * \param[in] right_param Parameter value of the right point.
 * \param[in] function Function to calculate a point for a given parameter
 * value.
 */
void divide_segment(std::pmr::forward_list<std::pair<Real, Point>>& samples,
    std::pmr::forward_list<std::pair<Real, Point>>::const_iterator left_iter,
    Real left_param, Real right_param,
    const std::function<Point(Real)>& function) {
    const Real mid_param = 0.5 * (left_param + right_param);
    const Point mid_point = function(mid_param);
    samples.insert_after(left_iter, std::make_pair(mid_param, mid_point));
}

/*!
 * \brief Add points adaptively.
 *
 * \param[in] function Function to sample.
 * This function calculates a point for a parameter value.
 * \param[in] config Configuration of sampling.
 * \param[in] parameter_range Range of the parameter.
 * \param[in] range Range of the plot.
 * \param[in] initial_num_points Number of initially sampled points.
 * \param[in,out] samples List of sampled parameters and corresponding points.
 * \return Number of points after adaptive addition.
 */
[[nodiscard]] std::size_t add_points_adaptively(
    const std::function<Point(Real)>& function, const SamplingConfig& config,
    const std::pair<Real, Real>& parameter_range,
    const plotter::PlotRange& range, std::size_t initial_num_points,
    std::pmr::forward_list<std::pair<Real, Point>>& samples) {
    const Real param_range_size =
        parameter_range.second - parameter_range.first;
    const Real x_range_size = range.x_range().second - range.x_range().first;
    const Real y_range_size = range.y_range().second - range.y_range().first;

    const Real param_diff_min_from_change_rate =
        param_range_size * config.min_param_change_rate();
    constexpr Real weak_epsilon = 100 * std::numeric_limits<Real>::epsilon();
    const Real param_diff_min_from_weak_epsilon =
        std::max(
            std::abs(parameter_range.first), std::abs(parameter_range.second)) *
        weak_epsilon;
    const Real param_diff_min = std::max(
        param_diff_min_from_change_rate, param_diff_min_from_weak_epsilon);

    const Real x_diff_max = x_range_size * config.max_coordinate_change_rate();
    const Real y_diff_max = y_range_size * config.max_coordinate_change_rate();

    const Real x_normalization_coeff = 1.0 / x_range_size;
    const Real y_normalization_coeff = 1.0 / y_range_size;

    const Real angle_change_cos_threshold = std::cos(
        config.max_angle_change_degrees() * (std::numbers::pi / 180.0));

    // std::forward_list does not have a size() method, so manual calculation is
    // required.
    std::size_t num_points = initial_num_points;
    auto cur_iter = samples.begin();
    while (cur_iter != samples.end() &&
        num_points <= config.max_num_sample_points()) {
        const auto next_iter = std::next(cur_iter);
        if (next_iter == samples.end()) {
            break;
        }

        const auto& [cur_param, cur_point] = *cur_iter;
        const auto& [next_param, next_point] = *next_iter;
        const Real cur_next_param_diff = next_param - cur_param;
        const Point cur_next_point_diff = next_point - cur_point;
        const bool is_cur_point_in_range = range.contains(cur_point);
        const bool is_next_point_in_range = range.contains(next_point);
        if (should_divide_two_points(cur_next_param_diff, cur_next_point_diff,
                is_cur_point_in_range, is_next_point_in_range, param_diff_min,
                x_diff_max, y_diff_max)) {
            divide_segment(samples, cur_iter, cur_param, next_param, function);
            ++num_points;
        } else {
            const auto next_next_iter = std::next(next_iter);
            if (next_next_iter != samples.end()) {
                const auto& [next_next_param, next_next_point] =
                    *next_next_iter;
                const Real extra_param_diff = next_next_param - next_param;
                const Point extra_point_diff = next_next_point - next_point;
                const bool is_next_next_point_in_range =
                    range.contains(next_next_point);
                const auto [should_divide_left, should_divide_right] =
                    should_divide_three_points(cur_next_param_diff,
                        extra_param_diff, cur_next_point_diff, extra_point_diff,
                        is_cur_point_in_range, is_next_point_in_range,
                        is_next_next_point_in_range, param_diff_min,
                        x_normalization_coeff, y_normalization_coeff,
                        angle_change_cos_threshold);
                if (should_divide_left) {
                    divide_segment(
                        samples, cur_iter, cur_param, next_param, function);
                    ++num_points;
                }
                if (should_divide_right) {
                    divide_segment(samples, next_iter, next_param,
                        next_next_param, function);
                    ++num_points;
                }
                if (!should_divide_left && !should_divide_right) {
                    ++cur_iter;
                }
            } else {
                ++cur_iter;
            }
        }
    }

    return num_points;
}

}  // namespace

std::vector<Point> PointSampler::operator()(
    const std::function<Point(Real)>& function,
    const std::pair<Real, Real>& parameter_range) const {
    utilities::validate_bounds(parameter_range, "parameter");

    constexpr std::size_t static_buffer_size = 65536;
    // NOLINTNEXTLINE(*-member-init): Raw buffer is sufficient here.
    std::array<char, static_buffer_size> static_buffer;
    std::pmr::monotonic_buffer_resource resource(
        static_buffer.data(), static_buffer.size());
    std::pmr::forward_list<std::pair<Real, Point>> samples(&resource);

    const std::size_t initial_num_samples =
        sample_initial_points(function, parameter_range,
            std::min(config_.initial_num_sample_points(),
                config_.max_num_sample_points()),
            config_.min_param_change_rate(), samples);

    const std::size_t num_samples = add_points_adaptively(function, config_,
        parameter_range, range_, initial_num_samples, samples);

    std::vector<Point> result;
    result.reserve(num_samples);
    std::ranges::transform(samples, std::back_inserter(result),
        [](const std::pair<Real, Point>& sample) { return sample.second; });
    return result;
}

}  // namespace func_sketch::sampling
