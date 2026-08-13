Exponential and Logarithmic Functions
==========================================

.. funcsketch:function:: exp(x)

    Exponential function.

    :param x: The exponent to which :math:`e` is raised.
    :type x: Real or Complex
    :definition: :math:`\exp(x) = e^x`
    :domain: :math:`(-\infty, \infty)` for real :math:`x`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :range: :math:`(0, \infty)` for real :math:`x`,
        or :math:`\mathbb{C} \setminus \{0\}` for complex :math:`x`
    :returns: The value of :math:`e^x`.
    :rtype: Real or Complex according to the type of ``x``.

.. funcsketch:function:: exp2(x)

    Base-2 exponential function.

    :param x: The exponent to which :math:`2` is raised.
    :type x: Real
    :definition: :math:`\mathrm{exp2}(x) = 2^x`
    :domain: :math:`(-\infty, \infty)`
    :range: :math:`(0, \infty)`
    :returns: The value of :math:`2^x`.
    :rtype: Real

.. funcsketch:function:: expm1(x)

    Exponential-minus-one function.

    :param x: The exponent to which :math:`e` is raised.
    :type x: Real
    :definition: :math:`\mathrm{expm1}(x) = e^x - 1`
    :domain: :math:`(-\infty, \infty)`
    :range: :math:`(-1, \infty)`
    :returns: The value of :math:`e^x - 1`.
    :rtype: Real

.. funcsketch:function:: log(x)

    Natural logarithm function.

    :param x: The value to take the natural logarithm of.
    :type x: Real or Complex
    :definition: :math:`\log(x) = \log_e(x)`.
        For complex :math:`x`, the principal branch is used,
        with a branch cut along :math:`(-\infty, 0]` on the real axis.
    :domain: :math:`(0, \infty)` for real :math:`x`,
        or :math:`\mathbb{C} \setminus \{0\}` for complex :math:`x`
    :range: :math:`(-\infty, \infty)` for real :math:`x`,
        or :math:`\{w \in \mathbb{C} : -\pi < \operatorname{Im}(w) \leq \pi\}` for complex :math:`x`
    :returns: The value of :math:`\log(x)`.
    :rtype: Real or Complex according to the type of ``x``.

.. funcsketch:function:: log1p(x)

    Natural logarithm of one plus the argument.

    :param x: The value to add :math:`1` to before taking the natural logarithm.
    :type x: Real
    :definition: :math:`\mathrm{log1p}(x) = \log(1 + x)`
    :domain: :math:`(-1, \infty)`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\log(1 + x)`.
    :rtype: Real

.. funcsketch:function:: log10(x)

    Base-10 logarithm function.

    :param x: The value to take the base-10 logarithm of.
    :type x: Real or Complex
    :definition: :math:`\mathrm{log10}(x) = \log_{10}(x)`.
        For complex :math:`x`, the principal branch is used,
        with a branch cut along :math:`(-\infty, 0]` on the real axis.
    :domain: :math:`(0, \infty)` for real :math:`x`,
        or :math:`\mathbb{C} \setminus \{0\}` for complex :math:`x`
    :range: :math:`(-\infty, \infty)` for real :math:`x`,
        or :math:`\left\{w \in \mathbb{C} : -\dfrac{\pi}{\log 10} < \operatorname{Im}(w) \leq \dfrac{\pi}{\log 10}\right\}` for complex :math:`x`
    :returns: The value of :math:`\log_{10}(x)`.
    :rtype: Real or Complex according to the type of ``x``.

.. funcsketch:function:: log2(x)

    Base-2 logarithm function.

    :param x: The value to take the base-2 logarithm of.
    :type x: Real
    :definition: :math:`\mathrm{log2}(x) = \log_{2}(x)`
    :domain: :math:`(0, \infty)`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\log_{2}(x)`.
    :rtype: Real
