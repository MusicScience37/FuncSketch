Miscellaneous Floating-point Operations
=============================================

.. funcsketch:function:: abs(x)

    Absolute value function.

    :param x: The value of which the absolute value is taken.
    :type x: Real
    :definition: :math:`\mathrm{abs}(x) = \lvert x \rvert`
    :domain: :math:`(-\infty, \infty)`
    :range: :math:`[0, \infty)`
    :returns: The absolute value of :math:`x`.
    :rtype: Real

.. funcsketch:function:: ceil(x)

    Ceiling function.

    :param x: The value of which the ceiling is taken.
    :type x: Real
    :definition: :math:`\mathrm{ceil}(x) = \lceil x \rceil`
    :domain: :math:`(-\infty, \infty)`
    :range: Integers
    :returns: The smallest integer not less than :math:`x`.
    :rtype: Real

.. funcsketch:function:: floor(x)

    Floor function.

    :param x: The value of which the floor is taken.
    :type x: Real
    :definition: :math:`\mathrm{floor}(x) = \lfloor x \rfloor`
    :domain: :math:`(-\infty, \infty)`
    :range: Integers
    :returns: The largest integer not greater than :math:`x`.
    :rtype: Real

.. funcsketch:function:: trunc(x)

    Truncation function.

    :param x: The value to truncate.
    :type x: Real
    :definition: :math:`\mathrm{trunc}(x) = \mathrm{sign}(x) \lfloor |x| \rfloor`
    :domain: :math:`(-\infty, \infty)`
    :range: Integers
    :returns: The integer part of :math:`x`, discarding the fractional part.
    :rtype: Real
