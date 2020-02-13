#include "JoSIM/Output.hpp"

#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace pyjosim {
void output(py::module &m)
{
    using namespace JoSIM;

    py::class_<Output>(m, "Output")
        .def(py::init([](Input &input, Matrix &matrix, Simulation &simulation) {
            Output output;
            output.write_output(input, matrix, simulation);
            return output;
        }));
}

} // namespace pyjosim
