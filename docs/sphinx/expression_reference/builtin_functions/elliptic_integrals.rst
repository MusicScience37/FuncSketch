Elliptic Integrals
==========================================

Elliptic integrals are integrals which arise in the calculation of the arc length of an ellipse.

.. funcsketch:function:: elliptic_f(phi, k)

    (Incomplete) elliptic integral of the first kind.

    :param phi: The amplitude.
    :type phi: Real
    :param k: The modulus.
    :type k: Real
    :definition: :math:`F(\phi, k) = \displaystyle\int_0^{\phi} \frac{d\theta}{\sqrt{1 - k^2 \sin^2 \theta}}`
    :domain: :math:`\phi \in \mathbb{R}` and :math:`|k| < 1`,
        or :math:`|k| \ge 1` and :math:`|\phi| < \arcsin(1 / |k|)`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`F(\phi, k)`.
    :rtype: Real

    .. image:: plots/elliptic_f.webp
