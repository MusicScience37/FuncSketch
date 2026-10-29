Mathematical Operations
===========================

In addition to mathematical functions,
FuncSketch supports mathematical operations,
which take function expressions as arguments.
Currently, only numerical integration is supported.

.. funcsketch:function:: integrate(function, left, right)

    Numerical integration.

    ``function`` is integrated with respect to the variable ``s`` over the interval from ``left`` to ``right``.
    ``left`` and ``right`` can be any real numbers.

    ``left >= right`` is allowed.
    ``integrate(function, left, right)`` is equivalent to ``-integrate(function, right, left)``.

    The current implementation supports only integration over finite intervals
    and integrands that are finite over the whole interval including its endpoints.

    Examples:

    - ``integrate(s, 0, 1)`` calculates :math:`\int_0^1 s\,ds`.
    - ``integrate(cos(s), 0, x)`` calculates :math:`\int_0^x \cos(s)\,ds`.

    :param function: The function to integrate.
    :type function: Function expression
    :param left: The left endpoint of the integration interval.
    :type left: Real
    :param right: The right endpoint of the integration interval.
    :type right: Real
    :definition: :math:`\int_{\text{left}}^{\text{right}} \text{function}(s)\,ds`
    :returns: The result of the numerical integration.
    :rtype: Real or Complex according to the return type of ``function``.
