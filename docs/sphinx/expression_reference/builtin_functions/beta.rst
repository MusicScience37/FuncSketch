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

.. funcsketch:function:: ibeta(a, b, x)

    Regularized incomplete beta function.

    :param a: The first parameter of the beta function.
    :type a: Real
    :param b: The second parameter of the beta function.
    :type b: Real
    :param x: The upper limit of the integral.
    :type x: Real
    :definition: :math:`I_x(a, b) = \dfrac{1}{B(a, b)} \displaystyle\int_0^x t^{a-1} (1 - t)^{b-1} \, dt`
    :domain: :math:`a > 0`, :math:`b > 0`, and :math:`0 \le x \le 1`
    :range: :math:`[0, 1]`
    :returns: The value of :math:`I_x(a, b)`.
    :rtype: Real

    .. image:: plots/ibeta.webp

.. funcsketch:function:: ibetac(a, b, x)

    Complement of the regularized incomplete beta function.

    :param a: The first parameter of the beta function.
    :type a: Real
    :param b: The second parameter of the beta function.
    :type b: Real
    :param x: The lower limit of the integral.
    :type x: Real
    :definition: :math:`\mathrm{ibetac}(a, b, x) = 1 - I_x(a, b) = \dfrac{1}{B(a, b)} \displaystyle\int_x^1 t^{a-1} (1 - t)^{b-1} \, dt`
    :domain: :math:`a > 0`, :math:`b > 0`, and :math:`0 \le x \le 1`
    :range: :math:`[0, 1]`
    :returns: The value of :math:`1 - I_x(a, b)`.
    :rtype: Real

    .. image:: plots/ibetac.webp

.. funcsketch:function:: ibeta_inv(a, b, p)

    Inverse of the regularized incomplete beta function.

    :param a: The first parameter of the beta function.
    :type a: Real
    :param b: The second parameter of the beta function.
    :type b: Real
    :param p: The value of the regularized incomplete beta function.
    :type p: Real
    :definition: :math:`\mathrm{ibeta\_inv}(a, b, p) = I^{-1}_p(a, b)` is the value :math:`x` satisfying :math:`I_x(a, b) = p`.
    :domain: :math:`a > 0`, :math:`b > 0`, and :math:`0 \le p \le 1`
    :range: :math:`[0, 1]`
    :returns: The value of :math:`I^{-1}_p(a, b)`.
    :rtype: Real

    .. image:: plots/ibeta_inv.webp
