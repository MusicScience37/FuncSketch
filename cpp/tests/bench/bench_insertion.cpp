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
 * \brief Benchmark of insertion of elements in lists.
 */
#include <array>
#include <cstddef>
#include <forward_list>
#include <iterator>
#include <list>
#include <memory_resource>
#include <vector>

#include <benchmark/benchmark.h>

#include "func_sketch/point.h"

constexpr std::size_t first_elements = 100;
constexpr std::size_t buffer_size = 16384;

#define INSERTION_BENCHMARK(FUNCTION) \
    BENCHMARK(FUNCTION)->Arg(10)->Arg(100)->Arg(1000)

void vector_insertion(benchmark::State& state) {
    const auto added_elements = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        std::vector<func_sketch::Point> vec;
        vec.reserve(first_elements + added_elements);
        for (std::size_t i = 0; i < first_elements; ++i) {
            vec.emplace_back(static_cast<double>(i), static_cast<double>(i));
        }
        auto iter_before = vec.begin() + first_elements - 2;
        for (std::size_t i = 0; i < added_elements; ++i) {
            iter_before = vec.emplace(
                iter_before, static_cast<double>(i), static_cast<double>(i));
        }
    }
}
INSERTION_BENCHMARK(vector_insertion);

void list_insertion(benchmark::State& state) {
    const auto added_elements = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        std::list<func_sketch::Point> list;
        for (std::size_t i = 0; i < first_elements; ++i) {
            list.emplace_back(static_cast<double>(i), static_cast<double>(i));
        }
        auto iter_before = std::prev(list.end(), 2);
        for (std::size_t i = 0; i < added_elements; ++i) {
            iter_before = list.emplace(
                iter_before, static_cast<double>(i), static_cast<double>(i));
        }
    }
}
INSERTION_BENCHMARK(list_insertion);

void pmr_list_insertion(benchmark::State& state) {
    const auto added_elements = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        std::pmr::monotonic_buffer_resource resource(buffer_size);
        std::pmr::list<func_sketch::Point> list(&resource);
        for (std::size_t i = 0; i < first_elements; ++i) {
            list.emplace_back(static_cast<double>(i), static_cast<double>(i));
        }
        auto iter_before = std::prev(list.end(), 2);
        for (std::size_t i = 0; i < added_elements; ++i) {
            iter_before = list.emplace(
                iter_before, static_cast<double>(i), static_cast<double>(i));
        }
    }
}
INSERTION_BENCHMARK(pmr_list_insertion);

void pmr_list_insertion_with_stack_buffer(benchmark::State& state) {
    const auto added_elements = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        std::array<std::byte, buffer_size> buffer{};
        std::pmr::monotonic_buffer_resource resource(
            buffer.data(), buffer.size());
        std::pmr::list<func_sketch::Point> list(&resource);
        for (std::size_t i = 0; i < first_elements; ++i) {
            list.emplace_back(static_cast<double>(i), static_cast<double>(i));
        }
        auto iter_before = std::prev(list.end(), 2);
        for (std::size_t i = 0; i < added_elements; ++i) {
            iter_before = list.emplace(
                iter_before, static_cast<double>(i), static_cast<double>(i));
        }
    }
}
INSERTION_BENCHMARK(pmr_list_insertion_with_stack_buffer);

void forward_list_insertion(benchmark::State& state) {
    const auto added_elements = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        std::forward_list<func_sketch::Point> list;
        auto iter = list.before_begin();
        auto iter_before = iter;
        for (std::size_t i = 0; i < first_elements; ++i) {
            iter = list.emplace_after(
                iter, static_cast<double>(i), static_cast<double>(i));
            if (i == first_elements - 3) {
                iter_before = iter;
            }
        }
        for (std::size_t i = 0; i < added_elements; ++i) {
            list.emplace_after(
                iter_before, static_cast<double>(i), static_cast<double>(i));
        }
    }
}
INSERTION_BENCHMARK(forward_list_insertion);

void pmr_forward_list_insertion(benchmark::State& state) {
    const auto added_elements = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        std::pmr::monotonic_buffer_resource resource(buffer_size);
        std::pmr::forward_list<func_sketch::Point> list(&resource);
        auto iter = list.before_begin();
        auto iter_before = iter;
        for (std::size_t i = 0; i < first_elements; ++i) {
            iter = list.emplace_after(
                iter, static_cast<double>(i), static_cast<double>(i));
            if (i == first_elements - 3) {
                iter_before = iter;
            }
        }
        for (std::size_t i = 0; i < added_elements; ++i) {
            list.emplace_after(
                iter_before, static_cast<double>(i), static_cast<double>(i));
        }
    }
}
INSERTION_BENCHMARK(pmr_forward_list_insertion);

void pmr_forward_list_insertion_with_stack_buffer(benchmark::State& state) {
    const auto added_elements = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        std::array<std::byte, buffer_size> buffer{};
        std::pmr::monotonic_buffer_resource resource(
            buffer.data(), buffer.size());
        std::pmr::forward_list<func_sketch::Point> list(&resource);
        auto iter = list.before_begin();
        auto iter_before = iter;
        for (std::size_t i = 0; i < first_elements; ++i) {
            iter = list.emplace_after(
                iter, static_cast<double>(i), static_cast<double>(i));
            if (i == first_elements - 3) {
                iter_before = iter;
            }
        }
        for (std::size_t i = 0; i < added_elements; ++i) {
            list.emplace_after(
                iter_before, static_cast<double>(i), static_cast<double>(i));
        }
    }
}
INSERTION_BENCHMARK(pmr_forward_list_insertion_with_stack_buffer);
