# FuncSketch

A project to create a graphing calculator.

## Objectives

- Real-time graphing of functions
- Support for a wide range of mathematical functions,
  from basic ones like trigonometric functions to special functions such as Bessel functions.

## Architecture and Design

This project is made of a C++ module with Python bindings and Python scripts for the GUI.

Important design documents:

- `docs/sphinx/design_notes/classes_cpp.puml`: UML class diagram for C++ classes
- `docs/sphinx/design_notes/classes_python.puml`: UML class diagram for Python classes
- `docs/sphinx/design_notes/grammar.md`: Grammar for the parser
- `docs/sphinx/design_notes/modules.puml`: UML diagram for module structure

## Notes on C++ Source Code

- Source code is located in `cpp` directory, not `src` directory.
- Configuration files including `CMakeLists.txt` for C++ is located in the repository root.
- Build directory is `build/Debug` for debug build and `build/Release` for release build. Use `build/Debug` by default.
- Use `Boost.Math` for special functions not in C++ standard library.
- Use `fmt` for formatting strings.
- This project supports several platforms, so platform-dependent functions should not be called directly. Instead, use existing cross-platform library functions.
- Some classes are tested in Python, so run the Python tests after changing C++ code.

## Notes on Python Source Code

- Use `Ruff` for linting, not for formatting.
- See `scripts/run_pytest.sh` for the appropriate way to run pytest.
- When testing plotting of functions with finite domain, specify the range with a larger domain than the function's domain to check that the function is not plotted outside its domain.
  Also, singularities of functions should be included in the range to check behavior of the function near singularities.
- System tests are implemented in the `system_tests` directory separately from the regular tests, and can be run using `scripts/run_system_test.sh`, which has the required setup for running system tests.
