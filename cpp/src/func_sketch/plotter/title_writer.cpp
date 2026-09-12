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
 * \brief Implementation of TitleWriter class.
 */
#include "func_sketch/plotter/title_writer.h"

#include <opencv2/core.hpp>

#include "func_sketch/plotter/plotting_util.h"

namespace func_sketch::plotter {

void TitleWriter::prepare(
    Margin& plot_region_margin, const PlotConfig& config) {
    if (!config.plot_title().empty()) {
        const int additional_margin =
            plot_title_height(config) + config.plot_title_margin();
        plot_region_margin.top(plot_region_margin.top() + additional_margin);
    }
}

void TitleWriter::write(
    Image& image, const Margin& plot_region_margin, const PlotConfig& config) {
    if (config.plot_title().empty()) {
        return;
    }
    const auto size = image.size;
    const auto color = convert_color(config.plot_title_color());

    const auto& text = config.plot_title();
    const int font_size = config.plot_title_font_size();
    text_renderer_.font_size(font_size);
    const auto [text_height, text_width] = text_renderer_.text_size(text);

    cv::Point top_left_position(plot_region_margin.left(),
        plot_region_margin.top() - config.plot_title_margin());
    top_left_position = adjust_text_position(top_left_position,
        cv::Size(text_width, text_height), cv::Size(size[1], size[0]));

    text_renderer_.render_text(image, text, top_left_position, color);
}

int TitleWriter::plot_title_height(const PlotConfig& config) {
    const int font_size = config.plot_title_font_size();
    text_renderer_.font_size(font_size);
    const auto [text_height, text_width] =
        text_renderer_.text_size(config.plot_title());
    return text_height;
}

}  // namespace func_sketch::plotter
