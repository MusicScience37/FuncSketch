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

## Notes on Python Source Codes

- Use Python 3.13.
- Use tools `black`, `isort`, `pylint`, `flake8`, and `mypy`.
- Use `pytest` for unit tests.
- Comments should be in Google style.
