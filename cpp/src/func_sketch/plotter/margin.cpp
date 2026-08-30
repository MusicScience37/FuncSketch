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
 * \brief Implementation of Margin class.
 */
#include "func_sketch/plotter/margin.h"

#include "func_sketch/exceptions.h"

namespace func_sketch::plotter {

Margin::Margin(int left, int right, int top, int bottom) {
    this->left(left);
    this->right(right);
    this->top(top);
    this->bottom(bottom);
}

Margin& Margin::left(int value) {
    if (value < 0) {
        throw InvalidArgumentException("Left margin must be non-negative");
    }
    left_ = value;
    return *this;
}

Margin& Margin::right(int value) {
    if (value < 0) {
        throw InvalidArgumentException("Right margin must be non-negative");
    }
    right_ = value;
    return *this;
}

Margin& Margin::top(int value) {
    if (value < 0) {
        throw InvalidArgumentException("Top margin must be non-negative");
    }
    top_ = value;
    return *this;
}

Margin& Margin::bottom(int value) {
    if (value < 0) {
        throw InvalidArgumentException("Bottom margin must be non-negative");
    }
    bottom_ = value;
    return *this;
}

int Margin::left() const noexcept { return left_; }

int Margin::right() const noexcept { return right_; }

int Margin::top() const noexcept { return top_; }

int Margin::bottom() const noexcept { return bottom_; }

}  // namespace func_sketch::plotter
