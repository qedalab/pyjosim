#include <pybind11/pybind11.h>

namespace py = pybind11;

// Define submodules
namespace pyjosim {

void cli_options(py::module& m);

}; // namespace pyjosim

// Define python module
PYBIND11_MODULE(pyjosim, m) {
  using namespace pyjosim;

  m.doc() = "JoSIM python interface";

  cli_options(m);
}

