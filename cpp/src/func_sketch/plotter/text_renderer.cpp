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
 * \brief Implementation of TextRenderer class.
 */
#include "func_sketch/plotter/text_renderer.h"

#include <opencv2/imgproc.hpp>

namespace func_sketch::plotter {

namespace {

//! Font face used for texts in plots.
constexpr int font_face = cv::FONT_HERSHEY_SIMPLEX;

//! Thickness of texts in plots.
constexpr int thickness = 1;

}  // namespace

void TextRenderer::font_size(int value) {
    font_size_ = value;
    font_scale_ = cv::getFontScaleFromHeight(font_face, value);
}

std::pair<int, int> TextRenderer::text_size(const std::string& text) const {
    const cv::Size size =
        cv::getTextSize(text, font_face, font_scale_, thickness, nullptr);
    return {size.height, size.width};
}

void TextRenderer::render_text(Image& image, const std::string& text,
    const cv::Point& top_left_position, const cv::Scalar& color) const {
    cv::putText(image, text, top_left_position, font_face, font_scale_, color,
        thickness, cv::LINE_AA);
}

}  // namespace func_sketch::plotter
