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

/*!
 * \brief Struct of lists of points for reducing the number of type conversions
 * between C++ and Python.
 */
struct PointList {
    //! Points.
    std::vector<func_sketch::plotter::Point> points;
};

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
        .def(nanobind::init<double, double, double>(), "r"_a, "g"_a, "b"_a,
            "Constructor.")
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
            [](const FunctionSampler& self) {
                throw std::runtime_error("Getting range is not implemented.");
            },
            [](FunctionSampler& self, const PlotRange& value) {
                self.range(value);
            },
            "Range of plots.")
        .def_prop_rw(
            "config",
            [](const FunctionSampler& self) {
                throw std::runtime_error("Getting config is not implemented.");
            },
            [](FunctionSampler& self, const PlotConfig& value) {
                self.config(value);
            },
            "Configuration of plots.")
        .def(
            "__call__",
            [](const FunctionSampler& self, const ExpressionPtr& function) {
                return PointList{self(*function)};
            },
            "function"_a, "Sample a function and return a list of points.");

    using func_sketch::plotter::Image;
    using func_sketch::plotter::Plotter;
    using RawImage = nanobind::ndarray<uint8_t, nanobind::shape<-1, -1, 3>,
        nanobind::c_contig>;
    nanobind::class_<Plotter>(m, "Plotter", "Class for plotting.")
        .def(nanobind::init<PlotRange, PlotConfig>(), "range"_a, "config"_a,
            "Constructor.")
        .def_prop_rw(
            "range",
            [](const Plotter& self) {
                throw std::runtime_error("Getting range is not implemented.");
            },
            [](Plotter& self, const PlotRange& value) { self.range(value); },
            "Range of plots.")
        .def_prop_rw(
            "config",
            [](const Plotter& self) {
                throw std::runtime_error("Getting config is not implemented.");
            },
            [](Plotter& self, const PlotConfig& value) { self.config(value); },
            "Configuration of plots.")
        .def(
            "write_background",
            [](const Plotter& self, const RawImage& raw_image) {
                Image image(static_cast<int>(raw_image.shape(0)),
                    static_cast<int>(raw_image.shape(1)), CV_8UC3,
                    raw_image.data());
                self.write_background(image);
            },
            "image"_a, "Write background of a plot.")
        .def(
            "write_curve",
            [](const Plotter& self, const PointList& point_list,
                const RGBColor& color, const RawImage& raw_image) {
                Image image(static_cast<int>(raw_image.shape(0)),
                    static_cast<int>(raw_image.shape(1)), CV_8UC3,
                    raw_image.data());
                self.write_curve(point_list.points, color, image);
            },
            "point_list"_a, "color"_a, "image"_a, "Write a curve on a plot.");
}
