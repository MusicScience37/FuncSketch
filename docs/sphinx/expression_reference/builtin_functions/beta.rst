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
