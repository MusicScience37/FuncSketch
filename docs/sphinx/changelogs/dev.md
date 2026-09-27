# Changes to be released in the next version

## Features

- Added more built-in functions.
  - Inverse error functions. (`erf_inv`, `erfc_inv`)
  - Beta functions. (`beta`, `lbeta`, `ibeta`)

## Fixes

## Improvements

- Updated the grammar of function expressions.
  - Unary plus can be handled now. For example, `+x` is valid.
  - Multiple unary operators are prohibited. For example, `++x` and `--x` are invalid.
  - The power operator now correctly handles negative exponents. For example, `2 ** -x` is valid.

## Miscellaneous
