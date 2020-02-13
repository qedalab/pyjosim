#include "./scoped_cout_null.hpp"

#include "JoSIM/Simulation.hpp"

#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>

#include <iostream>

namespace py = pybind11;

namespace pyjosim {
void simulation(py::module &m)
{
    using namespace JoSIM;

    py::class_<Simulation>(m, "Simulation")
        .def(py::init([](Input &input, Matrix &matrix) {
                 scoped_cout_null cout;
                 py::scoped_estream_redirect cerr;
                 Simulation simulation(input, matrix);
                 return simulation;
             }),
             py::keep_alive<1, 2>(), py::keep_alive<1, 3>());
}

} // namespace pyjosim
