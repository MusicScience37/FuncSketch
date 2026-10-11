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
 * \brief Test of ConstantList class.
 */
#include "func_sketch/math/constant_list.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "func_sketch/common_types.h"

TEST_CASE("func_sketch::math::ConstantList") {
    using func_sketch::Number;
    using func_sketch::Real;
    using func_sketch::math::ConstantList;

    SECTION("emplace and get") {
        ConstantList list;
        list.emplace("a", Number(1.23));
        list.emplace("b", Number(2.34));

        const auto a_value = list.get("a");
        REQUIRE(a_value.has_value());
        CHECK(std::get<Real>(a_value.value()) == 1.23);

        const auto b_value = list.get("b");
        REQUIRE(b_value.has_value());
        CHECK(std::get<Real>(b_value.value()) == 2.34);

        const auto c_value = list.get("c");
        CHECK(!c_value.has_value());
    }

    SECTION("check built-in constants") {
        const ConstantList list = func_sketch::math::generate_constant_list();

        SECTION("pi") {
            const auto pi_value = list.get("pi");
            REQUIRE(pi_value.has_value());
            CHECK_THAT(std::get<Real>(pi_value.value()),
                Catch::Matchers::WithinRel(3.14159265358979323846));
        }

        SECTION("e") {
            const auto e_value = list.get("e");
            REQUIRE(e_value.has_value());
            CHECK_THAT(std::get<Real>(e_value.value()),
                Catch::Matchers::WithinRel(2.71828182845904523536));
        }

        SECTION("euler_mascheroni") {
            const auto value = list.get("euler_mascheroni");
            REQUIRE(value.has_value());
            CHECK_THAT(std::get<Real>(value.value()),
                Catch::Matchers::WithinRel(0.57721566490153286061));
        }

        SECTION("golden_ratio") {
            const auto value = list.get("golden_ratio");
            REQUIRE(value.has_value());
            CHECK_THAT(std::get<Real>(value.value()),
                Catch::Matchers::WithinRel(1.61803398874989484820));
        }

        SECTION("avogadro_constant") {
            const auto value = list.get("avogadro_constant");
            REQUIRE(value.has_value());
            CHECK_THAT(std::get<Real>(value.value()),
                Catch::Matchers::WithinRel(6.02214076e23));
        }

        SECTION("boltzmann_constant") {
            const auto value = list.get("boltzmann_constant");
            REQUIRE(value.has_value());
            CHECK_THAT(std::get<Real>(value.value()),
                Catch::Matchers::WithinRel(1.380649e-23));
        }

        SECTION("elementary_charge") {
            const auto value = list.get("elementary_charge");
            REQUIRE(value.has_value());
            CHECK_THAT(std::get<Real>(value.value()),
                Catch::Matchers::WithinRel(1.602176634e-19));
        }

        SECTION("gravitational_constant") {
            const auto value = list.get("gravitational_constant");
            REQUIRE(value.has_value());
            CHECK_THAT(std::get<Real>(value.value()),
                Catch::Matchers::WithinRel(6.67430e-11));
        }

        SECTION("planck_constant") {
            const auto value = list.get("planck_constant");
            REQUIRE(value.has_value());
            CHECK_THAT(std::get<Real>(value.value()),
                Catch::Matchers::WithinRel(6.62607015e-34));
        }

        SECTION("speed_of_light") {
            const auto value = list.get("speed_of_light");
            REQUIRE(value.has_value());
            CHECK_THAT(std::get<Real>(value.value()),
                Catch::Matchers::WithinRel(299792458.0));
        }
    }
}
