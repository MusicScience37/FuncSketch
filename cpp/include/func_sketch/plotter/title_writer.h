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
 * \brief Definition of TitleWriter class.
 */
#pragma once

#include "func_sketch/plotter/image.h"
#include "func_sketch/plotter/margin.h"
#include "func_sketch/plotter/plot_config.h"
#include "func_sketch/plotter/text_renderer.h"

namespace func_sketch::plotter {

/*!
 * \brief Class to write plot titles.
 */
class TitleWriter {
public:
    /*!
     * \brief Add margins required for the title of the plot.
     *
     * \param[in,out] plot_region_margin Margin of the plot region.
     * \param[in] config Configuration of plots.
     */
    void prepare(Margin& plot_region_margin, const PlotConfig& config);

    /*!
     * \brief Write the title of the plot.
     *
     * \param[in,out] image Image to write.
     * \param[in] plot_region_margin Margin of the plot region.
     * \param[in] config Configuration of plots.
     */
    void write(Image& image, const Margin& plot_region_margin,
        const PlotConfig& config);

private:
    /*!
     * \brief Calculate the height of the title of the plot.
     *
     * \param[in] config Configuration of plots.
     * \return Height of the title of the plot.
     *
     * \note This function assumes that the title of the plot is present.
     */
    [[nodiscard]] int plot_title_height(const PlotConfig& config);

    //! Text renderer.
    TextRenderer text_renderer_;
};

}  // namespace func_sketch::plotter
