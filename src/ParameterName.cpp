#include "JoSIM/ParameterName.hpp"

#include <pybind11/pybind11.h>
namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<std::string>);

namespace pyjosim {

void parameter_name(py::module &m)
{
    using namespace JoSIM;

    py::class_<ParameterName>(m, "ParameterName")
        .def(py::init<std::string, std::string>())
        .def("name", &ParameterName::name)
        .def("subcircuit", &ParameterName::subcircuit)
        .def("__eq__", &ParameterName::operator==)
        .def("__hash__", [](ParameterName &parameter_name) {
            return std::hash<ParameterName>()(parameter_name);
        });
}

} // namespace pyjosim
