from conans import ConanFile
from conan.tools.cmake import CMake
from conan.tools.layout import cmake_layout
from conan.tools.files import copy
import os
import shutil
import json
import subprocess


class Assignment(ConanFile):
    scm = {
        "type": "git",
        "url": "auto",
        "revision": "auto"
    }

    name = "Assignment"
    version = "0.0.0"
    settings = "os", "compiler", "build_type", "arch"

    options = {}
    default_options = {}

    generators = "CMakeToolchain", "CMakeDeps"
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "test/*", "*.md", "*.cmake"

    def requirements(self):
        pass

    def configure(self):
        pass

    def _fix_cmake_presets(self):
        # remove the CMakeUserPresets file until Microsoft actually updates the file
        print("Copying CmakePresets.json to the root dir")
        conanfile_dir = os.path.dirname(os.path.realpath(__file__))

        # skips running this code is conan create . or equivalent is called as a CMakeUserPresets.json will not be created
        if not os.path.exists(os.path.join(conanfile_dir, 'CMakeUserPresets.json')):
            return

        # read the cmake user presets file, get the path to the CMakePresets.json file, and copy it to the
        # root folder of the project for VSCODE / Visual studio integration
        # this is only needed until Microsoft fixes the 'include' keyword in CMakePresets
        with open(os.path.join(conanfile_dir, 'CMakeUserPresets.json')) as json_file:
            data = json.load(json_file)
            cmake_presets_file = data['include'][0]

        shutil.copy(
            cmake_presets_file,
            os.path.join(conanfile_dir, "CMakeUserPresets.json")
        )

    def generate(self):
        self._fix_cmake_presets()

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
