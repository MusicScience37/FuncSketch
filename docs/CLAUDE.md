# Notes on Sphinx Documentation

- Use docs/build.sh to build the documentation.
  This script runs `sphinx-build` with required arguments and environment variables.
  It also runs `sphinx-apidoc` to generate the API reference included in the documentation.
- conf.py defines a custom directive `funcsketch:function` for documenting functions in FuncSketch.
  Functions documented with `funcsketch:function` directive can be referenced with `:funcsketch:func:` role.
- Documentation can also be written in Markdown using the `myst_parser` extension.
- For natural logarithm function, use `log` instead of `ln`.
