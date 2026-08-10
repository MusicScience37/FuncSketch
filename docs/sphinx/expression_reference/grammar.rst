Grammar
==================

.. todo::
    Add more contents.

Types
------------

.. csv-table::
    :header: "Type", "Description"

    Integer, "32bit signed integers."
    Real, "Double-precision floating-point numbers."

.. note::
    Future implementation may support boolean and complex numbers.

Implicit Conversions
..........................

- ``Integer`` can be implicitly converted to ``Real``.

Operators
--------------

.. csv-table::
    :header: "Operator", "Description"

    "``-x``", "Negation"
    "``x + y``", "Addition"
    "``x - y``", "Subtraction"
    "``x * y``", "Multiplication"
    "``x / y``", "Division"
    "``x ** y``", "Power (Works same as :funcsketch:func:`pow`)"

.. note::
    ``**`` is right-associative (e.g. ``2 ** 3 ** 4`` is parsed as
    ``2 ** (3 ** 4)``).
