Power Functions
=====================

.. funcsketch:function:: pow(base, exponent)

    Power function.

    :param base: The base of the power.
    :type base: Integer or Real
    :param exponent: The exponent of the power.
    :type exponent: Integer or Real
    :definition: :math:`\mathrm{pow}(\mathrm{base}, \mathrm{exponent}) = \mathrm{base}^{\mathrm{exponent}}`
    :domain: :math:`\mathrm{base} > 0`, or
        :math:`\mathrm{base} = 0` and :math:`\mathrm{exponent} \geq 0`, or
        :math:`\mathrm{base} < 0` and :math:`\mathrm{exponent}` has an integer value.
        (Same restrictions as ``std::pow`` in C++.)
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\mathrm{base}^{\mathrm{exponent}}`.
    :rtype: Real
