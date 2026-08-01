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
 * \brief Implementation of parser_test_strings function.
 */
#include "parser_test_strings.h"

std::vector<std::string> parser_test_strings() {
    return {
        // Constants.
        "1.23",
        "-2.34",
        // Parameters.
        "x",
        // Unary minus.
        "-x",
        // Addition.
        "1.23 + 4.56",
        // Subtraction.
        "1.23 - 4.56",
        // Multiplication.
        "1.23 * 4.56",
        // Division.
        "1.23 / 4.56",
        // Power.
        "1.23 ** 4.56",
        // Parentheses.
        "1.23 * (4.56 + 7.89)",
        // Function calls.
        "exp(1.23)",
        // Nested expressions.
        "exp(exp(1.23) + 4.56)",
        "1.23 * 3.45 / (6.78 - 9.01)",
        "-exp(1.23)",
        // Other identifiers.
        "TestIdentifier",
        "test_identifier",
        "test123",
        // Wrong expressions.
        "1.23 +",
        "1.23 * * 4.56",
        "exp(1.23,)",
    };
}
