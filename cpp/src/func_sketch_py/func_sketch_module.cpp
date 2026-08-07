#include <cstdint>
#include <utility>
#include <vector>

#include <fmt/format.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/pair.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

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
        .def(nanobind::init<>(), "Constructor.")
        .def(
            "__call__",
            [](const ExpressionParser& self,
                const std::string& expression_str) {
                return self(expression_str);
            },
            "expression_str"_a, "Parse a string into an Expression object.");

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
        // TODO Add properties.
        ;

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
            [](const Plotter& self, const RawImage& raw_image) {
                auto image = to_image(raw_image);
                self.write_background(image);
            },
            "image"_a,
            "Write background of a plot.\n\n"
            "The pixels of image are modified in place.")
        .def(
            "write_curve",
            [](const Plotter& self, const PointList& point_list,
                const RGBColor& color, const RawImage& raw_image) {
                auto image = to_image(raw_image);
                self.write_curve(point_list.points, color, image);
            },
            "point_list"_a, "color"_a, "image"_a,
            "Write a curve on a plot.\n\n"
            "The pixels of image are modified in place.");
}
