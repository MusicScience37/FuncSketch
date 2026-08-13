Hyperbolic Functions
==========================================

.. funcsketch:function:: sinh(x)

    Hyperbolic sine function.

    :param x: The value to take the hyperbolic sine of.
    :type x: Real or Complex
    :definition: :math:`\sinh(x) = \dfrac{e^x - e^{-x}}{2}`
    :domain: :math:`(-\infty, \infty)` for real :math:`x`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :range: :math:`(-\infty, \infty)` for real :math:`x`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :returns: The value of :math:`\sinh(x)`.
    :rtype: Real or Complex according to the type of ``x``.

.. funcsketch:function:: cosh(x)

    Hyperbolic cosine function.

    :param x: The value to take the hyperbolic cosine of.
    :type x: Real or Complex
    :definition: :math:`\cosh(x) = \dfrac{e^x + e^{-x}}{2}`
    :domain: :math:`(-\infty, \infty)` for real :math:`x`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :range: :math:`[1, \infty)` for real :math:`x`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :returns: The value of :math:`\cosh(x)`.
    :rtype: Real or Complex according to the type of ``x``.

.. funcsketch:function:: tanh(x)

    Hyperbolic tangent function.

    :param x: The value to take the hyperbolic tangent of.
    :type x: Real or Complex
    :definition: :math:`\tanh(x) = \dfrac{\sinh(x)}{\cosh(x)}`
    :domain: :math:`(-\infty, \infty)` for real :math:`x`,
        or :math:`\mathbb{C} \setminus \left\{i \left(\dfrac{\pi}{2} + n\pi\right) : n \in \mathbb{Z}\right\}` for complex :math:`x`
    :range: :math:`(-1, 1)` for real :math:`x`,
        or :math:`\mathbb{C} \setminus \{-1, 1\}` for complex :math:`x`
    :returns: The value of :math:`\tanh(x)`.
    :rtype: Real or Complex according to the type of ``x``.

.. funcsketch:function:: asinh(x)

    Hyperbolic arcsine function.

    :param x: The value to take the hyperbolic arcsine of.
    :type x: Real or Complex
    :definition: :math:`\mathrm{asinh}(x)`, the inverse function of :math:`\sinh(x)`.
        For complex :math:`x`, the principal branch is used,
        with branch cuts along :math:`(-i\infty, -i]` and :math:`[i, i\infty)` on the imaginary axis.
    :domain: :math:`(-\infty, \infty)` for real :math:`x`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :range: :math:`(-\infty, \infty)` for real :math:`x`,
        or :math:`\left\{w \in \mathbb{C} : -\dfrac{\pi}{2} \leq \operatorname{Im}(w) \leq \dfrac{\pi}{2}\right\}` for complex :math:`x`
    :returns: The value of :math:`\mathrm{asinh}(x)`.
    :rtype: Real or Complex according to the type of ``x``.

.. funcsketch:function:: acosh(x)

    Hyperbolic arccosine function.

    :param x: The value to take the hyperbolic arccosine of.
    :type x: Real or Complex
    :definition: :math:`\mathrm{acosh}(x)`, the inverse function of :math:`\cosh(x)` restricted to :math:`x \geq 0`.
        For complex :math:`x`, the principal branch is used,
        with a branch cut along :math:`(-\infty, 1)` on the real axis.
    :domain: :math:`[1, \infty)` for real :math:`x`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :range: :math:`[0, \infty)` for real :math:`x`,
        or :math:`\{w \in \mathbb{C} : \operatorname{Re}(w) \geq 0, -\pi \leq \operatorname{Im}(w) \leq \pi\}` for complex :math:`x`
    :returns: The value of :math:`\mathrm{acosh}(x)`.
    :rtype: Real or Complex according to the type of ``x``.

.. funcsketch:function:: atanh(x)

    Hyperbolic arctangent function.

    :param x: The value to take the hyperbolic arctangent of.
    :type x: Real or Complex
    :definition: :math:`\mathrm{atanh}(x)`, the inverse function of :math:`\tanh(x)`.
        For complex :math:`x`, the principal branch is used,
        with branch cuts along :math:`(-\infty, -1]` and :math:`[1, \infty)` on the real axis.
    :domain: :math:`(-1, 1)` for real :math:`x`,
        or :math:`\mathbb{C} \setminus \{-1, 1\}` for complex :math:`x`
    :range: :math:`(-\infty, \infty)` for real :math:`x`,
        or :math:`\left\{w \in \mathbb{C} : -\dfrac{\pi}{2} \leq \operatorname{Im}(w) \leq \dfrac{\pi}{2}\right\}` for complex :math:`x`
    :returns: The value of :math:`\mathrm{atanh}(x)`.
    :rtype: Real or Complex according to the type of ``x``.
