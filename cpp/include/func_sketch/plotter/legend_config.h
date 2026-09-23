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
 * \brief Definition of LegendConfig class.
 */
#pragma once

#include <string>
#include <string_view>

namespace func_sketch::plotter {

//! Default value of whether the legend is visible.
constexpr bool default_legend_visible = true;

//! Default title of the legend (empty string specifies no title).
constexpr std::string_view default_legend_title;

//! Default font size of the title of the legend in pixels.
constexpr int default_legend_title_font_size = 11;

//! Default font size of curve names in the legend in pixels.
constexpr int default_legend_curve_name_font_size = 11;

//! Default vertical spacing between legend entries in pixels.
constexpr int default_legend_entry_spacing =
    default_legend_curve_name_font_size;  // TODO Tune this value after
                                          // plotting.

//! Default margin between the legend and the plot area in pixels.
constexpr int default_legend_margin =
    default_legend_curve_name_font_size;  // TODO Tune this value after
                                          // plotting.

//! Default length in pixels of the line representing a curve in the legend.
constexpr int default_legend_curve_line_length =
    20;  // TODO Tune this value after plotting.

//! Default spacing in pixels between the line representing a curve and the
//! curve name in the legend.
constexpr int default_legend_curve_line_name_spacing =
    8;  // TODO Tune this value after plotting.

/*!
 * \brief Class of configurations of legends.
 */
class LegendConfig {
public:
    /*!
     * \brief Constructor.
     */
    LegendConfig() = default;

    /*!
     * \brief Set whether the legend is visible.
     *
     * \param[in] value Whether the legend is visible.
     * \return Reference to this object.
     */
    LegendConfig& visible(bool value) noexcept;

    /*!
     * \brief Set the title of the legend.
     *
     * \param[in] value Title of the legend.
     * \return Reference to this object.
     *
     * \note Empty string means no title.
     */
    LegendConfig& title(std::string value);

    /*!
     * \brief Set the font size of the title of the legend in pixels.
     *
     * \param[in] value Font size of the title of the legend in pixels.
     * \return Reference to this object.
     */
    LegendConfig& title_font_size(int value);

    /*!
     * \brief Set the font size of curve names in the legend in pixels.
     *
     * \param[in] value Font size of curve names in the legend in pixels.
     * \return Reference to this object.
     */
    LegendConfig& curve_name_font_size(int value);

    /*!
     * \brief Set the vertical spacing between legend entries in pixels.
     *
     * \param[in] value Vertical spacing between legend entries in pixels.
     * \return Reference to this object.
     */
    LegendConfig& entry_spacing(int value);

    /*!
     * \brief Set the margin between the legend and the plot area in pixels.
     *
     * \param[in] value Margin between the legend and the plot area in pixels.
     * \return Reference to this object.
     */
    LegendConfig& margin(int value);

    /*!
     * \brief Set the length in pixels of the line representing a curve in the
     * legend.
     *
     * \param[in] value Length in pixels of the line representing a curve in
     * the legend.
     * \return Reference to this object.
     */
    LegendConfig& curve_line_length(int value);

    /*!
     * \brief Set the spacing in pixels between the line representing a curve
     * and the curve name in the legend.
     *
     * \param[in] value Spacing in pixels between the line representing a curve
     * and the curve name in the legend.
     * \return Reference to this object.
     */
    LegendConfig& curve_line_name_spacing(int value);

    /*!
     * \brief Get whether the legend is visible.
     *
     * \return Whether the legend is visible.
     */
    [[nodiscard]] bool visible() const noexcept;

    /*!
     * \brief Get the title of the legend.
     *
     * \return Title of the legend.
     *
     * \note Empty string means no title.
     */
    [[nodiscard]] const std::string& title() const noexcept;

    /*!
     * \brief Get the font size of the title of the legend in pixels.
     *
     * \return Font size of the title of the legend in pixels.
     */
    [[nodiscard]] int title_font_size() const noexcept;

    /*!
     * \brief Get the font size of curve names in the legend in pixels.
     *
     * \return Font size of curve names in the legend in pixels.
     */
    [[nodiscard]] int curve_name_font_size() const noexcept;

    /*!
     * \brief Get the vertical spacing between legend entries in pixels.
     *
     * \return Vertical spacing between legend entries in pixels.
     */
    [[nodiscard]] int entry_spacing() const noexcept;

    /*!
     * \brief Get the margin between the legend and the plot area in pixels.
     *
     * \return Margin between the legend and the plot area in pixels.
     */
    [[nodiscard]] int margin() const noexcept;

    /*!
     * \brief Get the length in pixels of the line representing a curve in the
     * legend.
     *
     * \return Length in pixels of the line representing a curve in the legend.
     */
    [[nodiscard]] int curve_line_length() const noexcept;

    /*!
     * \brief Get the spacing in pixels between the line representing a curve
     * and the curve name in the legend.
     *
     * \return Spacing in pixels between the line representing a curve and the
     * curve name in the legend.
     */
    [[nodiscard]] int curve_line_name_spacing() const noexcept;

private:
    //! Whether the legend is visible.
    bool visible_{default_legend_visible};

    //! Title of the legend.
    std::string title_{default_legend_title};

    //! Font size of the title of the legend in pixels.
    int title_font_size_{default_legend_title_font_size};

    //! Font size of curve names in the legend in pixels.
    int curve_name_font_size_{default_legend_curve_name_font_size};

    //! Vertical spacing between legend entries in pixels.
    int entry_spacing_{default_legend_entry_spacing};

    //! Margin between the legend and the plot area in pixels.
    int margin_{default_legend_margin};

    //! Length in pixels of the line representing a curve in the legend.
    int curve_line_length_{default_legend_curve_line_length};

    //! Spacing in pixels between the line representing a curve and the curve
    //! name in the legend.
    int curve_line_name_spacing_{default_legend_curve_line_name_spacing};
};

}  // namespace func_sketch::plotter
