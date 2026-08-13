Functions for Complex Numbers
=================================

.. seealso::
    :funcsketch:func:`abs` is written in :ref:`builtin_functions_misc_float_operations`.

.. funcsketch:function:: real(x)

    Real part function.

    :param x: The value of which the real part is taken.
    :type x: Complex
    :definition: :math:`\mathrm{real}(x) = \operatorname{Re}(x)`.
        For :math:`x = a + bi` with real :math:`a, b`, :math:`\mathrm{real}(x) = a`.
    :domain: :math:`\mathbb{C}`
    :range: :math:`(-\infty, \infty)`
    :returns: The real part of :math:`x`.
    :rtype: Real

.. funcsketch:function:: imag(x)

    Imaginary part function.

    :param x: The value of which the imaginary part is taken.
    :type x: Complex
    :definition: :math:`\mathrm{imag}(x) = \operatorname{Im}(x)`.
        For :math:`x = a + bi` with real :math:`a, b`, :math:`\mathrm{imag}(x) = b`.
    :domain: :math:`\mathbb{C}`
    :range: :math:`(-\infty, \infty)`
    :returns: The imaginary part of :math:`x`.
    :rtype: Real

.. funcsketch:function:: arg(x)

    Argument (phase angle) function.

    :param x: The value of which the argument is taken.
    :type x: Complex
    :definition: :math:`\mathrm{arg}(x)`, the angle :math:`\theta \in (-\pi, \pi]` in radians
        such that :math:`x = |x| (\cos\theta + i \sin\theta)`,
        computed as :math:`\mathrm{atan2}(\operatorname{Im}(x), \operatorname{Re}(x))`.
        :math:`\mathrm{arg}(0) = 0` by convention.
    :domain: :math:`\mathbb{C}`
    :range: :math:`(-\pi, \pi]`
    :returns: The argument of :math:`x` in radians.
    :rtype: Real

.. funcsketch:function:: conj(x)

    Complex conjugate function.

    :param x: The value of which the complex conjugate is taken.
    :type x: Complex
    :definition: :math:`\mathrm{conj}(x) = \overline{x}`.
        For :math:`x = a + bi` with real :math:`a, b`, :math:`\mathrm{conj}(x) = a - bi`.
    :domain: :math:`\mathbb{C}`
    :range: :math:`\mathbb{C}`
    :returns: The complex conjugate of :math:`x`.
    :rtype: Complex
