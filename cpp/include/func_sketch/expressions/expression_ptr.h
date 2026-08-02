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
 * \brief Definition of ExpressionPtr class.
 */
#pragma once

#include <memory>

#include "func_sketch/expressions/expression.h"
#include "func_sketch/expressions/expression_memory_pool.h"

namespace func_sketch::expressions {

/*!
 * \brief Class of pointers to expressions with RAII.
 *
 * \note This class destroys the pointed expression when the ExpressionPtr
 * object is destroyed.
 */
class ExpressionPtr {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] expression Expression.
     * \param[in] memory_pool Memory pool used to create the expression.
     *
     * \note The memory pool must be the one used to create the expression.
     * Use of a different memory pool causes undefined behavior.
     */
    ExpressionPtr(Expression* expression,
        std::unique_ptr<ExpressionMemoryPool> memory_pool) noexcept
        : expression_(expression, Deleter(std::move(memory_pool))) {}

    /*!
     * \brief Constructor.
     */
    ExpressionPtr() noexcept = default;

    /*!
     * \brief Clear the pointer.
     */
    void reset() noexcept {
        expression_ = std::unique_ptr<Expression, Deleter>(nullptr, Deleter());
    }

    /*!
     * \brief Get the pointed expression.
     *
     * \return Pointed expression.
     */
    [[nodiscard]] Expression* get() const noexcept { return expression_.get(); }

    /*!
     * \brief Access the pointed expression.
     *
     * \return Reference to the pointed expression.
     */
    [[nodiscard]] Expression& operator*() const noexcept {
        return *expression_;
    }

    /*!
     * \brief Access the member of the pointed expression.
     *
     * \return Pointer to the member of the pointed expression.
     */
    [[nodiscard]] Expression* operator->() const noexcept {
        return expression_.get();
    }

private:
    //! Deleter for ExpressionPtr.
    class Deleter {
    public:
        /*!
         * \brief Constructor.
         *
         * \param[in] memory_pool Memory pool.
         */
        explicit Deleter(
            std::unique_ptr<ExpressionMemoryPool> memory_pool) noexcept
            : memory_pool_(std::move(memory_pool)) {}

        /*!
         * \brief Constructor.
         */
        Deleter() noexcept = default;

        /*!
         * \brief Delete the pointed expression.
         *
         * \param[in] expression Expression to delete.
         */
        void operator()(Expression* expression) const noexcept {
            if (expression != nullptr && memory_pool_ != nullptr) {
                memory_pool_->destroy(expression);
            }
        }

    private:
        //! Memory pool.
        std::unique_ptr<ExpressionMemoryPool> memory_pool_;
    };

    //! Pointer.
    std::unique_ptr<Expression, Deleter> expression_;
};

}  // namespace func_sketch::expressions
