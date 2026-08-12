# Build FuncSketch in Repository

## Dependencies

A development environment including dependencies can be created using
[Devcontainer of VSCode](https://code.visualstudio.com/docs/remote/containers).
The environment contains all dependencies required for development of FuncSketch
as follows:

- [Python](https://www.python.org/) 3.13
  - You may want to use [pyenv](https://github.com/pyenv/pyenv).
- [poetry](https://python-poetry.org/)
  - Required Python packages can be installed using poetry.
    Execute the command `poetry sync` on this directory.
- [CMake](https://cmake.org/)
- C++ 23 Compiler
  - Following compilers are tested in CI:
    - GCC 15
    - Clang 22
- [Doxygen](https://www.doxygen.nl/index.html) (for documentation)
- [Graphviz](https://graphviz.org/) (for documentation)
- [PlantUML](https://plantuml.com) (for documentation)
  - Set `PLANTUML_JAR_PATH` environment variable to specify the place of `plantuml.jar` file.
- Java runtime environment (JRE) for PlantUML. (for documentation)

## Build commands

After installation of dependencies,
execute the following commands to build the C++ module:

1. Download vcpkg if you haven't already.

   ```bash
   git submodule update --init
   ```

2. Build C++ module.

   CMake tools in VSCode can build the C++ module.
   Alternatively, you can build it from the command line as follows:

   ```bash
   poetry sync
   mkdir <repository-root>/build
   cd <repository-root>/build
   cmake .. -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake
   cmake --build .
   ```

After the build, you can

- Run FuncSketch using `poetry run func_sketch` command.
- Run tests in C++ using `ctest` command in the build directory.
- Run tests in Python using `scripts/run_pytest.sh` script.
- Build documentation using `docs/build.sh` script.
