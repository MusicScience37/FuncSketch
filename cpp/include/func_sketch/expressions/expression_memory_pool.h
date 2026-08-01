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
 * \brief Definition of ExpressionMemoryPool class.
 */
#pragma once

#include <memory>
#include <memory_resource>
#include <utility>

#include "func_sketch/expressions/expression.h"

namespace func_sketch::expressions {

/*!
 * \brief Class of memory pools for expressions.
 *
 * \note This class releases memory when an instance if destroyed.
 */
class ExpressionMemoryPool {
public:
    /*!
     * \brief Constructor.
     */
    ExpressionMemoryPool()
        : memory_resource_(
              std::make_unique<std::pmr::monotonic_buffer_resource>()),
          allocator_(memory_resource_.get()) {}

    /*!
     * \brief Create an expression.
     *
     * \tparam T Type of the expression.
     * \tparam Args Types of arguments.
     * \param[in] args Arguments.
     * \return Created expression.
     */
    template <typename T, typename... Args>
    [[nodiscard]] Expression* create(Args&&... args) {
        return allocator_.new_object<Expression>(
            T(std::forward<Args>(args)...));
    }

    /*!
     * \brief Destroy an expression including its child expressions.
     *
     * \param[in] expression Expression to destroy.
     *
     * \note This function calls destructors of the expression and its child
     * expressions. Memory is released when the memory pool is destroyed.
     * Use of the expression after calling this function is undefined behavior.
     * \note This function does nothing if the argument is nullptr.
     */
    void destroy(Expression* expression) {
        if (expression == nullptr) {
            return;
        }

        // TODO Implement destruction of child expressions when expressions with
        // child expressions are implemented.
        allocator_.delete_object(expression);
    }

private:
    //! Memory resource.
    std::unique_ptr<std::pmr::monotonic_buffer_resource> memory_resource_;

    //! Allocator of expressions.
    std::pmr::polymorphic_allocator<Expression> allocator_;
};

}  // namespace func_sketch::expressions
