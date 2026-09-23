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
 * \brief Definition of LegendWriter class.
 */
#pragma once

#include <string>
#include <utility>
#include <vector>

#include "func_sketch/plotter/image.h"
#include "func_sketch/plotter/margin.h"
#include "func_sketch/plotter/plot_config.h"
#include "func_sketch/plotter/rgb_color.h"
#include "func_sketch/plotter/text_renderer.h"

namespace func_sketch::plotter {

/*!
 * \brief Class to write legends in plots.
 */
class LegendWriter {
public:
    /*!
     * \brief Set the legend entries.
     *
     * \param[in] entries Legend entries.
     */
    void legend_entries(
        const std::vector<std::pair<std::string, RGBColor>>& entries);

    /*!
     * \brief Calculate the internal parameters and add margins required for
     * the legend.
     *
     * \param[in,out] plot_region_margin Margin of the plot region.
     * \param[in] config Configuration of plots.
     * \return Height of the space for the legend.
     */
    [[nodiscard]] int prepare(
        Margin& plot_region_margin, const PlotConfig& config);

    /*!
     * \brief Write the legend in the plot.
     *
     * \param[in,out] image Image to write.
     * \param[in] config Configuration of plots.
     * \param[in] plot_region_margin Margin of the plot region.
     */
    void write(Image& image, const PlotConfig& config,
        const Margin& plot_region_margin);

private:
    //! Legend entries.
    std::vector<std::pair<std::string, RGBColor>> legend_entries_;

    //! Text renderer.
    TextRenderer text_renderer_;
};

}  // namespace func_sketch::plotter
