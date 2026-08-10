Error Functions
==========================================

The error function is a special function related to the normal distribution.

.. funcsketch:function:: erf(x)

    Error function.

    :param x: The value to take the error function of.
    :type x: Real
    :definition: :math:`\mathrm{erf}(x) = \dfrac{2}{\sqrt{\pi}} \displaystyle\int_0^x e^{-t^2} \, dt`
    :domain: :math:`(-\infty, \infty)`
    :range: :math:`(-1, 1)`
    :returns: The value of :math:`\mathrm{erf}(x)`.
    :rtype: Real
