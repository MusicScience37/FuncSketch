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
 * \brief Definition of CurveWriter class.
 */
#pragma once

#include "func_sketch/plotter/image.h"
#include "func_sketch/plotter/plot_config.h"
#include "func_sketch/plotter/plot_range.h"
#include "func_sketch/plotter/point.h"
#include "func_sketch/plotter/point_converter.h"

namespace func_sketch::plotter {

/*!
 * \brief Class to write curves on plots.
 */
class CurveWriter {
public:
    /*!
     * \brief Write a curve.
     *
     * \param[in] samples Samples points of the curve.
     * \param[in] color Color of the curve.
     * \param[in,out] image Image to write.
     * \param[in] config Configuration of the plots.
     * \param[in] range Range of the plots.
     * \param[in] point_converter Point converter.
     */
    static void write_curve(const std::vector<Point>& samples,
        const RGBColor& color, Image& image, const PlotConfig& config,
        const PlotRange& range, const PointConverter& point_converter);
};

}  // namespace func_sketch::plotter
