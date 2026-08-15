Bessel Functions
=======================

.. funcsketch:function:: bessel_j(v, x)

    (Cylindrical) Bessel function of the first kind.

    :param v: The order of the Bessel function.
    :type v: Integer or Real
    :param x: The argument of the Bessel function.
    :type x: Real or Complex
    :definition: :math:`\displaystyle J_{\nu}(x) = \left(\frac{x}{2}\right)^{\nu} \sum_{k=0}^{\infty} \frac{(-1)^k}{k! \Gamma(\nu + k + 1)} \left(\frac{x}{2}\right)^{2k}`
    :domain: :math:`\mathbb{R}` for real :math:`x` and an integer :math:`\nu`,
        :math:`[0, \infty)` for real :math:`x` and a non-integer :math:`\nu`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :returns: The value of :math:`J_{\nu}(x)`.
    :rtype: Real or Complex according to the type of ``x``.

    .. image:: plots/bessel_j0.png
    .. image:: plots/bessel_j1.png

.. funcsketch:function:: bessel_y(v, x)

    (Cylindrical) Bessel function of the second kind.

    :param v: The order of the Bessel function.
    :type v: Integer or Real
    :param x: The argument of the Bessel function.
    :type x: Real or Complex
    :definition: :math:`\displaystyle Y_{\nu}(x) = \frac{J_{\nu}(x) \cos(\nu \pi) - J_{-\nu}(x)}{\sin(\nu \pi)}`.
        The limit is taken as :math:`\nu \to n` for integer order :math:`n`.
    :domain: :math:`(0, \infty)` for real :math:`x`
        or :math:`\mathbb{C}` for complex :math:`x`
    :returns: The value of :math:`Y_{\nu}(x)`.
    :rtype: Real or Complex according to the type of ``x``.

    .. image:: plots/bessel_y0.png
    .. image:: plots/bessel_y1.png

.. funcsketch:function:: bessel_i(v, x)

    (Cylindrical) modified Bessel function of the first kind.

    :param v: The order of the Bessel function.
    :type v: Integer or Real
    :param x: The argument of the Bessel function.
    :type x: Real or Complex
    :definition: :math:`\displaystyle I_{\nu}(x) = e^{-i \nu \pi / 2} J_{\nu}(i x)`.
    :domain: :math:`\mathbb{R}` for real :math:`x` and an integer :math:`\nu`,
        :math:`[0, \infty)` for real :math:`x` and a non-integer :math:`\nu`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :returns: The value of :math:`I_{\nu}(x)`.
    :rtype: Real or Complex according to the type of ``x``.

    .. image:: plots/bessel_i0.png
    .. image:: plots/bessel_i1.png

.. funcsketch:function:: bessel_k(v, x)

    (Cylindrical) modified Bessel function of the second kind.

    :param v: The order of the Bessel function.
    :type v: Integer or Real
    :param x: The argument of the Bessel function.
    :type x: Real or Complex
    :definition: :math:`\displaystyle K_{\nu}(x) = \frac{\pi}{2} \frac{I_{-\nu}(x) - I_{\nu}(x)}{\sin(\nu \pi)}`.
        The limit is taken as :math:`\nu \to n` for integer order :math:`n`.
    :domain: :math:`(0, \infty)` for real :math:`x`
        or :math:`\mathbb{C}` for complex :math:`x`
    :returns: The value of :math:`K_{\nu}(x)`.
    :rtype: Real or Complex according to the type of ``x``.

    .. image:: plots/bessel_k0.png
    .. image:: plots/bessel_k1.png

.. funcsketch:function:: hankel1(v, x)

    (Cylindrical) Hankel function of the first kind.

    :param v: The order of the Hankel function.
    :type v: Integer or Real
    :param x: The argument of the Hankel function.
    :type x: Real or Complex
    :definition: :math:`\displaystyle H_{\nu}^{(1)}(x) = J_{\nu}(x) + i Y_{\nu}(x)`.
    :domain: :math:`(0, \infty)` for real :math:`x`
        or :math:`\mathbb{C}` for complex :math:`x`
    :returns: The value of :math:`H_{\nu}^{(1)}(x)`.
    :rtype: Real or Complex according to the type of ``x``.

    For the plot of Hankel functions, see the plots of Bessel functions
    :funcsketch:func:`bessel_j` and :funcsketch:func:`bessel_y`,
    because Hankel functions have the same shape as Bessel functions
    in real and imaginary parts.

.. funcsketch:function:: hankel2(v, x)

    (Cylindrical) Hankel function of the second kind.

    :param v: The order of the Hankel function.
    :type v: Integer or Real
    :param x: The argument of the Hankel function.
    :type x: Real or Complex
    :definition: :math:`\displaystyle H_{\nu}^{(2)}(x) = J_{\nu}(x) - i Y_{\nu}(x)`.
    :domain: :math:`(0, \infty)` for real :math:`x`
        or :math:`\mathbb{C}` for complex :math:`x`
    :returns: The value of :math:`H_{\nu}^{(2)}(x)`.
    :rtype: Real or Complex according to the type of ``x``.

    For the plot of Hankel functions, see the plots of Bessel functions
    :funcsketch:func:`bessel_j` and :funcsketch:func:`bessel_y`,
    because Hankel functions have the same shape as Bessel functions
    in real and imaginary parts.

.. funcsketch:function:: spherical_bessel_j(n, x)

    Spherical Bessel function of the first kind.

    :param n: The order of the spherical Bessel function.
    :type n: Integer
    :param x: The argument of the spherical Bessel function.
    :type x: Real or Complex
    :definition: :math:`\displaystyle j_n(x) = \sqrt{\frac{\pi}{2x}} J_{n + 1/2}(x)`.
    :domain: :math:`[0, \infty)` for real :math:`x`
        or :math:`\mathbb{C}` for complex :math:`x`
    :returns: The value of :math:`j_n(x)`.
    :rtype: Real or Complex according to the type of ``x``.

    .. image:: plots/spherical_bessel_j0.png
    .. image:: plots/spherical_bessel_j1.png

.. funcsketch:function:: spherical_bessel_y(n, x)

    Spherical Bessel function of the second kind.

    :param n: The order of the spherical Bessel function.
    :type n: Integer
    :param x: The argument of the spherical Bessel function.
    :type x: Real or Complex
    :definition: :math:`\displaystyle y_n(x) = \sqrt{\frac{\pi}{2x}} Y_{n + 1/2}(x)`.
    :domain: :math:`(0, \infty)` for real :math:`x`
        or :math:`\mathbb{C}` for complex :math:`x`
    :returns: The value of :math:`y_n(x)`.
    :rtype: Real or Complex according to the type of ``x``.

    .. image:: plots/spherical_bessel_y0.png
    .. image:: plots/spherical_bessel_y1.png

.. funcsketch:function:: spherical_hankel1(n, x)

    Spherical Hankel function of the first kind.

    :param n: The order of the spherical Hankel function.
    :type n: Integer
    :param x: The argument of the spherical Hankel function.
    :type x: Real or Complex
    :definition: :math:`\displaystyle h_n^{(1)}(x) = j_n(x) + i y_n(x)`.
    :domain: :math:`(0, \infty)` for real :math:`x`
        or :math:`\mathbb{C}` for complex :math:`x`
    :returns: The value of :math:`h_n^{(1)}(x)`.
    :rtype: Real or Complex according to the type of ``x``.

    For the plot of spherical Hankel functions, see the plots of spherical Bessel functions
    :funcsketch:func:`spherical_bessel_j` and :funcsketch:func:`spherical_bessel_y`,
    because spherical Hankel functions have the same shape as spherical Bessel functions
    in real and imaginary parts.

.. funcsketch:function:: spherical_hankel2(n, x)

    Spherical Hankel function of the second kind.

    :param n: The order of the spherical Hankel function.
    :type n: Integer
    :param x: The argument of the spherical Hankel function.
    :type x: Real or Complex
    :definition: :math:`\displaystyle h_n^{(2)}(x) = j_n(x) - i y_n(x)`.
    :domain: :math:`(0, \infty)` for real :math:`x`
        or :math:`\mathbb{C}` for complex :math:`x`
    :returns: The value of :math:`h_n^{(2)}(x)`.
    :rtype: Real or Complex according to the type of ``x``.

    For the plot of spherical Hankel functions, see the plots of spherical Bessel functions
    :funcsketch:func:`spherical_bessel_j` and :funcsketch:func:`spherical_bessel_y`,
    because spherical Hankel functions have the same shape as spherical Bessel functions
    in real and imaginary parts.

.. funcsketch:function:: kelvin_ber(v, x)

    Kelvin function ``ber``.

    :param v: The order of the Kelvin function.
    :type v: Real
    :param x: The argument of the Kelvin function.
    :type x: Real
    :definition: :math:`\displaystyle \text{ber}_{\nu}(x) = \operatorname{Re}\left[J_{\nu}\left(x e^{3 \pi i / 4}\right)\right]`.
    :domain: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\text{ber}_{\nu}(x)`.
    :rtype: Real

    .. image:: plots/kelvin_ber.png

.. funcsketch:function:: kelvin_bei(v, x)

    Kelvin function ``bei``.

    :param v: The order of the Kelvin function.
    :type v: Real
    :param x: The argument of the Kelvin function.
    :type x: Real
    :definition: :math:`\displaystyle \text{bei}_{\nu}(x) = \operatorname{Im}\left[J_{\nu}\left(x e^{3 \pi i / 4}\right)\right]`.
    :domain: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\text{bei}_{\nu}(x)`.
    :rtype: Real

    .. image:: plots/kelvin_bei.png

.. funcsketch:function:: kelvin_ker(v, x)

    Kelvin function ``ker``.

    :param v: The order of the Kelvin function.
    :type v: Real
    :param x: The argument of the Kelvin function.
    :type x: Real
    :definition: :math:`\displaystyle \text{ker}_{\nu}(x) = \operatorname{Re}\left[e^{-\nu \pi i / 2} K_{\nu}\left(x e^{\pi i / 4}\right)\right]`.
    :domain: :math:`(0, \infty)`
    :returns: The value of :math:`\text{ker}_{\nu}(x)`.
    :rtype: Real

    .. image:: plots/kelvin_ker.png

.. funcsketch:function:: kelvin_kei(v, x)

    Kelvin function ``kei``.

    :param v: The order of the Kelvin function.
    :type v: Real
    :param x: The argument of the Kelvin function.
    :type x: Real
    :definition: :math:`\displaystyle \text{kei}_{\nu}(x) = \operatorname{Im}\left[e^{-\nu \pi i / 2} K_{\nu}\left(x e^{\pi i / 4}\right)\right]`.
    :domain: :math:`(0, \infty)`
    :returns: The value of :math:`\text{kei}_{\nu}(x)`.
    :rtype: Real

    .. image:: plots/kelvin_kei.png
