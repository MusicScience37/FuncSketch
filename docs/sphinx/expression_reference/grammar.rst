Grammar
==================

This page describes the grammar of function expressions in FuncSketch.

Types
------------

FuncSketch supports the following types of values:

.. csv-table::
    :header: "Type", "Description"

    Integer, "32-bit signed integers."
    Real, "Double-precision floating-point numbers."

When you write a number in a function expression,
it is automatically recognized as follows:

- ``Integer`` if it is an integer number without a decimal point
  (e.g. ``1``, ``-12``, ``0``)
- ``Real`` if it is a number with a decimal point and/or an exponent
  (e.g. ``1.0``, ``-12.34``, ``1e+6``)

.. note::
    Future implementation may support boolean and complex numbers.

Implicit Conversions
..........................

- ``Integer`` can be implicitly converted to ``Real``.
  This conversion is done automatically when an ``Integer`` value is
  used with a ``Real`` value in binary operations (e.g. ``1 + 2.0``),
  or when an ``Integer`` value is passed to a function that takes
  a ``Real`` argument.

Operators
--------------

The following operators are supported:

.. csv-table::
    :header: "Operator", "Description"

    "``-x``", "Negation"
    "``x + y``", "Addition"
    "``x - y``", "Subtraction"
    "``x * y``", "Multiplication"
    "``x / y``", "Division"
    "``x ** y``", "Power :math:`x^y` (Works the same as :funcsketch:func:`pow`)"

.. note::
    ``**`` is right-associative (e.g. ``2 ** 3 ** 4`` is parsed as
    ``2 ** (3 ** 4)``).

.. note::
    The right operand of ``**`` cannot be directly preceded by ``-``
    unless it is a number literal (e.g. ``2 ** -3`` is valid).
    To negate an identifier, a function call, or a parenthesized
    expression, wrap it in parentheses
    (e.g. ``2 ** (-x)`` instead of ``2 ** -x``).

Operator Precedence
...........................

Operators have the following precedence (from highest to lowest):

1. ``**`` (power)
2. ``-`` (negation)
3. ``*``, ``/`` (multiplication, division)
4. ``+``, ``-`` (addition, subtraction)

You can use parentheses ``()`` to change the order of evaluation.

Identifiers
-----------------

In function expressions, the following identifiers exist:

- Parameter of the function. Currently ``x`` is the only parameter name.
- Constants. (e.g. ``pi``, ``e``)
- Functions. (e.g. ``sin``, ``exp``)

Identifiers before ``(`` are treated as function names,
and other identifiers are treated as parameters or constants.
For example,

- When ``exp(x)`` is parsed, FuncSketch searches for a function
  named ``exp``.
- When ``x + 1`` is parsed, FuncSketch searches for
  a constant or a parameter named ``x``.

For built-in names of constants and functions,
see :ref:`builtin_constants` and :ref:`builtin_functions`.
