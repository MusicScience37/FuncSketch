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
 * \brief Implementation of LegendWriter class.
 */
#include "func_sketch/plotter/legend_writer.h"

#include <algorithm>
#include <ranges>

#include "func_sketch/plotter/plotting_util.h"

namespace func_sketch::plotter {

void LegendWriter::legend_entries(
    const std::vector<std::pair<std::string, RGBColor>>& entries) {
    legend_entries_ = entries;
}

int LegendWriter::prepare(
    Margin& plot_region_margin, const PlotConfig& config) {
    if (!config.legend().visible() || legend_entries_.empty()) {
        // No legend to display.
        return 0;
    }

    // Start from the zero height and width.
    int legend_height = 0;
    int legend_width = 0;

    // Handle the title.
    if (!config.legend().title().empty()) {
        text_renderer_.font_size(config.legend().title_font_size());
        const auto title_text_size =
            text_renderer_.text_size(config.legend().title());
        legend_height =
            title_text_size.height + config.legend().entry_spacing();
        legend_width = title_text_size.width;
    }

    // Handle the curve names in legend entries.
    text_renderer_.font_size(config.legend().curve_name_font_size());
    const auto [curve_name_height_sum, curve_name_max_width] =
        std::ranges::fold_left(
            legend_entries_ | std::views::transform([this](const auto& entry) {
                return text_renderer_.text_size(entry.first);
            }),
            std::make_pair(0, 0),
            [](const auto& previous_result, const TextSize& size) {
                return std::make_pair(previous_result.first + size.height,
                    std::max(previous_result.second, size.width));
            });

    const int entry_max_width = config.legend().curve_line_length() +
        config.legend().curve_line_name_spacing() + curve_name_max_width;
    legend_width = std::max(legend_width, entry_max_width);
    const int last_curve_name_depth =
        text_renderer_.text_size(legend_entries_.back().first).depth;
    legend_height += curve_name_height_sum +
        static_cast<int>(legend_entries_.size() - 1) *
            config.legend().entry_spacing() +
        last_curve_name_depth;

    legend_width += config.legend().margin();

    plot_region_margin.right(plot_region_margin.right() + legend_width);

    return legend_height;
}

void LegendWriter::write(
    Image& image, const PlotConfig& config, const Margin& plot_region_margin) {
    if (!config.legend().visible() || legend_entries_.empty()) {
        // No legend to display.
        return;
    }

    // Position of the top-left corner of the legend.
    const int position_x =
        image.cols - plot_region_margin.right() + config.legend().margin();
    int position_y = plot_region_margin.top();

    const auto legend_color_in_cv = convert_color(config.legend().color());

    // Handle the title.
    if (!config.legend().title().empty()) {
        text_renderer_.font_size(config.legend().title_font_size());
        const auto title_text_size =
            text_renderer_.text_size(config.legend().title());
        text_renderer_.render_text(image, config.legend().title(),
            cv::Point(position_x, position_y + title_text_size.height),
            legend_color_in_cv);

        position_y += title_text_size.height + config.legend().entry_spacing();
    }

    // Handle the legend entries.
    text_renderer_.font_size(config.legend().curve_name_font_size());
    for (const auto& [curve_name, curve_color] : legend_entries_) {
        const auto curve_name_text_size = text_renderer_.text_size(curve_name);

        const int line_position_y =
            position_y + (curve_name_text_size.height + 1) / 2;
        const int line_end_x = position_x + config.legend().curve_line_length();
        const auto line_start_point = cv::Point(position_x, line_position_y);
        const auto line_end_point = cv::Point(line_end_x, line_position_y);
        write_line(image, line_start_point, line_end_point,
            convert_color(curve_color), config.curve_line_width());

        const int text_position_x =
            line_end_x + config.legend().curve_line_name_spacing();
        const auto text_bottom_left_position = cv::Point(
            text_position_x, position_y + curve_name_text_size.height);
        text_renderer_.render_text(
            image, curve_name, text_bottom_left_position, legend_color_in_cv);

        position_y +=
            curve_name_text_size.height + config.legend().entry_spacing();
    }
}

}  // namespace func_sketch::plotter
