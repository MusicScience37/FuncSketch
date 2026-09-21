# Changes to be released in the next version

## Features

- Added support for Windows.
- Added interaction in plots.
  - Show mouse position.
  - Zoom in and out with the mouse wheel.
  - Pan by dragging with the left mouse button.
  - Zoom to a specific region by selecting it with the left mouse button and Ctrl key pressed.
- Added a command to save a plot as a PNG file.
- Made the image size configurable.

## Improvements

- Improved resolution of curve sampling.
- Made sampling more efficient.
  - In my development environment, time for sampling has been reduced by 25%.
- Made settings in the navigation bar collapsible.

## Miscellaneous

- Removed Eigen dependency.
- Updated benchmarks.
- Fixed warnings in GCC and MSVC.
- Configured SonarQube for static analysis.
- Refactored source code.
- Updated dependencies.
