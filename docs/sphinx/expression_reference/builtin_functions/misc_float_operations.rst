.. _builtin_functions_misc_float_operations:

Miscellaneous Floating-point Operations
=============================================

.. funcsketch:function:: abs(x)

    Absolute value function.

    :param x: The value of which the absolute value is taken.
    :type x: Real or Complex
    :definition: :math:`\mathrm{abs}(x) = \lvert x \rvert`
    :domain: :math:`(-\infty, \infty)` for real :math:`x`,
        or :math:`\mathbb{C}` for complex :math:`x`
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

.. funcsketch:function:: round(x)

    Rounding function.

    :param x: The value to round.
    :type x: Real
    :definition: :math:`\mathrm{round}(x)` is the nearest integer to :math:`x`, rounding halfway cases away from zero.
    :domain: :math:`(-\infty, \infty)`
    :range: Integers
    :returns: The value of :math:`x` rounded to the nearest integer.
    :rtype: Real
