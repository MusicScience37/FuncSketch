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

.. funcsketch:function:: comp_elliptic_k(k)

    Complete elliptic integral of the first kind.

    :param k: The modulus.
    :type k: Real
    :definition: :math:`K(k) = F(\pi / 2, k) = \displaystyle\int_0^{\pi / 2} \frac{d\theta}{\sqrt{1 - k^2 \sin^2 \theta}}`
    :domain: :math:`-1 < k < 1`
    :range: :math:`[\pi / 2, \infty)`
    :returns: The value of :math:`K(k)`.
    :rtype: Real

    .. image:: plots/comp_elliptic_k.webp

.. funcsketch:function:: elliptic_e(phi, k)

    (Incomplete) elliptic integral of the second kind.

    :param phi: The amplitude.
    :type phi: Real
    :param k: The modulus.
    :type k: Real
    :definition: :math:`E(\phi, k) = \displaystyle\int_0^{\phi} \sqrt{1 - k^2 \sin^2 \theta} \, d\theta`
    :domain: :math:`\phi \in \mathbb{R}` and :math:`|k| \le 1`,
        or :math:`|k| > 1` and :math:`|\phi| < \arcsin(1 / |k|)`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`E(\phi, k)`.
    :rtype: Real

    .. image:: plots/elliptic_e.webp
