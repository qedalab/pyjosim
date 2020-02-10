#include "JoSIM/Parameters.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::unordered_map<JoSIM::ParameterName, Parameter>);

namespace pyjosim {

void parameters(py::module &m) {
  using namespace JoSIM;
  namespace py = pybind11;

  py::bind_map<std::unordered_map<ParameterName, Parameter>>(m, "Parameters")
      .def("parse", [](std::unordered_map<ParameterName, Parameter> &self) {
        Parameters::parse_parameters(self);
      });

  py::class_<Parameter>(m, "Parameter")
      .def("set_expression", &Parameter::set_expression)
      .def("set_value", &Parameter::set_value)
      .def("get_expression", &Parameter::get_expression)
      .def("get_value", &Parameter::get_value);
}

} // namespace pyjosim
