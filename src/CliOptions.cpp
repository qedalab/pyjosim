#include "JoSIM/CliOptions.hpp"

#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

namespace pyjosim {
void cli_options(py::module &m) {
  using namespace JoSIM;

  py::class_<CliOptions>(m, "CliOptions")
      .def(py::init([](std::vector<std::string> args) {
        // In case of help
        py::scoped_ostream_redirect cout;
        py::scoped_estream_redirect cerr;

        // Convert vector of strings to argc, argv
        int argc = args.size() + 1;
        const char *josim_cstr = "JoSIM";
        auto argv = std::make_unique<const char *[]>(argc);

        argv[0] = josim_cstr;
        for (std::size_t i = 0; i < args.size(); i++)
          argv[i + 1] = args[i].c_str();

        return CliOptions::parse(argc, argv.get());
      }))
      .def_readonly("cir_file_name", &CliOptions::cir_file_name)
      .def_readonly("input_type", &CliOptions::input_type)
      .def_readonly("analysis_type", &CliOptions::analysis_type)
      .def_readonly("verbose", &CliOptions::verbose)
      .def_readonly("parallel", &CliOptions::parallel)
      .def_readonly("standardin", &CliOptions::standardin)
      .def_readonly("output_file_name", &CliOptions::output_file_name)
      .def_readonly("output_file_type", &CliOptions::output_file_type)
      .def_static("display_help",
                  []() {
                    py::scoped_ostream_redirect cout;
                    py::scoped_estream_redirect cerr;
                    CliOptions::display_help();
                  })
      .def_static("version_info",
                  []() {
                    py::scoped_ostream_redirect cout;
                    py::scoped_estream_redirect cerr;
                    CliOptions::version_info();
                  });
}

} // namespace pyjosim
