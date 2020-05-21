#include "JoSIM/Input.hpp"
#include "JoSIM/Model.hpp"

#include <pybind11/pybind11.h>
//#include <pybind11/stl.h>
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
        .def("clone", [](const Input &input) -> Input { return input; })
        .def("parse_models",
             [](Input &self) {
                 for (const auto &model : self.netlist.models) {
                     auto pair =
                         std::make_pair(model.second, model.first.second);
                     Model::parse_model(pair, self.netlist.models_new,
                                        self.parameters);
                 }
             })
        .def_property_readonly("controls",
                               [](Input &input) { return input.controls; })
        .def("clear_all_plots",
             [](Input &input) {
                 input.controls.erase(std::remove_if(
                     input.controls.begin(), input.controls.end(),
                     [](const std::string &str) {
                         for (const auto value : {"PLOT", "SAVE", "PRINT"}) {
                             if (str.find(value) != std::string::npos)
                                 return true;
                         }

                         return false;
                     }), input.controls.end());
             })
        .def("add_plot", [](Input &input, const std::string &str) {
            input.controls.emplace_back(
                std::move(std::string(".PRINT ").append(str)));
        });
}

} // namespace pyjosim
