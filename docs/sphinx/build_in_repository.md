# Build FuncSketch in Repository

## Dependencies

A development environment including dependencies can be created using
[Devcontainer of VSCode](https://code.visualstudio.com/docs/remote/containers).
The environment contains all dependencies required for development of FuncSketch
as follows:

- [Python](https://www.python.org/) 3.13
  - You may want to use [pyenv](https://github.com/pyenv/pyenv) optionally.
- [poetry](https://python-poetry.org/)
  - Required Python packages can be installed using poetry.
    Execute the command `poetry sync` on this directory.
- [CMake](https://cmake.org/)
- C++ 23 Compiler
  - Following compilers are tested in CI:
    - GCC 15
    - Clang 22
- Requirements only for documentation:
  - [Doxygen](https://www.doxygen.nl/index.html)
  - [Graphviz](https://graphviz.org/)
  - [PlantUML](https://plantuml.com)
    - Set `PLANTUML_JAR_PATH` environment variable to specify the place of `plantuml.jar` file.
  - Java runtime environment (JRE) for PlantUML.

## Build commands

After installation of dependencies,
you can build C++ module using CMake Tools in VSCode or executing the following commands in the terminal.

```bash
mkdir <repository-root>/build
cd <repository-root>/build
cmake ..
cmake --build .
```

Note that the build directory can be changed to any directory you like.

After the build, you can

- Run FuncSketch using `poetry run func_sketch` command.
- Run tests in C++ using `ctest` command in the build directory.
- Run tests in Python using `scripts/run_pytest.sh` script.
- Build documentation using `docs/build.sh` script.
