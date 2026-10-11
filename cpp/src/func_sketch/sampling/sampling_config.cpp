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
 * \brief Implementation of SamplingConfig class.
 */
#include "func_sketch/sampling/sampling_config.h"

#include <cmath>

#include <fmt/format.h>

#include "func_sketch/exceptions.h"

namespace func_sketch::sampling {

SamplingConfig& SamplingConfig::initial_num_sample_points(std::size_t value) {
    if (value < 2) {
        throw InvalidArgumentException(
            "Number of sample points must be at least 2");
    }
    initial_num_sample_points_ = value;
    return *this;
}

SamplingConfig& SamplingConfig::max_num_sample_points(std::size_t value) {
    if (value < 2) {
        throw InvalidArgumentException(
            "Number of sample points must be at least 2.");
    }
    if (value > max_max_num_sample_points) {
        throw InvalidArgumentException(
            fmt::format("Number of sample points must be at most {}",
                max_max_num_sample_points));
    }
    max_num_sample_points_ = value;
    return *this;
}

SamplingConfig& SamplingConfig::max_coordinate_change_rate(double value) {
    if (value <= 0.0) {
        throw InvalidArgumentException(
            "Maximum coordinate change rate must be positive.");
    }
    max_coordinate_change_rate_ = value;
    return *this;
}

SamplingConfig& SamplingConfig::max_angle_change_degrees(double value) {
    if (!std::isfinite(value) || 0.0 >= value || value >= 180.0) {
        throw InvalidArgumentException(
            "Maximum angle change must be in the range (0, 180) degrees.");
    }
    max_angle_change_degrees_ = value;
    return *this;
}

SamplingConfig& SamplingConfig::min_param_change_rate(double value) {
    if (value < min_min_param_change_rate) {
        throw InvalidArgumentException(
            fmt::format("Minimum parameter change rate must be at least {}",
                min_min_param_change_rate));
    }
    min_param_change_rate_ = value;
    return *this;
}

std::size_t SamplingConfig::initial_num_sample_points() const noexcept {
    return initial_num_sample_points_;
}

std::size_t SamplingConfig::max_num_sample_points() const noexcept {
    return max_num_sample_points_;
}

double SamplingConfig::max_coordinate_change_rate() const noexcept {
    return max_coordinate_change_rate_;
}

double SamplingConfig::max_angle_change_degrees() const noexcept {
    return max_angle_change_degrees_;
}

double SamplingConfig::min_param_change_rate() const noexcept {
    return min_param_change_rate_;
}

}  // namespace func_sketch::sampling
