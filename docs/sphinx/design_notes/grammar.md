# Grammar of Expressions

## Operator Precedence

1. Function calls
2. `**` (power) (right associative)
3. `-` (unary minus)
4. `*`, `/` (multiplication and division)
5. `+`, `-` (addition and subtraction)

## Rules

| Name                 | Rule                                                 |
| :------------------- | :--------------------------------------------------- |
| `literal`            | (See below)                                          |
| `identifier`         | (See below)                                          |
| `function_call_expr` | `identifier (sum_expr, sum_expr, ...)`               |
| `atomic_value_expr`  | `function_call_expr` or `literal` or `identifier`    |
| `value_expr`         | `atomic_value_expr` or `'(' sum_expr ')'`            |
| `factor_expr`        | `value_expr -('**' factor_expr)`                     |
| `unary_expr`         | `('-' factor_expr) or factor_expr`                   |
| `term_expr`          | `unary_expr *(('*' unary_expr) or ('/' unary_expr))` |
| `sum_expr`           | `term_expr *(( '+' term_expr) or ('-' term_expr))`   |
| `exp` (top level)    | `sum_expr`                                           |

TODO:

- `--1` should be an error.

## Literals

Literals are parsed as follows:

- A token is parsed as `Integer` if it is a number without a decimal point or an exponent
  (e.g. `1`, `-12`, `0`)
- A token is parsed as `Real` if it is a number with a decimal point and/or an exponent
  (e.g. `1.0`, `-12.34`, `1e+6`)
- A token is parsed as an imaginary number of type `Complex` if it is a number
  with a trailing `i` (e.g. `1.0i`, `-1e+6i`, `12i`)

## Identifiers

- Identifiers are used in followings:
  - Parameter names when used in `atomic_value_expr`. Currently only `x` is allowed.
  - Constant names when used in `atomic_value_expr`.
    - A parameter name and a constant name cannot have the same identifier.
  - Function names when used in `function_call_expr`.
- Identifiers are case-sensitive.
- Identifiers must be named as follows:
  - First character must be a letter (a-z, A-Z) or underscore (\_)
  - Subsequent characters can be letters, digits (0-9), or underscores
