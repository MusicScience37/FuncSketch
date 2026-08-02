#include <utility>
#include <vector>

#include <fmt/format.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
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
    using func_sketch::expressions::ExpressionPtr;
    nanobind::class_<ExpressionPtr>(m, "Expression")
        .def("__str__",
            [](const ExpressionPtr& self) { return fmt::format("{}", *self); });

    using func_sketch::parser::ExpressionParser;
    nanobind::class_<ExpressionParser>(m, "ExpressionParser")
        .def(nanobind::init<>())
        .def("__call__",
            [](const ExpressionParser& self,
                const std::string& expression_str) {
                return self(expression_str);
            });

    using func_sketch::plotter::RGBColor;
    nanobind::class_<RGBColor>(m, "RGBColor")
        .def(nanobind::init<double, double, double>())
        .def_rw("r", &RGBColor::r)
        .def_rw("g", &RGBColor::g)
        .def_rw("b", &RGBColor::b);

    using func_sketch::plotter::Point;
    nanobind::class_<Point>(m, "Point")
        .def(nanobind::init<double, double>())
        .def_rw("x", &Point::x)
        .def_rw("y", &Point::y);

    nanobind::class_<PointList>(m, "PointList")
        .def(nanobind::init<>())
        .def_rw("points", &PointList::points);

    using func_sketch::plotter::PlotRange;
    nanobind::class_<PlotRange>(m, "PlotRange")
        .def(nanobind::init<std::pair<double, double>,
            std::pair<double, double>>())
        .def_prop_ro("x_range", &PlotRange::x_range)
        .def_prop_ro("y_range", &PlotRange::y_range);

    using func_sketch::plotter::PlotConfig;
    nanobind::class_<PlotConfig>(m, "PlotConfig").def(nanobind::init<>())
        // TODO Add properties.
        ;

    using func_sketch::plotter::FunctionSampler;
    nanobind::class_<FunctionSampler>(m, "FunctionSampler")
        .def(nanobind::init<PlotRange, PlotConfig>())
        .def_prop_rw(
            "range",
            [](const FunctionSampler& self) {
                throw std::runtime_error("Getting range is not implemented.");
            },
            [](FunctionSampler& self, const PlotRange& value) {
                self.range(value);
            })
        .def_prop_rw(
            "config",
            [](const FunctionSampler& self) {
                throw std::runtime_error("Getting config is not implemented.");
            },
            [](FunctionSampler& self, const PlotConfig& value) {
                self.config(value);
            })
        .def("__call__",
            [](const FunctionSampler& self, const ExpressionPtr& function) {
                return PointList{self(*function)};
            });

    using func_sketch::plotter::Image;
    using func_sketch::plotter::Plotter;
    using RawImage = nanobind::ndarray<uint8_t, nanobind::shape<-1, -1, 3>,
        nanobind::c_contig>;
    nanobind::class_<Plotter>(m, "Plotter")
        .def(nanobind::init<PlotRange, PlotConfig>())
        .def_prop_rw(
            "range",
            [](const Plotter& self) {
                throw std::runtime_error("Getting range is not implemented.");
            },
            [](Plotter& self, const PlotRange& value) { self.range(value); })
        .def_prop_rw(
            "config",
            [](const Plotter& self) {
                throw std::runtime_error("Getting config is not implemented.");
            },
            [](Plotter& self, const PlotConfig& value) { self.config(value); })
        .def("write_background",
            [](const Plotter& self, const RawImage& raw_image) {
                Image image(static_cast<int>(raw_image.shape(0)),
                    static_cast<int>(raw_image.shape(1)), CV_8UC3,
                    raw_image.data());
                self.write_background(image);
            })
        .def("write_curve",
            [](const Plotter& self, const PointList& point_list,
                const RGBColor& color, const RawImage& raw_image) {
                Image image(static_cast<int>(raw_image.shape(0)),
                    static_cast<int>(raw_image.shape(1)), CV_8UC3,
                    raw_image.data());
                self.write_curve(point_list.points, color, image);
            });
}
