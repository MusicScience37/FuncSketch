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
 * \brief Definition of PlotConfig class.
 */
#pragma once

#include "func_sketch/plotter/axes_config.h"
#include "func_sketch/plotter/grid_config.h"
#include "func_sketch/plotter/margin.h"
#include "func_sketch/plotter/rgb_color.h"
#include "func_sketch/plotter/sampling_config.h"

namespace func_sketch::plotter {

// TODO Tune these values

//! Default line width of curves in pixels.
constexpr int default_curve_line_width = 1;

//! Default color of background.
constexpr auto default_background_color =
    RGBColor{.r = 255, .g = 255, .b = 255};

/*!
 * \brief Class of configurations of a plot.
 */
class PlotConfig {
public:
    /*!
     * \brief Constructor.
     */
    PlotConfig() = default;

    /*!
     * \brief Access the configuration of margins.
     *
     * \return Reference to the configuration of margins.
     */
    [[nodiscard]] Margin& margin() noexcept;

    /*!
     * \brief Get the configuration of margins.
     *
     * \return Reference to the configuration of margins.
     */
    [[nodiscard]] const Margin& margin() const noexcept;

    /*!
     * \brief Access the configuration of axes.
     *
     * \return Reference to the configuration of axes.
     */
    [[nodiscard]] AxesConfig& axes() noexcept;

    /*!
     * \brief Get the configuration of axes.
     *
     * \return Reference to the configuration of axes.
     */
    [[nodiscard]] const AxesConfig& axes() const noexcept;

    /*!
     * \brief Access the configuration of the grid.
     *
     * \return Reference to the configuration of the grid.
     */
    [[nodiscard]] GridConfig& grid() noexcept;

    /*!
     * \brief Get the configuration of the grid.
     *
     * \return Reference to the configuration of the grid.
     */
    [[nodiscard]] const GridConfig& grid() const noexcept;

    /*!
     * \brief Access the configuration of sampling.
     *
     * \return Reference to the configuration of sampling.
     */
    [[nodiscard]] SamplingConfig& sampling() noexcept;

    /*!
     * \brief Get the configuration of sampling.
     *
     * \return Reference to the configuration of sampling.
     */
    [[nodiscard]] const SamplingConfig& sampling() const noexcept;

    /*!
     * \brief Set the line width of curves in pixels.
     *
     * \param[in] value Line width of curves in pixels.
     * \return Reference to this object.
     */
    PlotConfig& curve_line_width(int value);

    /*!
     * \brief Set the color of background.
     *
     * \param[in] value Color of background.
     * \return Reference to this object.
     */
    PlotConfig& background_color(const RGBColor& value);

    /*!
     * \brief Get the line width of curves in pixels.
     *
     * \return Line width of curves in pixels.
     */
    [[nodiscard]] int curve_line_width() const noexcept;

    /*!
     * \brief Get the color of background.
     *
     * \return Color of background.
     */
    [[nodiscard]] const RGBColor& background_color() const noexcept;

private:
    //! Configuration of margins.
    Margin margin_;

    //! Configuration of axes.
    AxesConfig axes_;

    //! Configuration of the grid.
    GridConfig grid_;

    //! Configuration of sampling.
    SamplingConfig sampling_;

    //! Line width of curves in pixels.
    int curve_line_width_{default_curve_line_width};

    //! Color of background.
    RGBColor background_color_{default_background_color};
};

}  // namespace func_sketch::plotter
