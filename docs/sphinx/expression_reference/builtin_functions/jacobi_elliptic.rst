Jacobi Elliptic Functions
==========================================

Jacobi elliptic functions are defined as inverse functions of the elliptic integral of the first kind.

.. funcsketch:function:: jacobi_sn(u, k)

    Jacobi elliptic function :math:`\mathrm{sn}`.

    :param u: The argument.
    :type u: Real
    :param k: The modulus.
    :type k: Real
    :definition: :math:`\mathrm{sn}(u, k) = \sin \phi` where :math:`u = F(\phi, k)`
        (:math:`F` is the elliptic integral of the first kind :funcsketch:func:`elliptic_f`)
    :domain: :math:`u \in \mathbb{R}` and :math:`k \in \mathbb{R}`
    :range: :math:`[-1, 1]`
    :returns: The value of :math:`\mathrm{sn}(u, k)`.
    :rtype: Real

    .. image:: plots/jacobi_sn.webp

.. funcsketch:function:: jacobi_cn(u, k)

    Jacobi elliptic function :math:`\mathrm{cn}`.

    :param u: The argument.
    :type u: Real
    :param k: The modulus.
    :type k: Real
    :definition: :math:`\mathrm{cn}(u, k) = \cos \phi` where :math:`u = F(\phi, k)`
        (:math:`F` is the elliptic integral of the first kind :funcsketch:func:`elliptic_f`)
    :domain: :math:`u \in \mathbb{R}` and :math:`k \in \mathbb{R}`
    :range: :math:`[-1, 1]`
    :returns: The value of :math:`\mathrm{cn}(u, k)`.
    :rtype: Real

    .. image:: plots/jacobi_cn.webp

.. funcsketch:function:: jacobi_dn(u, k)

    Jacobi elliptic function :math:`\mathrm{dn}`.

    :param u: The argument.
    :type u: Real
    :param k: The modulus.
    :type k: Real
    :definition: :math:`\mathrm{dn}(u, k) = \dfrac{d \phi}{d u}` where :math:`u = F(\phi, k)`
        (:math:`F` is the elliptic integral of the first kind :funcsketch:func:`elliptic_f`)
    :domain: :math:`u \in \mathbb{R}` and :math:`k \in \mathbb{R}`
    :range: :math:`[-1, 1]`
    :returns: The value of :math:`\mathrm{dn}(u, k)`.
    :rtype: Real

    .. image:: plots/jacobi_dn.webp
