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
 * \brief Definition of exception classes.
 */
#pragma once

#include <stdexcept>

namespace func_sketch {

/*!
 * \brief Base class of exceptions in this project.
 */
class FuncSketchException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

/*!
 * \brief Class of exceptions for invalid arguments.
 */
class InvalidArgumentException : public FuncSketchException {
public:
    using FuncSketchException::FuncSketchException;
};

/*!
 * \brief Class of exceptions of invalid expressions.
 */
class InvalidExpressionException : public InvalidArgumentException {
public:
    using InvalidArgumentException::InvalidArgumentException;
};

}  // namespace func_sketch
