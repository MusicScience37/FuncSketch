# FuncSketch

A project to create a graphing calculator.

## Objectives

- Real-time graphing of functions
- Support for a wide range of mathematical functions,
  from basic ones like trigonometric functions to special functions such as Bessel functions.

## Directory Structure

This project is made of a C++ module with Python bindings and Python scripts for the GUI.

Directory structure:

- `cpp`: C++ source codes
  - `cmake`: Scripts for CMake
  - `include`: Header files
  - `src`: Source files
  - `tests`: Tests
- `docs`: Documentation
  - Some important files:
    - `sphinx/design_notes/classes_cpp.puml`: UML class diagram for C++ classes
    - `sphinx/design_notes/classes_python.puml`: UML class diagram for Python classes
    - `sphinx/design_notes/grammar.md`: Grammar for the parser
    - `sphinx/design_notes/modules.puml`: UML diagram for module structure
- `src`: Python source codes
  - `func_sketch`: Python package
    - `_gui`: Package directory for GUI
    - `_impl`: Package directory for the internal logic
    - `_cpp`: C++ extension module built from source codes in `cpp` directory
- `tests`: Tests of Python source codes

## Notes on C++ Source Codes

- Use C++ 23 standard.
- Use CMake.
  - Build directory is `build/Debug` for debug build and `build/Release` for release build. Use `build/Debug` by default.
- Use `clang-format` and `clang-tidy`.
- Use `Catch2` and `ApprovalTests` for unit tests.
- Use `nanobind` for Python bindings.
- Use `Boost.Spirit` for parsing.
- Use `Boost.Math` for special functions not in C++ standard library.
- Use `fmt` for formatting strings.
- Use `OpenCV` for writing plots.
- This project will support several platforms in the future, so platform-dependent functions should not be called directly. Instead, use existing cross-platform library functions.
- Tests of plotting is done in Python, so run tests in Python after changing plotting-related C++ codes.

## Notes on Python Source Codes

- Use Python 3.13.
- Use tools `black`, `isort`, `pylint`, `flake8`, and `mypy`.
- Use `pytest` for unit tests.
  - See `scripts/run_pytest.sh` for the appropriate way to run pytest.
  - When testing plotting of functions with finite domain, specify the range with a larger domain than the function's domain to check that the function is not plotted outside its domain.
    Also, singularities of functions should be included in the range to check behavior of the function near singularities.
- Comments should be in Google style.

## Notes on Sphinx Documentation

- Use docs/build.sh to build the documentation.
  This script runs `sphinx-build` with required arguments and environment variables.
  And it also runs `sphinx-apidoc` to generate API reference included in the documentation.
- conf.py defines a custom directive `funcsketch:function` for documenting functions in FuncSketch.
  Functions documented with `funcsketch:function` directive can be referenced with `:funcsketch:func:` role.
- Documentation can be written also in Markdown format using `myst_parser` extension.
- For natural logarithm function, use `log` instead of `ln`.
