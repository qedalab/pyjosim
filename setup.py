""" Custom build.py to enable building with CMake from Poetry """
import os
import sys
import re
import subprocess
from distutils.version import LooseVersion
from typing import Optional, List
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext

import attr

if sys.version_info < (3, 6):
    print("Python 3.6 or higher is required, please upgrade.")
    sys.exit(-1)

REQUIREMENTS = ["numpy"]
BUILD_REQUIREMENTS = ["setuptools", "wheels", "cmake>=3.13", "ninja"]


@attr.s(auto_attribs=True, slots=True, frozen=True, init=False)
class CMakeBuildType:
    """ CMake build class"""

    build_type: str

    def __init__(self, build_type: str, custom: bool = False):

        if not custom and build_type.upper() not in [
            "DEBUG",
            "RELEASE",
            "MINSIZEREL",
            "RELWITHDEBINFO",
        ]:
            print("ERROR: invalid build type: '{}'".format(build_type))
            exit(-1)

        object.__setattr__(self, "build_type", build_type)


def get_cmake_executable():
    cmake3_version = get_cmake_version("cmake3")
    cmake_version = get_cmake_version("cmake")

    # Use newer cmake
    if cmake3_version > cmake_version:
        return "cmake3"
    else:
        return "cmake"


def get_cmake_version(cmake_exe: str = "cmake"):
    """ Returns the CMake version or None if CMake is not found """
    try:
        out = subprocess.check_output([cmake_exe, "--version"])
    except OSError:
        return None

    version_string = re.search(r"version\s*([\d.]+)", out.decode()).group(1)
    return LooseVersion(version_string)


class CMakeExtension(Extension):
    """ Setuptools CMake Extension """

    _build_type: Optional[CMakeBuildType]
    _minimum_cmake_version: LooseVersion
    _cmake_version: LooseVersion
    _source_directory: str
    _cmake_exe: str

    def __init__(
        self,
        name,
        source_directory="",
        build_type: CMakeBuildType = None,
        minimum_cmake_version: str = "3.13",
        cmake_exe: Optional[str] = None
    ):
        # Set CMake executable
        if cmake_exe is not None:
            self._cmake_exe = cmake_exe
        else:
            self._cmake_exe = get_cmake_executable()
        print("CMake executable {}".format(self._cmake_exe))

        self._update_cmake_version(minimum_cmake_version)
        self._set_source_directory(source_directory)

        self._build_type = build_type

        Extension.__init__(self, name, sources=[])

    def _set_source_directory(self, source_directory):
        self._source_directory = os.path.abspath(source_directory)

    def _update_cmake_version(self, minimum_cmake_version):
        """ Checks that minimum cmake version and sets version info """
        cmake_version = get_cmake_version(self._cmake_exe)

        # Ensure that CMake is found
        if cmake_version is None:
            print("ERROR: CMake executable not found.")
            exit(-1)

        # Ensure that the minimum cmake version
        if cmake_version < minimum_cmake_version:
            print("ERROR: Found CMake is too old")
            print("  found={}".format(cmake_version))
            print("  required={}".format(minimum_cmake_version))
            exit(-1)

        self._minimum_cmake_version = LooseVersion(minimum_cmake_version)
        self._cmake_version = cmake_version

    def get_build_type(self):
        """ Get the cmake build type """
        return self._build_type

    def get_source_directory(self):
        """ Get the cmake source directory """
        return self._source_directory


class CMakeBuild(build_ext):
    """ CMake Extension Builder """

    def run(self):
        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext: CMakeExtension):
        if not isinstance(ext, CMakeExtension):
            print("ERROR: CMakeBuild cannot build non CMakeExtension")
            exit(-1)

        extension_directory = os.path.abspath(
            os.path.dirname(self.get_ext_fullpath(ext.name))
        )

        cmake_args = [
            ext.get_source_directory(),
            self._get_build_type_flag(ext.get_build_type()),
            "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={}".format(extension_directory),
        ]

        self._make_build_dir()
        self._conan_install(ext._source_directory)
        self._cmake_configure(ext._cmake_exe, cmake_args)
        self._cmake_build(ext._cmake_exe)
        # self._install()

    def _conan_install(self, source_directory):
        subprocess.check_call(
            ["conan", "install", source_directory], cwd=self.build_temp
        )

    def _get_build_type_flag(self, build_type: Optional[CMakeBuildType]):
        """ Get CMake build type flag """

        if build_type is None:
            build_type_str = "Debug" if self.debug else "Release"
            build_type = CMakeBuildType(build_type_str)

        return "-DCMAKE_BUILD_TYPE={}".format(build_type.build_type)

    def _make_build_dir(self):
        """ Makes the build directory if it doesn't exist """
        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)

    def _cmake_configure(self, cmake_exe: str, cmake_args: List[str]):
        """ Configures the project """
        subprocess.check_call([cmake_exe] + cmake_args, cwd=self.build_temp)

    def _cmake_build(self, cmake_exe: str, build_args: List[str] = None):
        """ Build project """

        if build_args is None:
            build_args = []

        subprocess.check_call(
            [cmake_exe, "--build", "."] + build_args, cwd=self.build_temp
        )

    def _install(self):
        pass


setup(
    # Meta data
    name="pyjosim",
    version="2.3",
    author="Paul le Roux",
    author_email="pleroux0@outlook.com",
    description="Python bindings for JoSIM",
    # Package data
    ext_modules=[CMakeExtension("pyjosim", minimum_cmake_version="3.13")],
    cmdclass=dict(build_ext=CMakeBuild),
    zip_safe=False
)
