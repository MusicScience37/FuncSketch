Trigonometric Functions
==========================================

.. funcsketch:function:: sin(x)

    Sine function.

    :param x: The angle in radians.
    :type x: Real or Complex
    :definition: :math:`\sin(x)`
    :domain: :math:`(-\infty, \infty)` for real :math:`x`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :range: :math:`[-1, 1]` for real :math:`x`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :returns: The value of :math:`\sin(x)`.
    :rtype: Real or Complex according to the type of ``x``.

.. funcsketch:function:: cos(x)

    Cosine function.

    :param x: The angle in radians.
    :type x: Real or Complex
    :definition: :math:`\cos(x)`
    :domain: :math:`(-\infty, \infty)` for real :math:`x`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :range: :math:`[-1, 1]` for real :math:`x`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :returns: The value of :math:`\cos(x)`.
    :rtype: Real or Complex according to the type of ``x``.

.. funcsketch:function:: tan(x)

    Tangent function.

    :param x: The angle in radians.
    :type x: Real or Complex
    :definition: :math:`\tan(x) = \dfrac{\sin(x)}{\cos(x)}`
    :domain: :math:`x \neq \dfrac{\pi}{2} + n\pi \ (n \in \mathbb{Z})`,
        for real or complex :math:`x`
    :range: :math:`(-\infty, \infty)` for real :math:`x`,
        or :math:`\mathbb{C} \setminus \{-i, i\}` for complex :math:`x`
    :returns: The value of :math:`\tan(x)`.
    :rtype: Real or Complex according to the type of ``x``.

.. funcsketch:function:: asin(x)

    Arcsine function.

    :param x: The value to take the arcsine of.
    :type x: Real or Complex
    :definition: :math:`\arcsin(x)`, the inverse function of :math:`\sin(x)`.
        For complex :math:`x`, the principal branch is used,
        with branch cuts along :math:`(-\infty, -1]` and :math:`[1, \infty)` on the real axis.
    :domain: :math:`[-1, 1]` for real :math:`x`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :range: :math:`\left[-\dfrac{\pi}{2}, \dfrac{\pi}{2}\right]` for real :math:`x`,
        or :math:`\left\{w \in \mathbb{C} : -\dfrac{\pi}{2} \leq \operatorname{Re}(w) \leq \dfrac{\pi}{2}\right\}` for complex :math:`x`
    :returns: The value of :math:`\arcsin(x)` in radians.
    :rtype: Real or Complex according to the type of ``x``.

.. funcsketch:function:: acos(x)

    Arccosine function.

    :param x: The value to take the arccosine of.
    :type x: Real or Complex
    :definition: :math:`\arccos(x)`, the inverse function of :math:`\cos(x)`.
        For complex :math:`x`, the principal branch is used,
        with branch cuts along :math:`(-\infty, -1]` and :math:`[1, \infty)` on the real axis.
    :domain: :math:`[-1, 1]` for real :math:`x`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :range: :math:`[0, \pi]` for real :math:`x`,
        or :math:`\{w \in \mathbb{C} : 0 \leq \operatorname{Re}(w) \leq \pi\}` for complex :math:`x`
    :returns: The value of :math:`\arccos(x)` in radians.
    :rtype: Real or Complex according to the type of ``x``.

.. funcsketch:function:: atan(x)

    Arctangent function.

    :param x: The value to take the arctangent of.
    :type x: Real or Complex
    :definition: :math:`\arctan(x)`, the inverse function of :math:`\tan(x)`.
        For complex :math:`x`, the principal branch is used,
        with branch cuts along :math:`(-i\infty, -i]` and :math:`[i, i\infty)` on the imaginary axis.
    :domain: :math:`(-\infty, \infty)` for real :math:`x`,
        or :math:`\mathbb{C} \setminus \{-i, i\}` for complex :math:`x`
    :range: :math:`\left(-\dfrac{\pi}{2}, \dfrac{\pi}{2}\right)` for real :math:`x`,
        or :math:`\left\{w \in \mathbb{C} : -\dfrac{\pi}{2} < \operatorname{Re}(w) < \dfrac{\pi}{2}\right\}` for complex :math:`x`
    :returns: The value of :math:`\arctan(x)` in radians.
    :rtype: Real or Complex according to the type of ``x``.

.. funcsketch:function:: atan2(y, x)

    Arctangent function of two variables,
    using the signs of both arguments to determine the quadrant of the result.

    :param y: The y-coordinate.
    :type y: Real
    :param x: The x-coordinate.
    :type x: Real
    :definition: :math:`\mathrm{atan2}(y, x)`,
        the angle in radians between the positive x-axis
        and the ray to the point :math:`(x, y)`.
    :domain: :math:`(x, y) \neq (0, 0)`
    :range: :math:`(-\pi, \pi]`
    :returns: The value of :math:`\mathrm{atan2}(y, x)` in radians.
    :rtype: Real
