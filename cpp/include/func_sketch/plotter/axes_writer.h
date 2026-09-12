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
 * \brief Definition of AxesWriter class.
 */
#pragma once

#include "func_sketch/plotter/axis_ticks.h"
#include "func_sketch/plotter/image.h"
#include "func_sketch/plotter/margin.h"
#include "func_sketch/plotter/plot_config.h"
#include "func_sketch/plotter/plot_range.h"
#include "func_sketch/plotter/point_converter.h"
#include "func_sketch/plotter/text_renderer.h"

namespace func_sketch::plotter {

/*!
 * \brief Class to write axes in plots.
 */
class AxesWriter {
public:
    /*!
     * \brief Calculate the internal parameters and add margins required for
     * axes.
     *
     * \param[in,out] plot_region_margin Margin of the plot region.
     * \param[in] config Configuration of plots.
     * \param[in] range Range of plots.
     * \param[in] height Height of the plot region.
     * \param[in] width Width of the plot region.
     */
    void prepare(Margin& plot_region_margin, const PlotConfig& config,
        const PlotRange& range, int height, int width);

    /*!
     * \brief Write axes in plots.
     *
     * \param[in,out] image Image to write.
     * \param[in] config Configuration of plots.
     * \param[in] range Range of plots.
     * \param[in] point_converter Point converter.
     */
    void write(Image& image, const PlotConfig& config, const PlotRange& range,
        const PointConverter& point_converter);

private:
    /*!
     * \brief Write grid lines of plots.
     *
     * \param[in,out] image Image to write.
     * \param[in] config Configuration of plots.
     * \param[in] range Range of plots.
     * \param[in] point_converter Point converter.
     */
    void write_grid_lines(Image& image, const PlotConfig& config,
        const PlotRange& range, const PointConverter& point_converter) const;

    /*!
     * \brief Write x axis.
     *
     * \param[in,out] image Image to write.
     * \param[in] config Configuration of plots.
     * \param[in] range Range of plots.
     * \param[in] point_converter Point converter.
     */
    void write_x_axis(Image& image, const PlotConfig& config,
        const PlotRange& range, const PointConverter& point_converter);

    /*!
     * \brief Write y axis.
     *
     * \param[in,out] image Image to write.
     * \param[in] config Configuration of plots.
     * \param[in] range Range of plots.
     * \param[in] point_converter Point converter.
     */
    void write_y_axis(Image& image, const PlotConfig& config,
        const PlotRange& range, const PointConverter& point_converter);

    /*!
     * \brief Update axis ticks.
     *
     * \param[in] plot_region_margin Margin of the plot region.
     * \param[in] config Configuration of plots.
     * \param[in] range Range of plots.
     * \param[in] height Height of the plot region.
     * \param[in] width Width of the plot region.
     */
    void update_axis_ticks(const Margin& plot_region_margin,
        const PlotConfig& config, const PlotRange& range, int height,
        int width);

    /*!
     * \brief Update the height of x-axis ticks.
     *
     * \param[in] config Configuration of plots.
     */
    void update_x_axis_tick_height(const PlotConfig& config);

    /*!
     * \brief Update the width of y-axis ticks.
     *
     * \param[in] config Configuration of plots.
     */
    void update_y_axis_tick_width(const PlotConfig& config);

    /*!
     * \brief Calculate the height of x-axis title.
     *
     * \param[in] config Configuration of plots.
     * \return Height of the x-axis title.
     *
     * \note This function assumes that the x-axis title is present.
     */
    [[nodiscard]] int x_axis_title_height(const PlotConfig& config);

    /*!
     * \brief Calculate the width of y-axis title.
     *
     * \param[in] config Configuration of plots.
     * \return Width of the y-axis title.
     *
     * \note This function assumes that the y-axis title is present.
     */
    [[nodiscard]] int y_axis_title_width(const PlotConfig& config);

    //! Ticks of the x-axis.
    AxisTicks x_axis_ticks_;

    //! Ticks of the y-axis.
    AxisTicks y_axis_ticks_;

    //! Height of x-axis ticks.
    int x_axis_tick_height_{};

    //! Width of y-axis ticks.
    int y_axis_tick_width_{};

    //! Text renderer.
    TextRenderer text_renderer_;
};

}  // namespace func_sketch::plotter
