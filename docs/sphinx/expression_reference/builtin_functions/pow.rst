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

.. funcsketch:function:: sqrt(x)

    Square root function.

    :param x: The value to take the square root of.
    :type x: Real
    :definition: :math:`\mathrm{sqrt}(x) = \sqrt{x}`
    :domain: :math:`[0, \infty)`
    :range: :math:`[0, \infty)`
    :returns: The value of :math:`\sqrt{x}`.
    :rtype: Real

.. funcsketch:function:: cbrt(x)

    Cube root function.

    :param x: The value to take the cube root of.
    :type x: Real
    :definition: :math:`\mathrm{cbrt}(x) = \sqrt[3]{x}`
    :domain: :math:`(-\infty, \infty)`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\sqrt[3]{x}`.
    :rtype: Real
