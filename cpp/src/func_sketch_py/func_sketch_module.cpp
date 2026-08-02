#include <fmt/format.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include "func_sketch/expressions/expression_ptr.h"
#include "func_sketch/parser/expression_parser.h"

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
}
