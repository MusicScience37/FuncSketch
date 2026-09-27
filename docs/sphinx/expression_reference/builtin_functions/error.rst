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

    .. image:: plots/erf.webp

.. funcsketch:function:: erfc(x)

    Complementary error function.

    :param x: The value to take the complementary error function of.
    :type x: Real
    :definition: :math:`\mathrm{erfc}(x) = 1 - \mathrm{erf}(x)`
    :domain: :math:`(-\infty, \infty)`
    :range: :math:`(0, 2)`
    :returns: The value of :math:`\mathrm{erfc}(x)`.
    :rtype: Real

    .. image:: plots/erfc.webp

.. funcsketch:function:: erf_inv(x)

    Inverse error function.

    :param x: The value to take the inverse error function of.
    :type x: Real
    :definition: :math:`\mathrm{erf\_inv}(x) = \mathrm{erf}^{-1}(x)` is the inverse function of :math:`\mathrm{erf}(x)`.
    :domain: :math:`(-1, 1)`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\mathrm{erf}^{-1}(x)`.
    :rtype: Real

    .. image:: plots/erf_inv.webp

.. funcsketch:function:: erfc_inv(x)

    Inverse complementary error function.

    :param x: The value to take the inverse complementary error function of.
    :type x: Real
    :definition: :math:`\mathrm{erfc\_inv}(x) = \mathrm{erfc}^{-1}(x)` is the inverse function of :math:`\mathrm{erfc}(x)`.
    :domain: :math:`(0, 2)`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\mathrm{erfc}^{-1}(x)`.
    :rtype: Real

    .. image:: plots/erfc_inv.webp
