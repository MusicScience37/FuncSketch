Hyperbolic Functions
==========================================

.. funcsketch:function:: sinh(x)

    Hyperbolic sine function.

    :param x: The value to take the hyperbolic sine of.
    :type x: Real
    :definition: :math:`\sinh(x) = \dfrac{e^x - e^{-x}}{2}`
    :domain: :math:`(-\infty, \infty)`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\sinh(x)`.
    :rtype: Real

.. funcsketch:function:: cosh(x)

    Hyperbolic cosine function.

    :param x: The value to take the hyperbolic cosine of.
    :type x: Real
    :definition: :math:`\cosh(x) = \dfrac{e^x + e^{-x}}{2}`
    :domain: :math:`(-\infty, \infty)`
    :range: :math:`[1, \infty)`
    :returns: The value of :math:`\cosh(x)`.
    :rtype: Real

.. funcsketch:function:: tanh(x)

    Hyperbolic tangent function.

    :param x: The value to take the hyperbolic tangent of.
    :type x: Real
    :definition: :math:`\tanh(x) = \dfrac{\sinh(x)}{\cosh(x)}`
    :domain: :math:`(-\infty, \infty)`
    :range: :math:`(-1, 1)`
    :returns: The value of :math:`\tanh(x)`.
    :rtype: Real

.. funcsketch:function:: asinh(x)

    Hyperbolic arcsine function.

    :param x: The value to take the hyperbolic arcsine of.
    :type x: Real
    :definition: :math:`\mathrm{asinh}(x)`, the inverse function of :math:`\sinh(x)`.
    :domain: :math:`(-\infty, \infty)`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\mathrm{asinh}(x)`.
    :rtype: Real

.. funcsketch:function:: acosh(x)

    Hyperbolic arccosine function.

    :param x: The value to take the hyperbolic arccosine of.
    :type x: Real
    :definition: :math:`\mathrm{acosh}(x)`, the inverse function of :math:`\cosh(x)` restricted to :math:`x \geq 0`.
    :domain: :math:`[1, \infty)`
    :range: :math:`[0, \infty)`
    :returns: The value of :math:`\mathrm{acosh}(x)`.
    :rtype: Real

.. funcsketch:function:: atanh(x)

    Hyperbolic arctangent function.

    :param x: The value to take the hyperbolic arctangent of.
    :type x: Real
    :definition: :math:`\mathrm{atanh}(x)`, the inverse function of :math:`\tanh(x)`.
    :domain: :math:`(-1, 1)`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\mathrm{atanh}(x)`.
    :rtype: Real
