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
