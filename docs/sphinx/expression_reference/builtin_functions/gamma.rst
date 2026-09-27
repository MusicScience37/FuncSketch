Gamma Functions
==========================================

The gamma function is a special function extending the factorial to real numbers.

.. funcsketch:function:: gamma(x)

    Gamma function.

    :param x: The value to take the gamma function of.
    :type x: Real or Complex
    :definition: :math:`\Gamma(x) = \displaystyle\int_0^\infty t^{x-1} e^{-t} \, dt` for :math:`x > 0`,
        extended to the rest of the domain by analytic continuation.
    :domain: :math:`x \in \mathbb{R}` or :math:`x \in \mathbb{C}`, excluding :math:`0, -1, -2, \ldots`
    :range: :math:`\mathbb{R} \setminus \{0\}` for real :math:`x`,
        or :math:`\mathbb{C} \setminus \{0\}` for complex :math:`x`
    :returns: The value of :math:`\Gamma(x)`.
    :rtype: Real or Complex according to the type of ``x``.

    .. image:: plots/gamma.webp

.. funcsketch:function:: lgamma(x)

    Natural logarithm of the absolute value of the gamma function.

    :param x: The value to take the function of.
    :type x: Real
    :definition: :math:`\mathrm{lgamma}(x) = \log{|\Gamma(x)|}`
    :domain: :math:`x \in \mathbb{R}`, excluding :math:`0, -1, -2, \ldots`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\log{|\Gamma(x)|}`.
    :rtype: Real

    .. image:: plots/lgamma.webp

.. funcsketch:function:: digamma(x)

    Digamma function.

    :param x: The value to take the digamma function of.
    :type x: Real
    :definition: :math:`\psi(x) = \dfrac{d}{dx} \log{\Gamma(x)} = \dfrac{\Gamma'(x)}{\Gamma(x)}`
    :domain: :math:`x \in \mathbb{R}`, excluding :math:`0, -1, -2, \ldots`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\psi(x)`.
    :rtype: Real

    .. image:: plots/digamma.webp

.. funcsketch:function:: trigamma(x)

    Trigamma function.

    :param x: The value to take the trigamma function of.
    :type x: Real
    :definition: :math:`\psi^{(1)}(x) = \dfrac{d^2}{dx^2} \log{\Gamma(x)}`
    :domain: :math:`x \in \mathbb{R}`, excluding :math:`0, -1, -2, \ldots`
    :range: :math:`(0, \infty)`
    :returns: The value of :math:`\psi^{(1)}(x)`.
    :rtype: Real

    .. image:: plots/trigamma.webp

.. funcsketch:function:: polygamma(n, x)

    Polygamma function.

    :param n: The order of the polygamma function.
    :type n: Integer
    :param x: The value to take the polygamma function of.
    :type x: Real
    :definition: :math:`\psi^{(n)}(x) = \dfrac{d^{n+1}}{dx^{n+1}} \log{\Gamma(x)}`
    :domain: :math:`n \in \{0, 1, 2, \ldots\}`, :math:`x \in \mathbb{R}`, excluding :math:`x \in \{0, -1, -2, \ldots\}`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\psi^{(n)}(x)`.
    :rtype: Real

    .. image:: plots/polygamma.webp

.. funcsketch:function:: igamma(a, x)

    Regularized lower incomplete gamma function.

    :param a: The parameter of the gamma function.
    :type a: Real
    :param x: The upper limit of the integral.
    :type x: Real
    :definition: :math:`P(a, x) = \dfrac{1}{\Gamma(a)} \displaystyle\int_0^x t^{a-1} e^{-t} \, dt`
    :domain: :math:`a > 0` and :math:`x \ge 0`
    :range: :math:`[0, 1]`
    :returns: The value of :math:`P(a, x)`.
    :rtype: Real

    .. image:: plots/igamma.webp

.. funcsketch:function:: igammac(a, x)

    Regularized upper incomplete gamma function.

    :param a: The parameter of the gamma function.
    :type a: Real
    :param x: The lower limit of the integral.
    :type x: Real
    :definition: :math:`Q(a, x) = 1 - P(a, x) = \dfrac{1}{\Gamma(a)} \displaystyle\int_x^\infty t^{a-1} e^{-t} \, dt`
    :domain: :math:`a > 0` and :math:`x \ge 0`
    :range: :math:`[0, 1]`
    :returns: The value of :math:`Q(a, x)`.
    :rtype: Real

    .. image:: plots/igammac.webp

.. funcsketch:function:: igamma_inv(a, p)

    Inverse of the regularized lower incomplete gamma function.

    :param a: The parameter of the gamma function.
    :type a: Real
    :param p: The value of the regularized lower incomplete gamma function.
    :type p: Real
    :definition: :math:`\mathrm{igamma\_inv}(a, p) = P^{-1}(a, p)` is the value :math:`x` satisfying :math:`P(a, x) = p`.
    :domain: :math:`a > 0` and :math:`0 \le p \le 1`
    :range: :math:`[0, \infty]`
    :returns: The value of :math:`P^{-1}(a, p)`.
    :rtype: Real

    .. image:: plots/igamma_inv.webp

.. funcsketch:function:: igammac_inv(a, q)

    Inverse of the regularized upper incomplete gamma function.

    :param a: The parameter of the gamma function.
    :type a: Real
    :param q: The value of the regularized upper incomplete gamma function.
    :type q: Real
    :definition: :math:`\mathrm{igammac\_inv}(a, q) = Q^{-1}(a, q)` is the value :math:`x` satisfying :math:`Q(a, x) = q`.
    :domain: :math:`a > 0` and :math:`0 \le q \le 1`
    :range: :math:`[0, \infty]`
    :returns: The value of :math:`Q^{-1}(a, q)`.
    :rtype: Real

    .. image:: plots/igammac_inv.webp
