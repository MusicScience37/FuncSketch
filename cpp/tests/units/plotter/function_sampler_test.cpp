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
 * \brief Test of FunctionSampler class.
 */
#include "func_sketch/plotter/function_sampler.h"

#include <memory>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/expressions/binary_expression.h"
#include "func_sketch/expressions/expression_memory_pool.h"
#include "func_sketch/expressions/expression_ptr.h"
#include "func_sketch/expressions/parameter_expression.h"
#include "func_sketch/math/binary_operator.h"
#include "func_sketch/math/binary_operators.h"

TEST_CASE("func_sketch::plotter::FunctionSampler") {
    using func_sketch::expressions::BinaryExpression;
    using func_sketch::expressions::ExpressionMemoryPool;
    using func_sketch::expressions::ExpressionPtr;
    using func_sketch::expressions::ParameterExpression;
    using func_sketch::math::BinaryOperator;
    using func_sketch::math::MultiplicationOperator;
    using func_sketch::plotter::FunctionSampler;
    using func_sketch::plotter::PlotConfig;
    using func_sketch::plotter::PlotRange;

    SECTION("sample a function") {
        const auto range = PlotRange({-1.0, 1.0}, {-1.0, 1.0});
        const auto config = PlotConfig().num_sample_points(5);
        FunctionSampler sampler(range, config);

        auto pool = std::make_unique<ExpressionMemoryPool>();
        auto* expression =
            pool->create<BinaryExpression>(pool->create<ParameterExpression>(),
                pool->create<ParameterExpression>(),
                BinaryOperator{MultiplicationOperator{}});
        const auto expression_ptr = ExpressionPtr(expression, std::move(pool));

        const auto samples = sampler(*expression_ptr);

        REQUIRE(samples.size() == 5);
        constexpr double tolerance = 1e-10;
        // NOLINTBEGIN(*-magic-numbers)
        CHECK_THAT(samples[0].x, Catch::Matchers::WithinAbs(-1.0, tolerance));
        CHECK_THAT(samples[0].y, Catch::Matchers::WithinAbs(1.0, tolerance));
        CHECK_THAT(samples[1].x, Catch::Matchers::WithinAbs(-0.5, tolerance));
        CHECK_THAT(samples[1].y, Catch::Matchers::WithinAbs(0.25, tolerance));
        CHECK_THAT(samples[2].x, Catch::Matchers::WithinAbs(0.0, tolerance));
        CHECK_THAT(samples[2].y, Catch::Matchers::WithinAbs(0.0, tolerance));
        CHECK_THAT(samples[3].x, Catch::Matchers::WithinAbs(0.5, tolerance));
        CHECK_THAT(samples[3].y, Catch::Matchers::WithinAbs(0.25, tolerance));
        CHECK_THAT(samples[4].x, Catch::Matchers::WithinAbs(1.0, tolerance));
        CHECK_THAT(samples[4].y, Catch::Matchers::WithinAbs(1.0, tolerance));
        // NOLINTEND(*-magic-numbers)
    }
}
