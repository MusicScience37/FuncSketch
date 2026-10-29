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
 * \brief Implementation of generate_math_operation_list function.
 */
#include "func_sketch/expressions/generate_math_operation_list.h"

#include "func_sketch/expressions/operations/integration_operation.h"

namespace func_sketch::expressions {

MathOperationList generate_math_operation_list() {
    MathOperationList list;

    // In integration_operation.h
    list.emplace(integration_operation());

    return list;
}

}  // namespace func_sketch::expressions
