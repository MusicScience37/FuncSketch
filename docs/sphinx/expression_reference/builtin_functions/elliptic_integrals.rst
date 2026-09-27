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

.. funcsketch:function:: comp_elliptic_e(k)

    Complete elliptic integral of the second kind.

    :param k: The modulus.
    :type k: Real
    :definition: :math:`E(k) = E(\pi / 2, k) = \displaystyle\int_0^{\pi / 2} \sqrt{1 - k^2 \sin^2 \theta} \, d\theta`
    :domain: :math:`-1 \le k \le 1`
    :range: :math:`[1, \pi / 2]`
    :returns: The value of :math:`E(k)`.
    :rtype: Real

    .. image:: plots/comp_elliptic_e.webp

.. funcsketch:function:: elliptic_pi(n, phi, k)

    (Incomplete) elliptic integral of the third kind.

    :param n: The characteristic.
    :type n: Real
    :param phi: The amplitude.
    :type phi: Real
    :param k: The modulus.
    :type k: Real
    :definition: :math:`\Pi(n, \phi, k) = \displaystyle\int_0^{\phi} \frac{d\theta}{(1 - n \sin^2 \theta) \sqrt{1 - k^2 \sin^2 \theta}}`
    :domain: :math:`\phi \in \mathbb{R}`, :math:`n < 1`, and :math:`|k| < 1`,
        or :math:`|\phi| < \pi / 2`, :math:`n \sin^2 \phi < 1`, and :math:`k^2 \sin^2 \phi < 1`
    :range: :math:`(-\infty, \infty)`
    :returns: The value of :math:`\Pi(n, \phi, k)`.
    :rtype: Real

    .. image:: plots/elliptic_pi.webp

.. funcsketch:function:: comp_elliptic_pi(n, k)

    Complete elliptic integral of the third kind.

    :param n: The characteristic.
    :type n: Real
    :param k: The modulus.
    :type k: Real
    :definition: :math:`\Pi(n, k) = \Pi(n, \pi / 2, k) = \displaystyle\int_0^{\pi / 2} \frac{d\theta}{(1 - n \sin^2 \theta) \sqrt{1 - k^2 \sin^2 \theta}}`
    :domain: :math:`n < 1` and :math:`-1 < k < 1`
    :range: :math:`(0, \infty)`
    :returns: The value of :math:`\Pi(n, k)`.
    :rtype: Real

    .. image:: plots/comp_elliptic_pi.webp
