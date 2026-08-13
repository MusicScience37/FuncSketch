# Mathematical Functions to be Implemented

This page lists mathematical functions to be implemented in FuncSketch.
Functions which has been implemented will be removed from this list.

## Basic Functions

All basic functions in `<cmath>` header in C++11 have been implemented.

## Other Special Functions

Candidate of implementation of special functions are as follows:

| Type                 | Function                                                            | Name in FuncSketch | In C++                            | In Python |
| :------------------- | :------------------------------------------------------------------ | :----------------- | :-------------------------------- | :-------- |
| Beta                 | Beta function $B{(x, y)}$                                           | (TODO)             | `std::beta`                       | (TODO)    |
| Beta                 | Incomplete beta function $B{(x; a, b)}$                             | (TODO)             | `boost::math::ibeta`              | (TODO)    |
| Airy                 | Airy function of the first kind $\mathrm{Ai}{(x)}$                  | (TODO)             | `boost::math::airy_ai`            | (TODO)    |
| Airy                 | Airy function of the second kind $\mathrm{Bi}{(x)}$                 | (TODO)             | `boost::math::airy_bi`            | (TODO)    |
| Bessel               | Cylindrical Bessel function $J_{\nu}{(x)}$                          | (TODO)             | `std::cyl_bessel_j`               | (TODO)    |
| Bessel               | Cylindrical Neumann function $Y_{\nu}{(x)}$                         | (TODO)             | `std::cyl_neumann`                | (TODO)    |
| Bessel               | Regular modified cylindrical Bessel function $I_{\nu}{(x)}$         | (TODO)             | `std::cyl_bessel_i`               | (TODO)    |
| Bessel               | Irregular modified cylindrical Bessel function $K_{\nu}{(x)}$       | (TODO)             | `std::cyl_bessel_k`               | (TODO)    |
| Bessel               | Spherical Bessel function $j_n{(x)}$                                | (TODO)             | `std::sph_bessel`                 | (TODO)    |
| Bessel               | Spherical Neumann function $y_n{(x)}$                               | (TODO)             | `std::sph_neumann`                | (TODO)    |
| Bessel               | Cylindrical Hankel function of the first kind $H_{\nu}^{(1)}{(x)}$  | (TODO)             | `boost::math::cyl_hankel_1`       | (TODO)    |
| Bessel               | Cylindrical Hankel function of the second kind $H_{\nu}^{(2)}{(x)}$ | (TODO)             | `boost::math::cyl_hankel_2`       | (TODO)    |
| Bessel               | Spherical Hankel function of the first kind $h_n^{(1)}{(x)}$        | (TODO)             | `boost::math::sph_hankel_1`       | (TODO)    |
| Bessel               | Spherical Hankel function of the second kind $h_n^{(2)}{(x)}$       | (TODO)             | `boost::math::sph_hankel_2`       | (TODO)    |
| Kelvin               | Kelvin function $\mathrm{ber}_{\nu}{(x)}$                           | (TODO)             | (TODO)                            | (TODO)    |
| Kelvin               | Kelvin function $\mathrm{bei}_{\nu}{(x)}$                           | (TODO)             | (TODO)                            | (TODO)    |
| Kelvin               | Kelvin function $\mathrm{ker}_{\nu}{(x)}$                           | (TODO)             | (TODO)                            | (TODO)    |
| Kelvin               | Kelvin function $\mathrm{kei}_{\nu}{(x)}$                           | (TODO)             | (TODO)                            | (TODO)    |
| Gamma                | Digamma function $\psi{(x)}$                                        | (TODO)             | `boost::math::digamma`            | (TODO)    |
| Gamma                | Polygamma function $\psi^{(n)}{(x)}$                                | (TODO)             | `boost::math::polygamma`          | (TODO)    |
| Gamma                | Upper incomplete gamma function $\Gamma{(a, x)}$                    | (TODO)             | `boost::math::tgamma`             | (TODO)    |
| Gamma                | Lower incomplete gamma function $\gamma{(a, x)}$                    | (TODO)             | `boost::math::tgamma_lower`       | (TODO)    |
| Error function       | Inverse error function $\mathrm{erf}^{-1}{(x)}$                     | (TODO)             | `boost::math::erf_inv`            | (TODO)    |
| Error function       | Inverse complementary error function $\mathrm{erfc}^{-1}{(x)}$      | (TODO)             | `boost::math::erfc_inv`           | (TODO)    |
| Hermite              | Hermite polynomial $H_n{(x)}$ (physicist's)                         | (TODO)             | `std::hermite`                    | (TODO)    |
| Chebyshev            | Chebyshev polynomial of the first kind $T_n{(x)}$                   | (TODO)             | `boost::math::chebyshev_t`        | (TODO)    |
| Chebyshev            | Chebyshev polynomial of the second kind $U_n{(x)}$                  | (TODO)             | `boost::math::chebyshev_u`        | (TODO)    |
| Gegenbauer           | Gegenbauer polynomial $C_n^{(\lambda)}{(x)}$                        | (TODO)             | `boost::math::gegenbauer`         | (TODO)    |
| Laguerre             | Laguerre polynomial $L_n{(x)}$                                      | (TODO)             | `std::laguerre`                   | (TODO)    |
| Laguerre             | Associated Laguerre polynomial $L_n^{(\alpha)}{(x)}$                | (TODO)             | `std::assoc_laguerre`             | (TODO)    |
| Legendre             | Legendre polynomial $P_n{(x)}$                                      | (TODO)             | `std::legendre`                   | (TODO)    |
| Legendre             | Associated Legendre polynomial $P_n^m{(x)}$                         | (TODO)             | `std::assoc_legendre`             | (TODO)    |
| Legendre             | Spherical associated Legendre polynomial                            | (TODO)             | `std::sph_legendre`               | (TODO)    |
| Jacobi polynomial    | Jacobi polynomial $P_n^{(\alpha, \beta)}{(x)}$                      | (TODO)             | `boost::math::jacobi`             | (TODO)    |
| Elliptic integral    | Complete elliptic integral of the first kind $K(k)$                 | (TODO)             | `std::comp_ellint_1`              | (TODO)    |
| Elliptic integral    | Complete elliptic integral of the second kind $E(k)$                | (TODO)             | `std::comp_ellint_2`              | (TODO)    |
| Elliptic integral    | Complete elliptic integral of the third kind $\Pi(n, k)$            | (TODO)             | `std::comp_ellint_3`              | (TODO)    |
| Elliptic integral    | Incomplete elliptic integral of the first kind $F(\phi, k)$         | (TODO)             | `std::ellint_1`                   | (TODO)    |
| Elliptic integral    | Incomplete elliptic integral of the second kind $E(\phi, k)$        | (TODO)             | `std::ellint_2`                   | (TODO)    |
| Elliptic integral    | Incomplete elliptic integral of the third kind $\Pi(n, \phi, k)$    | (TODO)             | `std::ellint_3`                   | (TODO)    |
| Jacobi elliptic      | Jacobi elliptic function $\mathrm{sn}{(u, k)}$                      | (TODO)             | `boost::math::jacobi_sn`          | (TODO)    |
| Jacobi elliptic      | Jacobi elliptic function $\mathrm{cn}{(u, k)}$                      | (TODO)             | `boost::math::jacobi_cn`          | (TODO)    |
| Jacobi elliptic      | Jacobi elliptic function $\mathrm{dn}{(u, k)}$                      | (TODO)             | `boost::math::jacobi_dn`          | (TODO)    |
| Exponential integral | Exponential integral $Ei(x)$                                        | (TODO)             | `std::expint`                     | (TODO)    |
| Other integrals      | Dawson integral $F{(x)}$                                            | (TODO)             | (TODO)                            | (TODO)    |
| Other integrals      | Sine integral $\mathrm{Si}{(x)}$                                    | (TODO)             | (TODO)                            | (TODO)    |
| Other integrals      | Cosine integral $\mathrm{Ci}{(x)}$                                  | (TODO)             | (TODO)                            | (TODO)    |
| Hypergeometric       | Confluent hypergeometric function (Kummer's M) $M{(a, b, x)}$       | (TODO)             | `boost::math::hypergeometric_1F1` | (TODO)    |
| Hypergeometric       | Confluent hypergeometric function (Kummer's U) $U{(a, b, x)}$       | (TODO)             | (TODO)                            | (TODO)    |
| Hypergeometric       | Gauss hypergeometric function ${}_2F_1{(a, b; c; x)}$               | (TODO)             | (TODO)                            | (TODO)    |
| Zeta                 | Riemann zeta function $\zeta{(x)}$                                  | (TODO)             | `std::riemann_zeta`               | (TODO)    |
| Zeta                 | Hurwitz zeta function $\zeta{(x, q)}$                               | (TODO)             | (TODO)                            | (TODO)    |
| Lambert W            | Lambert W function (principal branch) $W_0{(x)}$                    | (TODO)             | `boost::math::lambert_w0`         | (TODO)    |
| Lambert W            | Lambert W function (secondary branch) $W_{-1}{(x)}$                 | (TODO)             | `boost::math::lambert_wm1`        | (TODO)    |
| Owen                 | Owen's T function $T{(h, a)}$                                       | (TODO)             | `boost::math::owens_t`            | (TODO)    |

- TODO: Names in Python will be researched later.
- TODO: Names of functions in FuncSketch are not decided yet.
- TODO: Some functions have several different definitions, so we need to determine the definitions to be used in FuncSketch.
- TODO: Some functions have different order of arguments in notation and implementation in C++, so we need to determine the order of arguments to be used in FuncSketch.
- Special functions are added in C++17, and some of them are not available in some compilers even in 2026. So we will use Boost.Math for these functions.
- Boost.Math does not provide a dedicated function for the Gauss hypergeometric function ${}_2F_1$. But `boost::math::hypergeometric_pFq` (generalized hypergeometric function) may be able to be used to compute it instead.
- Boost.Math does not currently provide Kelvin functions, the Dawson integral, sine/cosine integrals, the Hurwitz zeta function, or Kummer's U function.
  - Kelvin function can be computed using Bessel functions.
