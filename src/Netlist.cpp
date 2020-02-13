#include "JoSIM/Netlist.hpp"

#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace pyjosim {
void netlist(py::module &m) {
  using namespace JoSIM;

  py::class_<Netlist>(m, "Netlist")
    .def("expand_subcircuits", &Netlist::expand_subcircuits)
    .def("expand_maindesign", &Netlist::expand_maindesign);
}

} // namespace pyjosim
