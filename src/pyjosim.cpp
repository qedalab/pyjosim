#include <pybind11/pybind11.h>

namespace py = pybind11;

// Define submodules
namespace pyjosim {

void analysis_type(py::module &m);
void cli_options(py::module& m);
void input(py::module& m);
void input_type(py::module& m);
void netlist(py::module& m);
void parameter_name(py::module& m);
void parameters(py::module& m);

}; // namespace pyjosim

// Define python module
PYBIND11_MODULE(pyjosim, m) {
  using namespace pyjosim;

  m.doc() = "JoSIM python interface";

  analysis_type(m);
  cli_options(m);
  input(m);
  input_type(m);
  netlist(m);
  parameter_name(m);
  parameters(m);
}

