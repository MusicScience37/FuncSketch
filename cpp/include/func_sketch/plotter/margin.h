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
 * \brief Definition of Margin class.
 */
#pragma once

namespace func_sketch::plotter {

//! Default margin in pixels.
constexpr int default_margin = 0;

/*!
 * \brief Class to save margins of plots.
 */
class Margin {
public:
    /*!
     * \brief Constructor.
     */
    Margin() = default;

    /*!
     * \brief Constructor.
     *
     * \param[in] left Left margin of plots in pixels.
     * \param[in] right Right margin of plots in pixels.
     * \param[in] top Top margin of plots in pixels.
     * \param[in] bottom Bottom margin of plots in pixels.
     */
    Margin(int left, int right, int top, int bottom);

    /*!
     * \brief Set the left margin of plots in pixels.
     *
     * \param[in] value Left margin of plots in pixels.
     * \return Reference to this object.
     */
    Margin& left(int value);

    /*!
     * \brief Set the right margin of plots in pixels.
     *
     * \param[in] value Right margin of plots in pixels.
     * \return Reference to this object.
     */
    Margin& right(int value);

    /*!
     * \brief Set the top margin of plots in pixels.
     *
     * \param[in] value Top margin of plots in pixels.
     * \return Reference to this object.
     */
    Margin& top(int value);

    /*!
     * \brief Set the bottom margin of plots in pixels.
     *
     * \param[in] value Bottom margin of plots in pixels.
     * \return Reference to this object.
     */
    Margin& bottom(int value);

    /*!
     * \brief Get the left margin of plots in pixels.
     *
     * \return Left margin of plots in pixels.
     */
    [[nodiscard]] int left() const noexcept;

    /*!
     * \brief Get the right margin of plots in pixels.
     *
     * \return Right margin of plots in pixels.
     */
    [[nodiscard]] int right() const noexcept;

    /*!
     * \brief Get the top margin of plots in pixels.
     *
     * \return Top margin of plots in pixels.
     */
    [[nodiscard]] int top() const noexcept;

    /*!
     * \brief Get the bottom margin of plots in pixels.
     *
     * \return Bottom margin of plots in pixels.
     */
    [[nodiscard]] int bottom() const noexcept;

    /*!
     * \brief Expand this margin so that each side is at least as large as
     * the corresponding side of another margin.
     *
     * \param[in] min_margin Margin to use as the lower bound of each side.
     * \return Reference to this object.
     */
    Margin& expand_to_at_least(const Margin& min_margin);

private:
    //! Left margin of plots in pixels.
    int left_{default_margin};

    //! Right margin of plots in pixels.
    int right_{default_margin};

    //! Top margin of plots in pixels.
    int top_{default_margin};

    //! Bottom margin of plots in pixels.
    int bottom_{default_margin};
};

}  // namespace func_sketch::plotter
