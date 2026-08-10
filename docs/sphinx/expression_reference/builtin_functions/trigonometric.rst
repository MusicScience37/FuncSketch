Trigonometric Functions
==========================================

.. funcsketch:function:: sin(x)

    Sine function.

    :param x: The angle in radians.
    :type x: Real
    :definition: :math:`\sin(x)`
    :domain: :math:`(-\infty, \infty)`
    :range: :math:`[-1, 1]`
    :returns: The value of :math:`\sin(x)`.
    :rtype: Real

.. funcsketch:function:: cos(x)

    Cosine function.

    :param x: The angle in radians.
    :type x: Real
    :definition: :math:`\cos(x)`
    :domain: :math:`(-\infty, \infty)`
    :range: :math:`[-1, 1]`
    :returns: The value of :math:`\cos(x)`.
    :rtype: Real

.. funcsketch:function:: tan(x)

    Tangent function.

    :param x: The angle in radians.
    :type x: Real
    :definition: :math:`\tan(x) = \dfrac{\sin(x)}{\cos(x)}`
    :domain: :math:`x \neq \dfrac{\pi}{2} + n\pi \ (n \in \mathbb{Z})`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\tan(x)`.
    :rtype: Real

.. funcsketch:function:: asin(x)

    Arcsine function.

    :param x: The value to take the arcsine of.
    :type x: Real
    :definition: :math:`\arcsin(x)`, the inverse function of :math:`\sin(x)`.
    :domain: :math:`[-1, 1]`
    :range: :math:`\left[-\dfrac{\pi}{2}, \dfrac{\pi}{2}\right]`
    :returns: The value of :math:`\arcsin(x)` in radians.
    :rtype: Real

.. funcsketch:function:: acos(x)

    Arccosine function.

    :param x: The value to take the arccosine of.
    :type x: Real
    :definition: :math:`\arccos(x)`, the inverse function of :math:`\cos(x)`.
    :domain: :math:`[-1, 1]`
    :range: :math:`[0, \pi]`
    :returns: The value of :math:`\arccos(x)` in radians.
    :rtype: Real

.. funcsketch:function:: atan(x)

    Arctangent function.

    :param x: The value to take the arctangent of.
    :type x: Real
    :definition: :math:`\arctan(x)`, the inverse function of :math:`\tan(x)`.
    :domain: :math:`(-\infty, \infty)`
    :range: :math:`\left(-\dfrac{\pi}{2}, \dfrac{\pi}{2}\right)`
    :returns: The value of :math:`\arctan(x)` in radians.
    :rtype: Real

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
