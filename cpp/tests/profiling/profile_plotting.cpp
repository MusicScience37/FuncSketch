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
 * \brief Profiling of plotting.
 */
#include <cstddef>
#include <string>

#include <gperftools/profiler.h>
#include <opencv2/core.hpp>

#include "func_sketch/math/functions/python_function_list.h"
#include "func_sketch/parser/expression_parser.h"
#include "func_sketch/plotter/function_sampler.h"
#include "func_sketch/plotter/plotter.h"

constexpr int image_width = 800;
constexpr int image_height = 600;

constexpr auto curve_color =
    func_sketch::plotter::RGBColor{.r = 0xCA, .g = 0x76, .b = 0x39};

int main(int argc, char** argv) {
    std::string expression_str = "sin(1/x)";
    std::size_t num_repetitions = 5000;
    if (argc > 1) {
        expression_str = argv[1];
    }
    if (argc > 2) {
        num_repetitions = std::stoul(argv[2]);
    }

    const auto range =
        func_sketch::plotter::PlotRange({-1.0, 1.0}, {-1.0, 1.0});
    const auto sampling_config = func_sketch::plotter::SamplingConfig{};
    const auto plot_config = func_sketch::plotter::PlotConfig{};

    const auto python_function_list = func_sketch::math::PythonFunctionList{};
    func_sketch::parser::ExpressionParser parser{python_function_list};
    func_sketch::plotter::FunctionSampler sampler{range, sampling_config};
    func_sketch::plotter::Plotter plotter{range, plot_config};

    cv::Mat image(image_height, image_width, CV_8UC3);

    ProfilerStart("profile_plotting.prof");
    for (std::size_t i = 0; i < num_repetitions; ++i) {
        const auto expression = parser(expression_str);
        const auto samples = sampler(*expression);
        plotter.write_background(image);
        plotter.write_curve(samples, curve_color, image);
    }
    ProfilerStop();

    return 0;
}
