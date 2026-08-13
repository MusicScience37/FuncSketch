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
 * \brief Benchmark of plotting.
 */
#include <array>
#include <string_view>

#include <benchmark/benchmark.h>
#include <opencv2/core.hpp>

#include "func_sketch/parser/expression_parser.h"
#include "func_sketch/plotter/function_sampler.h"
#include "func_sketch/plotter/plotter.h"

constexpr int image_width = 800;
constexpr int image_height = 600;

constexpr auto curve_color =
    func_sketch::plotter::RGBColor{.r = 0xCA, .g = 0x76, .b = 0x39};

constexpr auto expressions = std::to_array<std::string_view>(
    {"x", "x * x", "x ** 3", "exp(x)", "gamma(x)"});

/*!
 * \brief Class of the fixture for benchmark of plotting.
 */
class PlottingFixture : public benchmark::Fixture {
public:
    /*!
     * \brief Perform benchmark of plotting.
     *
     * \param[in] state State of the benchmark.
     * \param[in] expression_str Expression string.
     */
    void benchmark_plotting(
        benchmark::State& state, const std::string& expression_str) {
        for (auto _ : state) {
            auto expression = parser_(expression_str);
            auto samples = sampler_(*expression);
            plotter_.write_background(image_);
            plotter_.write_curve(samples, curve_color, image_);
            benchmark::DoNotOptimize(expression);
            benchmark::DoNotOptimize(samples);
            benchmark::DoNotOptimize(image_);
            benchmark::ClobberMemory();
        }
    }

private:
    //! Parser.
    func_sketch::parser::ExpressionParser parser_;

    //! Sampler.
    func_sketch::plotter::FunctionSampler sampler_{
        func_sketch::plotter::PlotRange({-1.0, 1.0}, {-1.0, 1.0}),
        func_sketch::plotter::PlotConfig()};

    //! Plotter.
    func_sketch::plotter::Plotter plotter_{
        func_sketch::plotter::PlotRange({-1.0, 1.0}, {-1.0, 1.0}),
        func_sketch::plotter::PlotConfig()};

    //! Buffer of the image.
    cv::Mat image_ = cv::Mat(image_height, image_width, CV_8UC3);
};

BENCHMARK_DEFINE_F(PlottingFixture, Plot)(benchmark::State& state) {
    const auto expression_index = static_cast<std::size_t>(state.range(0));
    const auto expression_str =
        static_cast<std::string>(expressions[expression_index]);
    benchmark_plotting(state, expression_str);
}
static void custom_arguments(benchmark::Benchmark* bench) {
    for (std::size_t i = 0; i < expressions.size(); ++i) {
        bench->Arg(static_cast<int>(i));
    }
}
BENCHMARK_REGISTER_F(PlottingFixture, Plot)
    ->Unit(benchmark::kMillisecond)
    ->Apply(custom_arguments);
