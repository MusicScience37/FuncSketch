Beta Functions
==========================================

The beta function is a special function closely related to the gamma function.

.. funcsketch:function:: beta(x, y)

    Beta function.

    :param x: The first argument of the beta function.
    :type x: Real
    :param y: The second argument of the beta function.
    :type y: Real
    :definition: :math:`B(x, y) = \displaystyle\int_0^1 t^{x-1} (1 - t)^{y-1} \, dt = \frac{\Gamma(x) \Gamma(y)}{\Gamma(x + y)}`
    :domain: :math:`x > 0` and :math:`y > 0`
    :range: :math:`(0, \infty)`
    :returns: The value of :math:`B(x, y)`.
    :rtype: Real

    .. image:: plots/beta.webp

.. funcsketch:function:: lbeta(x, y)

    Natural logarithm of the absolute value of the beta function.

    :param x: The first argument of the beta function.
    :type x: Real
    :param y: The second argument of the beta function.
    :type y: Real
    :definition: :math:`\mathrm{lbeta}(x, y) = \log{|B(x, y)|}`,
        where :math:`B(x, y) = \dfrac{\Gamma(x) \Gamma(y)}{\Gamma(x + y)}` is extended to negative arguments using the gamma function.
    :domain: :math:`x, y \in \mathbb{R}`, excluding :math:`x, y, x + y \in \{0, -1, -2, \ldots\}`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\log{|B(x, y)|}`.
    :rtype: Real

    .. image:: plots/lbeta.webp
