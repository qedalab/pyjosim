#include "JoSIM/Input.hpp"

#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace pyjosim {

void input(py::module &m) {
  using namespace JoSIM;

  py::class_<Input>(m, "Input")
      .def(py::init<AnalysisType, InputType, bool>())
      .def_readwrite("parameters", &Input::parameters)
      .def("parse_file", [](Input &self, std::string path) {
        Input::parse_file(path, self);
      });
}

} // namespace pyjosim
