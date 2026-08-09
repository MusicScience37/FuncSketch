# Mathematical Functions to be Implemented

## Basic Functions

Basic functions in `<cmath>` header in C++11:

| Type          | Function                                                        | Name in FuncSketch | In C++        | In Python     |
| :------------ | :-------------------------------------------------------------- | :----------------- | :------------ | :------------ |
| Exponential   | Exponential function $e^x$                                      | `exp`              | `std::exp`    | `math.exp`    |
| Exponential   | 2 raised to the given power $2^x$                               | `exp2`             | `std::exp2`   | `math.exp2`   |
| Exponential   | Exponential function minus 1 $e^x - 1$                          | `expm1`            | `std::expm1`  | `math.expm1`  |
| Logarithm     | Natural logarithm function $\log{x}$                            | `log`              | `std::log`    | `math.log`    |
| Logarithm     | Natural logarithm of 1 plus x $\log{(1+x)}$                     | `log1p`            | `std::log1p`  | `math.log1p`  |
| Logarithm     | Common logarithm function $\log_{10}{x}$                        | `log10`            | `std::log10`  | `math.log10`  |
| Logarithm     | Base 2 logarithm function $\log_{2}{x}$                         | `log2`             | `std::log2`   | `math.log2`   |
| Power         | Power function $x^y$                                            | `pow`              | `std::pow`    | `math.pow`    |
| Power         | Square root function $\sqrt{x}$                                 | `sqrt`             | `std::sqrt`   | `math.sqrt`   |
| Power         | Cube root function $\sqrt[3]{x}$                                | `cbrt`             | `std::cbrt`   | `math.cbrt`   |
| Trigonometric | Sine function $\sin{x}$                                         | `sin`              | `std::sin`    | `math.sin`    |
| Trigonometric | Cosine function $\cos{x}$                                       | `cos`              | `std::cos`    | `math.cos`    |
| Trigonometric | Tangent function $\tan{x}$                                      | `tan`              | `std::tan`    | `math.tan`    |
| Trigonometric | Arcsine function $\arcsin{x}$                                   | `asin`             | `std::asin`   | `math.asin`   |
| Trigonometric | Arccosine function $\arccos{x}$                                 | `acos`             | `std::acos`   | `math.acos`   |
| Trigonometric | Arctangent function $\arctan{x}$                                | `atan`             | `std::atan`   | `math.atan`   |
| Trigonometric | Arctangent function on two variables                            | `atan2`            | `std::atan2`  | `math.atan2`  |
| Hyperbolic    | Hyperbolic sine function $\sinh{x}$                             | `sinh`             | `std::sinh`   | `math.sinh`   |
| Hyperbolic    | Hyperbolic cosine function $\cosh{x}$                           | `cosh`             | `std::cosh`   | `math.cosh`   |
| Hyperbolic    | Hyperbolic tangent function $\tanh{x}$                          | `tanh`             | `std::tanh`   | `math.tanh`   |
| Hyperbolic    | Hyperbolic arcsine function $\mathrm{asinh}\,{x}$               | `asinh`            | `std::asinh`  | `math.asinh`  |
| Hyperbolic    | Hyperbolic arccosine function $\mathrm{acosh}\,{x}$             | `acosh`            | `std::acosh`  | `math.acosh`  |
| Hyperbolic    | Hyperbolic arctangent function $\mathrm{atanh}\,{x}$            | `atanh`            | `std::atanh`  | `math.atanh`  |
| Error         | Error function $\mathrm{erf}\,{x}$                              | `erf`              | `std::erf`    | `math.erf`    |
| Error         | Complementary error function $\mathrm{erfc}\,{x}$               | `erfc`             | `std::erfc`   | `math.erfc`   |
| Gamma         | Gamma function $\Gamma{(x)}$                                    | `gamma`            | `std::tgamma` | `math.gamma`  |
| Gamma         | Natural logarithm of the gamma function $\log{\|\Gamma{(x)}\|}$ | `lgamma`           | `std::lgamma` | `math.lgamma` |
| Misc          | Absolute value function $\|x\|$                                 | `abs`              | `std::abs`    | `math.fabs`   |
| Misc          | Ceiling function $\lceil{x}\rceil$                              | `ceil`             | `std::ceil`   | `math.ceil`   |
| Misc          | Floor function $\lfloor{x}\rfloor$                              | `floor`            | `std::floor`  | `math.floor`  |
| Misc          | Truncation function $\mathrm{trunc}\,{x}$                       | `trunc`            | `std::trunc`  | `math.trunc`  |

- `pow` and `atan2` functions have two arguments, whereas all other functions have one argument.
- All functions will be calculated using floating-point numbers.
- Some functions in `<cmath>` header have been omitted because of less importance for graphing calculators.

## Special Functions

Candidate of implementation of special functions are as follows:

| Type                 | Function                                                         | Name in FuncSketch | In C++                | In Python |
| :------------------- | :--------------------------------------------------------------- | :----------------- | :-------------------- | :-------- |
| Beta                 | Beta function $B{(x, y)}$                                        | (TODO)             | `std::beta`           | (TODO)    |
| Bessel               | Cylindrical Bessel function $J_{\nu}{(x)}$                       | (TODO)             | `std::cyl_bessel_j`   | (TODO)    |
| Bessel               | Cylindrical Neumann function $Y_{\nu}{(x)}$                      | (TODO)             | `std::cyl_neumann`    | (TODO)    |
| Bessel               | Regular modified cylindrical Bessel function $I_{\nu}{(x)}$      | (TODO)             | `std::cyl_bessel_i`   | (TODO)    |
| Bessel               | Irregular modified cylindrical Bessel function $K_{\nu}{(x)}$    | (TODO)             | `std::cyl_bessel_k`   | (TODO)    |
| Bessel               | Spherical Bessel function $j_n{(x)}$                             | (TODO)             | `std::sph_bessel`     | (TODO)    |
| Bessel               | Spherical Neumann function $y_n{(x)}$                            | (TODO)             | `std::sph_neumann`    | (TODO)    |
| Hermite              | Hermite polynomial $H_n{(x)}$ (physicist's)                      | (TODO)             | `std::hermite`        | (TODO)    |
| Laguerre             | Laguerre polynomial $L_n{(x)}$                                   | (TODO)             | `std::laguerre`       | (TODO)    |
| Laguerre             | Associated Laguerre polynomial $L_n^{(\alpha)}{(x)}$             | (TODO)             | `std::assoc_laguerre` | (TODO)    |
| Legendre             | Legendre polynomial $P_n{(x)}$                                   | (TODO)             | `std::legendre`       | (TODO)    |
| Legendre             | Associated Legendre polynomial $P_n^m{(x)}$                      | (TODO)             | `std::assoc_legendre` | (TODO)    |
| Legendre             | Spherical associated Legendre polynomial                         | (TODO)             | `std::sph_legendre`   | (TODO)    |
| Elliptic integral    | Complete elliptic integral of the first kind $K(k)$              | (TODO)             | `std::comp_ellint_1`  | (TODO)    |
| Elliptic integral    | Complete elliptic integral of the second kind $E(k)$             | (TODO)             | `std::comp_ellint_2`  | (TODO)    |
| Elliptic integral    | Complete elliptic integral of the third kind $\Pi(n, k)$         | (TODO)             | `std::comp_ellint_3`  | (TODO)    |
| Elliptic integral    | Incomplete elliptic integral of the first kind $F(\phi, k)$      | (TODO)             | `std::ellint_1`       | (TODO)    |
| Elliptic integral    | Incomplete elliptic integral of the second kind $E(\phi, k)$     | (TODO)             | `std::ellint_2`       | (TODO)    |
| Elliptic integral    | Incomplete elliptic integral of the third kind $\Pi(n, \phi, k)$ | (TODO)             | `std::ellint_3`       | (TODO)    |
| Exponential integral | Exponential integral $Ei(x)$                                     | (TODO)             | `std::expint`         | (TODO)    |
| Zeta                 | Riemann zeta function $\zeta{(x)}$                               | (TODO)             | `std::riemann_zeta`   | (TODO)    |

- TODO: Research for more special functions.
- TODO: Names in Python will be researched later.
- TODO: Names of functions in FuncSketch are not decided yet.
- TODO: Some functions have several different definitions, so we need to determine the definitions to be used in FuncSketch.
- TODO: Some functions have different order of arguments in notation and implementation in C++, so we need to determine the order of arguments to be used in FuncSketch.
- Special functions are added in C++17, and some of them are not available in some compilers even in 2026. So we will use Boost.Math for these functions.
