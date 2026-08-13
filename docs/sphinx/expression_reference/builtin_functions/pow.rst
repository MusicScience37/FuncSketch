Power Functions
=====================

.. funcsketch:function:: pow(base, exponent)

    Power function.

    :param base: The base of the power.
    :type base: Integer, Real, or Complex
    :param exponent: The exponent of the power.
    :type exponent: Integer, Real, or Complex
    :definition: :math:`\mathrm{pow}(\mathrm{base}, \mathrm{exponent}) = \mathrm{base}^{\mathrm{exponent}}`.
        When either :math:`\mathrm{base}` or :math:`\mathrm{exponent}` is complex,
        this is computed as :math:`\exp(\mathrm{exponent} \log(\mathrm{base}))`
        using the principal branch of :math:`\log`.
    :domain:
        - For integer or real numbers,
          :math:`\mathrm{base} > 0`, or
          :math:`\mathrm{base} = 0` and :math:`\mathrm{exponent} \geq 0`, or
          :math:`\mathrm{base} < 0` and :math:`\mathrm{exponent}` has an integer value
          (same restrictions as ``std::pow`` in C++).
        - For complex numbers, :math:`\mathrm{base} \neq 0`
          (same restrictions as ``std::pow`` in C++).
    :range: :math:`(-\infty, \infty)` when both :math:`\mathrm{base}` and :math:`\mathrm{exponent}` are real,
        or :math:`\mathbb{C}` when :math:`\mathrm{base}` or :math:`\mathrm{exponent}` is complex
    :returns: The value of :math:`\mathrm{base}^{\mathrm{exponent}}`.
    :rtype: Real or Complex according to the type of ``base`` and ``exponent``.

.. funcsketch:function:: sqrt(x)

    Square root function.

    :param x: The value to take the square root of.
    :type x: Real or Complex
    :definition: :math:`\mathrm{sqrt}(x) = \sqrt{x}`.
        For complex :math:`x`, the principal branch is used,
        with a branch cut along :math:`(-\infty, 0)` on the real axis.
    :domain: :math:`[0, \infty)` for real :math:`x`,
        or :math:`\mathbb{C}` for complex :math:`x`
    :range: :math:`[0, \infty)` for real :math:`x`,
        or :math:`\{w \in \mathbb{C} : \operatorname{Re}(w) \geq 0\}` for complex :math:`x`
    :returns: The value of :math:`\sqrt{x}`.
    :rtype: Real or Complex according to the type of ``x``.

.. funcsketch:function:: cbrt(x)

    Cube root function.

    :param x: The value to take the cube root of.
    :type x: Real
    :definition: :math:`\mathrm{cbrt}(x) = \sqrt[3]{x}`
    :domain: :math:`(-\infty, \infty)`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\sqrt[3]{x}`.
    :rtype: Real
