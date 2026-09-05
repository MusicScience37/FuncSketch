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
 * \brief Benchmark of vectorization.
 */
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <random>
#include <vector>

#include <Eigen/Core>
#include <benchmark/benchmark.h>

static std::vector<double> create_input(std::size_t size) {
    std::vector<double> input(size);
    // NOLINTNEXTLINE: for reproducibility
    std::mt19937 generator{};
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    std::ranges::generate(input,
        [&generator, &distribution]() { return distribution(generator); });
    return input;
}

#define BENCH_WITH_ARGS(NAME) \
    BENCHMARK(NAME)           \
        ->Arg(100)            \
        ->Arg(150)            \
        ->Arg(200)            \
        ->Arg(300)            \
        ->Arg(500)            \
        ->Arg(1000)           \
        ->Arg(2000)           \
        ->Arg(5000)           \
        ->Arg(10000)

// Actual function is defined in virtual functions, so prevent inlining.
#ifdef __GNUC__
__attribute__((noinline))
#endif
double target_function(double arg) {
    return std::exp(arg) * arg;
}

static void bench_element_wise(benchmark::State& state) {
    const std::size_t size = static_cast<std::size_t>(state.range(0));
    const std::vector<double> input = create_input(size);
    std::vector<double> output(size);

    for (auto _ : state) {
        std::ranges::transform(input, output.begin(),
            [](double arg) { return target_function(arg); });
        benchmark::ClobberMemory();
        benchmark::DoNotOptimize(output.data());
    }
}
BENCH_WITH_ARGS(bench_element_wise);

static void bench_dynamic_vector(benchmark::State& state) {
    const std::size_t size = static_cast<std::size_t>(state.range(0));
    const std::vector<double> input = create_input(size);
    std::vector<double> output(size);

    for (auto _ : state) {
        Eigen::VectorXd input_eigen = Eigen::Map<const Eigen::VectorXd>(
            input.data(), static_cast<Eigen::Index>(input.size()));
        Eigen::VectorXd exp = input_eigen.array().exp();
        Eigen::VectorXd output_eigen = exp.array() * input_eigen.array();
        Eigen::Map<Eigen::VectorXd>(output.data(),
            static_cast<Eigen::Index>(output.size())) = output_eigen;
        benchmark::ClobberMemory();
        benchmark::DoNotOptimize(output.data());
    }
}
BENCH_WITH_ARGS(bench_dynamic_vector);

static void bench_static_buffer(benchmark::State& state) {
    const std::size_t size = static_cast<std::size_t>(state.range(0));
    const std::vector<double> input = create_input(size);
    std::vector<double> output(size);

    constexpr std::size_t buffer_size = 128;
    using vector_type = Eigen::Matrix<double, Eigen::Dynamic, 1,
        Eigen::ColMajor, buffer_size, 1>;

    for (auto _ : state) {
        for (std::size_t i = 0; i < size; i += buffer_size) {
            const auto current_buffer_size =
                static_cast<Eigen::Index>(std::min(buffer_size, size - i));
            vector_type input_eigen = Eigen::Map<const vector_type>(
                input.data() + i, current_buffer_size);
            vector_type exp = input_eigen.array().exp();
            vector_type output_eigen = exp.array() * input_eigen.array();
            Eigen::Map<vector_type>(output.data() + i, current_buffer_size) =
                output_eigen;
        }
        benchmark::ClobberMemory();
        benchmark::DoNotOptimize(output.data());
    }
}
BENCH_WITH_ARGS(bench_static_buffer);
