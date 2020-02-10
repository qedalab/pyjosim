#include <pybind11/pybind11.h>

namespace py = pybind11;

// Define submodules
namespace pyjosim {

}; // namespace pyjosim

// Define python module
PYBIND11_MODULE(pyjosim, m) {
  m.doc() = "JoSIM python interface";
}

