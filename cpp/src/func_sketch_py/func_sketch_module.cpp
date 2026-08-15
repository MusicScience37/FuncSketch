#include <cstdint>
#include <functional>
#include <utility>
#include <vector>

#include <fmt/format.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/complex.h>
#include <nanobind/stl/pair.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

#include "func_sketch/common_types.h"
#include "func_sketch/expressions/expression_evaluator.h"
#include "func_sketch/expressions/expression_ptr.h"
#include "func_sketch/parser/expression_parser.h"
#include "func_sketch/plotter/function_sampler.h"
#include "func_sketch/plotter/image.h"
#include "func_sketch/plotter/plot_config.h"
#include "func_sketch/plotter/plot_range.h"
#include "func_sketch/plotter/plotter.h"
#include "func_sketch/plotter/point.h"
#include "func_sketch/plotter/rgb_color.h"

namespace {

/*!
 * \brief Struct of lists of points for reducing the number of type conversions
 * between C++ and Python.
 */
struct PointList {
    //! Points.
    std::vector<func_sketch::plotter::Point> points;
};

/*!
 * \brief Type of raw images passed from Python as numpy arrays of RGB
 * pixels.
 *
 * \note The device is restricted to CPU so that the buffer can be safely
 * accessed from C++ code without copying. Also the data is restricted to
 * contiguous buffer so that the buffer can be safely converted to OpenCV Mat
 * without copying.
 */
using RawImage = nanobind::ndarray<uint8_t, nanobind::shape<-1, -1, 3>,
    nanobind::c_contig, nanobind::device::cpu>;

/*!
 * \brief Convert a raw image passed from Python to an Image object.
 *
 * \param[in] raw_image Raw image.
 * \return Image object sharing the buffer with the raw image.
 *
 * \note The returned image shares the buffer with \p raw_image without
 * copying. Writing to the returned image writes back into \p raw_image.
 */
func_sketch::plotter::Image to_image(const RawImage& raw_image) {
    return func_sketch::plotter::Image(static_cast<int>(raw_image.shape(0)),
        static_cast<int>(raw_image.shape(1)), CV_8UC3, raw_image.data());
}

/*!
 * \brief Wrap a Python function to C++ function.
 *
 * \tparam ResultType Type of the result of the function.
 * \tparam ArgsType Types of the arguments of the function.
 * \param[in] python_function Python function.
 * \return C++ function that wraps the Python function.
 */
template <typename ResultType, typename... ArgsType>
[[nodiscard]] std::function<ResultType(ArgsType...)> wrap_python_function(
    const nanobind::object& python_function) {
    return [python_function](ArgsType... args) -> ResultType {
        try {
            return nanobind::cast<ResultType>(python_function(args...));
        } catch (const std::exception& e) {
            return std::numeric_limits<ResultType>::quiet_NaN();
        }
    };
}

/*!
 * \brief Generate the list of functions from Python.
 *
 * \return List of functions.
 */
func_sketch::math::PythonFunctionList generate_python_function_list() {
    using func_sketch::Complex;
    using func_sketch::Real;

    nanobind::module_ scipy_special =
        nanobind::module_::import_("scipy.special");

    return func_sketch::math::PythonFunctionList{
        .complex_gamma =
            wrap_python_function<Complex, Complex>(scipy_special.attr("gamma")),
        .complex_bessel_j = wrap_python_function<Complex, Real, Complex>(
            scipy_special.attr("jv")),
        .complex_bessel_y = wrap_python_function<Complex, Real, Complex>(
            scipy_special.attr("yv")),
        .complex_bessel_i = wrap_python_function<Complex, Real, Complex>(
            scipy_special.attr("iv")),
        .complex_bessel_k = wrap_python_function<Complex, Real, Complex>(
            scipy_special.attr("kv")),
        .complex_hankel1 = wrap_python_function<Complex, Real, Complex>(
            scipy_special.attr("hankel1")),
        .complex_hankel2 = wrap_python_function<Complex, Real, Complex>(
            scipy_special.attr("hankel2")),
        .complex_spherical_bessel_j =
            wrap_python_function<Complex, unsigned, Complex>(
                scipy_special.attr("spherical_jn")),
        .complex_spherical_bessel_y =
            wrap_python_function<Complex, unsigned, Complex>(
                scipy_special.attr("spherical_yn")),
    };
}

}  // namespace

// NOLINTNEXTLINE(*-identifier-length,*-vararg,*-c-arrays,*-array-decay,*-value-param): external library.
NB_MODULE(_cpp, m) {
    using nanobind::literals::operator""_a;

    m.doc() = "C++ module for func_sketch";

    using func_sketch::expressions::ExpressionPtr;
    nanobind::class_<ExpressionPtr>(m, "Expression", "Class of expressions.")
        .def(
            "__str__",
            [](const ExpressionPtr& self) { return fmt::format("{}", *self); },
            "Format the expression as a string.");

    using func_sketch::parser::ExpressionParser;
    nanobind::class_<ExpressionParser>(
        m, "ExpressionParser", R"(Class of parser for expressions.

Objects of this class can be called with a string to parse it into an Expression object.)")
        .def(
            "__init__",
            [](ExpressionParser* self) {
                new (self) ExpressionParser(generate_python_function_list());
            },
            "Constructor.")
        .def(
            "__call__",
            [](const ExpressionParser& self,
                const std::string& expression_str) {
                return self(expression_str);
            },
            "expression_str"_a, "Parse a string into an Expression object.");

    using func_sketch::expressions::ExpressionEvaluator;
    nanobind::class_<ExpressionEvaluator>(
        m, "ExpressionEvaluator", "Class to evaluate expressions.")
        .def(nanobind::init<>(), "Constructor.")
        .def(
            "__call__",
            [](const ExpressionEvaluator& self, const ExpressionPtr& expression,
                func_sketch::Real parameter) {
                func_sketch::Real result;
                self(*expression, parameter, result);
                return result;
            },
            "expression"_a, "parameter"_a,
            "Evaluate an expression at a parameter and return the result.");

    using func_sketch::plotter::RGBColor;
    nanobind::class_<RGBColor>(m, "RGBColor", "Class of RGB colors.")
        .def(nanobind::init<std::uint8_t, std::uint8_t, std::uint8_t>(), "r"_a,
            "g"_a, "b"_a, "Constructor.")
        .def_rw("r", &RGBColor::r, "Red component.")
        .def_rw("g", &RGBColor::g, "Green component.")
        .def_rw("b", &RGBColor::b, "Blue component.");

    using func_sketch::plotter::Point;
    nanobind::class_<Point>(m, "Point", "Class of points.")
        .def(nanobind::init<double, double>(), "x"_a, "y"_a, "Constructor.")
        .def_rw("x", &Point::x, "X coordinate.")
        .def_rw("y", &Point::y, "Y coordinate.");

    nanobind::class_<PointList>(m, "PointList", "Class of lists of points.")
        .def(nanobind::init<std::vector<Point>>(), "points"_a, "Constructor.")
        .def_rw("points", &PointList::points, "List of points.");

    using func_sketch::plotter::PlotRange;
    nanobind::class_<PlotRange>(m, "PlotRange", "Class of ranges of plots.")
        .def(nanobind::init<std::pair<double, double>,
                 std::pair<double, double>>(),
            "x_range"_a, "y_range"_a, "Constructor.")
        .def_prop_ro("x_range", &PlotRange::x_range, "Range of x-axis.")
        .def_prop_ro("y_range", &PlotRange::y_range, "Range of y-axis.");

    using func_sketch::plotter::PlotConfig;
    nanobind::class_<PlotConfig>(
        m, "PlotConfig", "Class of configurations of plots.")
        .def(nanobind::init<>(), "Constructor.")
        .def_prop_rw(
            "left_margin",
            [](const PlotConfig& self) -> int { return self.left_margin(); },
            [](PlotConfig& self, int value) { self.left_margin(value); },
            "Left margin of plots in pixels.")
        .def_prop_rw(
            "right_margin",
            [](const PlotConfig& self) -> int { return self.right_margin(); },
            [](PlotConfig& self, int value) { self.right_margin(value); },
            "Right margin of plots in pixels.")
        .def_prop_rw(
            "top_margin",
            [](const PlotConfig& self) -> int { return self.top_margin(); },
            [](PlotConfig& self, int value) { self.top_margin(value); },
            "Top margin of plots in pixels.")
        .def_prop_rw(
            "bottom_margin",
            [](const PlotConfig& self) -> int { return self.bottom_margin(); },
            [](PlotConfig& self, int value) { self.bottom_margin(value); },
            "Bottom margin of plots in pixels.")
        .def_prop_rw(
            "tick_label_font_size",
            [](const PlotConfig& self) -> int {
                return self.tick_label_font_size();
            },
            [](PlotConfig& self, int value) {
                self.tick_label_font_size(value);
            },
            "Font size of tick labels in pixels.")
        .def_prop_rw(
            "axes_line_width",
            [](const PlotConfig& self) -> int {
                return self.axes_line_width();
            },
            [](PlotConfig& self, int value) { self.axes_line_width(value); },
            "Line width of axes in pixels.")
        .def_prop_rw(
            "grid_line_width",
            [](const PlotConfig& self) -> int {
                return self.grid_line_width();
            },
            [](PlotConfig& self, int value) { self.grid_line_width(value); },
            "Line width of grid lines in pixels.")
        .def_prop_rw(
            "zero_line_width",
            [](const PlotConfig& self) -> int {
                return self.zero_line_width();
            },
            [](PlotConfig& self, int value) { self.zero_line_width(value); },
            "Line width of the grid line at zero in pixels.")
        .def_prop_rw(
            "curve_line_width",
            [](const PlotConfig& self) -> int {
                return self.curve_line_width();
            },
            [](PlotConfig& self, int value) { self.curve_line_width(value); },
            "Line width of curves in pixels.")
        .def_prop_rw(
            "background_color",
            [](const PlotConfig& self) -> RGBColor {
                return self.background_color();
            },
            [](PlotConfig& self, const RGBColor& value) {
                self.background_color(value);
            },
            "Color of background.")
        .def_prop_rw(
            "axes_color",
            [](const PlotConfig& self) -> RGBColor {
                return self.axes_color();
            },
            [](PlotConfig& self, const RGBColor& value) {
                self.axes_color(value);
            },
            "Color of axes.")
        .def_prop_rw(
            "grid_color",
            [](const PlotConfig& self) -> RGBColor {
                return self.grid_color();
            },
            [](PlotConfig& self, const RGBColor& value) {
                self.grid_color(value);
            },
            "Color of grid lines.")
        .def_prop_rw(
            "initial_num_sample_points",
            [](const PlotConfig& self) -> std::size_t {
                return self.initial_num_sample_points();
            },
            [](PlotConfig& self, std::size_t value) {
                self.initial_num_sample_points(value);
            },
            "Number of points to sample initially in adaptive sampling.")
        .def_prop_rw(
            "max_num_sample_points",
            [](const PlotConfig& self) -> std::size_t {
                return self.max_num_sample_points();
            },
            [](PlotConfig& self, std::size_t value) {
                self.max_num_sample_points(value);
            },
            "Maximum number of points to sample in adaptive sampling.\n\n"
            "Note:\n"
            "    This value should be larger than "
            "initial_num_sample_points. Otherwise, this configuration has "
            "no effect.\n\n"
            "Note:\n"
            "    This value is limited for safety limit of memory "
            "usage.")
        .def_prop_rw(
            "max_coordinate_change_rate",
            [](const PlotConfig& self) -> double {
                return self.max_coordinate_change_rate();
            },
            [](PlotConfig& self, double value) {
                self.max_coordinate_change_rate(value);
            },
            "Threshold of the change in coordinates of sample points "
            "relative to the plot range in adaptive sampling.")
        .def_prop_rw(
            "slope_change_threshold",
            [](const PlotConfig& self) -> double {
                return self.slope_change_threshold();
            },
            [](PlotConfig& self, double value) {
                self.slope_change_threshold(value);
            },
            "Threshold of the change in slope normalized by the plot range "
            "in adaptive sampling.")
        .def_prop_rw(
            "min_param_change_rate",
            [](const PlotConfig& self) -> double {
                return self.min_param_change_rate();
            },
            [](PlotConfig& self, double value) {
                self.min_param_change_rate(value);
            },
            "Minimum rate of parameter change in adaptive sampling.\n\n"
            "Note:\n"
            "    This value is limited for safety limit of memory "
            "usage.")
        .def_prop_rw(
            "num_pixels_per_tick_in_x_axis",
            [](const PlotConfig& self) -> std::size_t {
                return self.num_pixels_per_tick_in_x_axis();
            },
            [](PlotConfig& self, std::size_t value) {
                self.num_pixels_per_tick_in_x_axis(value);
            },
            "Number of pixels per tick in the x-axis.")
        .def_prop_rw(
            "num_pixels_per_tick_in_y_axis",
            [](const PlotConfig& self) -> std::size_t {
                return self.num_pixels_per_tick_in_y_axis();
            },
            [](PlotConfig& self, std::size_t value) {
                self.num_pixels_per_tick_in_y_axis(value);
            },
            "Number of pixels per tick in the y-axis.");

    using func_sketch::plotter::FunctionSampler;
    nanobind::class_<FunctionSampler>(
        m, "FunctionSampler", "Class to sample functions for plotting.")
        .def(nanobind::init<PlotRange, PlotConfig>(), "range"_a, "config"_a,
            "Constructor.")
        .def_prop_rw(
            "range",
            // Making the getter nullptr causes an error in mypy, so we must
            // write a getter that throws an exception instead.
            [](FunctionSampler& self) -> PlotRange {
                throw std::runtime_error("Property 'range' is write-only.");
            },
            [](FunctionSampler& self, const PlotRange& value) {
                self.range(value);
            },
            "Range of plots. (write-only)")
        .def_prop_rw(
            "config",
            [](FunctionSampler& self) -> PlotConfig {
                throw std::runtime_error("Property 'config' is write-only.");
            },
            [](FunctionSampler& self, const PlotConfig& value) {
                self.config(value);
            },
            "Configuration of plots. (write-only)")
        .def(
            "__call__",
            [](const FunctionSampler& self, const ExpressionPtr& function) {
                return PointList{self(*function)};
            },
            "function"_a, "Sample a function and return a list of points.");

    using func_sketch::plotter::Plotter;
    nanobind::class_<Plotter>(m, "Plotter", "Class for plotting.")
        .def(nanobind::init<PlotRange, PlotConfig>(), "range"_a, "config"_a,
            "Constructor.")
        .def_prop_rw(
            "range",
            [](Plotter& self) -> PlotRange {
                throw std::runtime_error("Property 'range' is write-only.");
            },
            [](Plotter& self, const PlotRange& value) { self.range(value); },
            "Range of plots. (write-only)")
        .def_prop_rw(
            "config",
            [](Plotter& self) -> PlotConfig {
                throw std::runtime_error("Property 'config' is write-only.");
            },
            [](Plotter& self, const PlotConfig& value) { self.config(value); },
            "Configuration of plots. (write-only)")
        .def(
            "write_background",
            [](Plotter& self, const RawImage& raw_image) {
                auto image = to_image(raw_image);
                self.write_background(image);
            },
            "image"_a,
            "Write background of a plot.\n\n"
            "The pixels of image are modified in place.")
        .def(
            "write_curve",
            [](Plotter& self, const PointList& point_list,
                const RGBColor& color, const RawImage& raw_image) {
                auto image = to_image(raw_image);
                self.write_curve(point_list.points, color, image);
            },
            "point_list"_a, "color"_a, "image"_a,
            "Write a curve on a plot.\n\n"
            "The pixels of image are modified in place.");
}
