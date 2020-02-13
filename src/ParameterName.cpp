#include "JoSIM/ParameterName.hpp"

#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace pyjosim {

void parameter_name(py::module &m)
{
    using namespace JoSIM;

    py::class_<ParameterName>(m, "ParameterName")
        .def(py::init<std::string, std::string>())
        .def("name", &ParameterName::name)
        .def("subcircuit", &ParameterName::subcircuit)
        .def("__eq__", &ParameterName::operator==);
}

} // namespace pyjosim
