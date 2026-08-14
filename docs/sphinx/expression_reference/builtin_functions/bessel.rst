Bessel Functions
=======================

.. funcsketch:function:: bessel_j(v, x)

    Cylindrical Bessel function of the first kind.

    :param v: The order of the Bessel function.
    :type v: Integer or Real
    :param x: The argument of the Bessel function.
    :type x: Real or Complex
    :definition: :math:`\displaystyle J_{\nu}(x) = \left(\frac{x}{2}\right)^{\nu} \sum_{k=0}^{\infty} \frac{(-1)^k}{k! \Gamma(\nu + k + 1)} \left(\frac{x}{2}\right)^{2k}`
    :domain: :math:`\mathbb{R}` for real :math:`x` and an integer :math:`\nu`,
        :math:`[0, \infty)` for real :math:`x` and a non-integer :math:`\nu`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :range: (To be written)
    :returns: The value of :math:`J_{\nu}(x)`.
    :rtype: Real or Complex according to the type of ``x``.

    .. image:: plots/bessel_j0.png
    .. image:: plots/bessel_j1.png

.. funcsketch:function:: bessel_y(v, x)

    Cylindrical Bessel function of the second kind.

    :param v: The order of the Bessel function.
    :type v: Integer or Real
    :param x: The argument of the Bessel function.
    :type x: Real or Complex
    :definition: :math:`\displaystyle Y_{\nu}(x) = \frac{J_{\nu}(x) \cos(\nu \pi) - J_{-\nu}(x)}{\sin(\nu \pi)}`.
        The limit is taken as :math:`\nu \to n` for integer order :math:`n`.
    :domain: :math:`(0, \infty)` for real :math:`x`
        or :math:`\mathbb{C}` for complex :math:`x`
    :range: (To be written)
    :returns: The value of :math:`Y_{\nu}(x)`.
    :rtype: Real or Complex according to the type of ``x``.

    .. image:: plots/bessel_y0.png
    .. image:: plots/bessel_y1.png
