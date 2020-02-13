#include "JoSIM/Output.hpp"

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<JoSIM::Trace>);

namespace pyjosim {
void output(py::module &m)
{
    using namespace JoSIM;

    py::class_<Trace>(m, "Trace")
        .def_readonly("type", &Trace::type_)
        .def_readonly("name", &Trace::name_)
        .def_property_readonly("data", [](Trace &trace) {
            auto &vec = trace.data_;
            double *data = vec.data();
            size_t size = vec.size();
            return py::array_t<double>(size, data);
        });

    py::bind_vector<std::vector<Trace>>(m, "Traces");

    py::class_<Output>(m, "Output")
        .def(py::init([](Input &input, Matrix &matrix, Simulation &simulation) {
            Output output;
            output.write_output(input, matrix, simulation);
            return output;
        }))
        .def_readonly("traces", &Output::traces);
}

} // namespace pyjosim
