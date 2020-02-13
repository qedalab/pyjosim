#include "JoSIM/Input.hpp"
#include "JoSIM/Model.hpp"

#include <pybind11/pybind11.h>
namespace py = pybind11;

namespace pyjosim {

void input(py::module &m)
{
    using namespace JoSIM;

    py::class_<Input>(m, "Input")
        .def(py::init<AnalysisType, InputType, bool>())
        .def("identify_simulation",
             [](Input &self) {
                 Transient::identify_simulation(self.controls, self.transSim);
             })
        .def_readwrite("parameters", &Input::parameters)
        .def_readwrite("netlist", &Input::netlist)
        .def("parse_file",
             [](Input &self, std::string path) { self.parse_file(path); })
        .def("parse_models", [](Input &self) {
            for (const auto &model : self.netlist.models) {
                auto pair = std::make_pair(model.second, model.first.second);
                Model::parse_model(pair, self.netlist.models_new,
                                   self.parameters);
            }
        });
}

} // namespace pyjosim
