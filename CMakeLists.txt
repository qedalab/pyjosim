cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(pyjosim
        VERSION 2.3
                DESCRIPTION
                "Python bindings for JoSIM"
                HOMEPAGE_URL
                "https://github.com/pleroux0/pyjosim"
        LANGUAGES CXX)

# Include cmake scripts
include(${PROJECT_SOURCE_DIR}/cmake/conan.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/warnings.cmake)

find_package(pybind11 REQUIRED)
find_package(CMakeSuiteSparseConfig REQUIRED)
find_package(CMakeSuiteSparseAMD REQUIRED)
find_package(CMakeSuiteSparseCOLAMD REQUIRED)
find_package(CMakeSuiteSparseBTF REQUIRED)
find_package(CMakeSuiteSparseKLU REQUIRED)
find_package(josim REQUIRED)

pybind11_add_module(pyjosim
                    SHARED
                    THIN_LTO
                    src/pyjosim.cpp
                    src/j_input.cpp
                    src/j_output.cpp
                    src/j_matrix.cpp
                    src/j_simulation.cpp)

# Add include directories
target_include_directories(
  pyjosim
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>)

target_link_libraries(pyjosim PRIVATE josim::josim)
