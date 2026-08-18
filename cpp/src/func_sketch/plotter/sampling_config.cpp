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
#include "func_sketch/plotter/sampling_config.h"

#include <fmt/format.h>

#include "func_sketch/exceptions.h"

namespace func_sketch::plotter {

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

SamplingConfig& SamplingConfig::slope_change_threshold(double value) {
    if (value <= 0.0) {
        throw InvalidArgumentException(
            "Slope change threshold must be positive.");
    }
    slope_change_threshold_ = value;
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

double SamplingConfig::slope_change_threshold() const noexcept {
    return slope_change_threshold_;
}

double SamplingConfig::min_param_change_rate() const noexcept {
    return min_param_change_rate_;
}

}  // namespace func_sketch::plotter
