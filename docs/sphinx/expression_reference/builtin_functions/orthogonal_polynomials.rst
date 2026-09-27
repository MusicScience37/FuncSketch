Orthogonal Polynomials
==========================================

Orthogonal polynomials are families of polynomials
which are orthogonal to each other under some inner product.

.. funcsketch:function:: hermite(n, x)

    Hermite polynomial (physicist's Hermite polynomial).

    :param n: The degree of the Hermite polynomial.
    :type n: Integer
    :param x: The argument of the Hermite polynomial.
    :type x: Real
    :definition: :math:`H_n(x) = (-1)^n e^{x^2} \dfrac{d^n}{dx^n} e^{-x^2}`
    :domain: :math:`n \in \{0, 1, 2, \ldots\}`, :math:`x \in \mathbb{R}`
    :returns: The value of :math:`H_n(x)`.
    :rtype: Real

    .. image:: plots/hermite.webp
