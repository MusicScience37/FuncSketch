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
 * \brief Definition of AxisTicks class.
 */
#pragma once

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "func_sketch/common_types.h"

namespace func_sketch::plotter {

/*!
 * \brief Struct to represent ticks of axes.
 */
struct AxisTicks {
    //! Tick values in real numbers.
    std::vector<Real> values;

    //! Tick strings.
    std::vector<std::string> strings;
};

/*!
 * \brief Generate ticks of axes.
 *
 * \param[in] range Range of the axis. Pair of minimum and maximum values.
 * \param[in] approx_num_ticks Desired number of ticks. Approximately this
 * number of ticks will be generated.
 * \param[out] ticks Ticks of the axis.
 */
void generate_axis_ticks(const std::pair<Real, Real>& range,
    std::size_t approx_num_ticks, AxisTicks& ticks);

}  // namespace func_sketch::plotter
