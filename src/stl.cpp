#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

#include <vector>
#include <string>

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<std::string>);

namespace pyjosim {
void stl(py::module &m)
{
  py::bind_vector<std::vector<std::string>>(m, "StringVector");
}

} // namespace pyjosim
