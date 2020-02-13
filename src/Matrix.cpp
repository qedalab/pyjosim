#include "./scoped_cout_null.hpp"

#include "JoSIM/Matrix.hpp"

#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace pyjosim {
void matrix(py::module &m)
{
    using namespace JoSIM;

    py::class_<Matrix>(m, "Matrix")
        .def(py::init([](Input &input) {
                 scoped_cout_null cout;
                 py::scoped_estream_redirect cerr;
                 Matrix matrix;
                 matrix.create_matrix(input);
                 find_relevant_traces(input.controls, matrix);
                 return matrix;
             }),
             py::keep_alive<1, 2>());
}

} // namespace pyjosim
