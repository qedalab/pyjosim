#include "JoSIM/InputType.hpp"

#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

namespace pyjosim {

void input_type(py::module &m)
{
    using namespace JoSIM;

    py::enum_<InputType>(m, "InputType")
        .value("Jsim", InputType::Jsim)
        .value("WrSpice", InputType::WrSpice);
}

} // namespace pyjosim
