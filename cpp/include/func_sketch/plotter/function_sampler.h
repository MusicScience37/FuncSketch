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
 * \brief Definition of FunctionSampler class.
 */
#pragma once

#include <vector>

#include "func_sketch/expressions/expression.h"
#include "func_sketch/expressions/expression_evaluator.h"
#include "func_sketch/plotter/plot_config.h"
#include "func_sketch/plotter/plot_range.h"
#include "func_sketch/plotter/point.h"

namespace func_sketch::plotter {

/*!
 * \brief Class to sample functions for plotting.
 */
class FunctionSampler {
public:
    /*!
     * \brief Constructor.
     *
     * \param[in] range Range of plots.
     * \param[in] config Configuration of plots.
     */
    FunctionSampler(const PlotRange& range, const PlotConfig& config);

    /*!
     * \brief Set the range of plots.
     *
     * \param[in] value Range of plots.
     * \return Reference to this object.
     */
    FunctionSampler& range(const PlotRange& value);

    /*!
     * \brief Set the configuration of plots.
     *
     * \param[in] value Configuration of plots.
     * \return Reference to this object.
     */
    FunctionSampler& config(const PlotConfig& value);

    /*!
     * \brief Sample a function for plotting.
     *
     * \param[in] function Function to sample.
     * \return Sampled points of the function.
     */
    [[nodiscard]] std::vector<Point> operator()(
        const expressions::Expression& function) const;

private:
    /*!
     * \brief Sample initial points.
     *
     * \param[in] function Function to sample.
     * \return Sampled points of the function.
     */
    [[nodiscard]] std::vector<Point> sample_initial_points(
        const expressions::Expression& function) const;

    /*!
     * \brief Sample additional points adaptively.
     *
     * \param[in] function Function to sample.
     * \param[in] initial_samples Initial sampled points.
     * \return Sampled points of the function.
     */
    [[nodiscard]] std::vector<Point> sample_adaptive_points(
        const expressions::Expression& function,
        const std::vector<Point>& initial_samples) const;

    /*!
     * \brief Divide if the last change of y is large.
     *
     * \param[in] function Function to sample.
     * \param[in,out] samples Sampled points of the function.
     * \retval true The segment was divided into two segments.
     * \retval false The segment was not divided into two segments.
     */
    [[nodiscard]] bool divide_last_segment_according_to_y_change(
        const expressions::Expression& function,
        std::vector<Point>& samples) const;

    /*!
     * \brief Divide if the last change of slope of y is large.
     *
     * \param[in] function Function to sample.
     * \param[in,out] samples Sampled points of the function.
     * \retval true The segment was divided into two segments.
     * \retval false The segment was not divided into two segments.
     */
    [[nodiscard]] bool divide_last_segment_according_to_slope_change(
        const expressions::Expression& function,
        std::vector<Point>& samples) const;

    /*!
     * \brief Divide if one end of the last segment is not finite.
     *
     * \param[in] function Function to sample.
     * \param[in,out] samples Sampled points of the function.
     * \retval true The segment was divided into two segments.
     * \retval false The segment was not divided into two segments.
     */
    [[nodiscard]] bool divide_last_segment_when_one_end_is_not_finite(
        const expressions::Expression& function,
        std::vector<Point>& samples) const;

    /*!
     * \brief Divide a segment into two segments in sample points if applicable.
     *
     * \param[in] function Function to sample.
     * \param[in,out] samples Sampled points of the function.
     * \param[in] left_index Index of the left point of the segment.
     * \retval true The segment was divided into two segments.
     * \retval false The segment was not divided into two segments.
     *
     * \note This function checks the condition to skip sampling, and does
     * sample if the condition is not satisfied.
     */
    [[nodiscard]] bool divide_segment(const expressions::Expression& function,
        std::vector<Point>& samples, std::size_t left_index) const;

    /*!
     * \brief Sample an additional point between two points.
     *
     * \param[in] function Function to sample.
     * \param[in] left_point Left point.
     * \param[in] right_point Right point.
     * \return Sampled point of the function.
     */
    [[nodiscard]] Point sample_additional_point(
        const expressions::Expression& function, const Point& left_point,
        const Point& right_point) const;

    /*!
     * \brief Check the condition to skip sampling of a point between two
     * points.
     *
     * \param[in] left_point Left point.
     * \param[in] right_point Right point.
     * \retval true Do not sample a point between the two points.
     * \retval false Sample a point between the two points.
     */
    [[nodiscard]] bool is_sampling_should_be_skipped(
        const Point& left_point, const Point& right_point) const;

    //! Range of plots.
    PlotRange range_;

    //! Configuration of plots.
    PlotConfig config_;

    //! Evaluator of expressions.
    expressions::ExpressionEvaluator evaluator_;
};

}  // namespace func_sketch::plotter
