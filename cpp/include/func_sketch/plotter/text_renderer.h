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
 * \brief Definition of TextRenderer class.
 */
#pragma once

#include <opencv2/core.hpp>

#include "func_sketch/plotter/image.h"

namespace func_sketch::plotter {

/*!
 * \brief Class to render texts on images.
 */
class TextRenderer {
public:
    /*!
     * \brief Constructor.
     */
    TextRenderer() = default;

    /*!
     * \brief Set the font size.
     *
     * \param[in] value Font size.
     */
    void font_size(int value);

    /*!
     * \brief Get the size of a text.
     *
     * \param[in] text Text.
     * \return Height and width of the text.
     *
     * \note Call font_size() before calling this function.
     * Otherwise the behavior is undefined.
     */
    [[nodiscard]] std::pair<int, int> text_size(const std::string& text) const;

    /*!
     * \brief Render a text.
     *
     * \param[out] image Image to render on.
     * \param[in] text Text to render.
     * \param[in] top_left_position Top-left position to render the text.
     * \param[in] color Color of the text.
     *
     * \note Call font_size() before calling this function.
     * Otherwise the behavior is undefined.
     */
    void render_text(Image& image, const std::string& text,
        const cv::Point& top_left_position, const cv::Scalar& color) const;

private:
    //! Font size.
    int font_size_{};

    //! Font scale.
    double font_scale_{};
};

}  // namespace func_sketch::plotter
