# Grammar of Expressions

## Operator Precedence

1. Function calls
2. `**` (power) (right associative)
3. `-` (unary minus)
4. `*`, `/` (multiplication and division)
5. `+`, `-` (addition and subtraction)

## Rules

| Name                 | Rule                                                             |
| :------------------- | :--------------------------------------------------------------- |
| `constant`           | Floating-point number or integer (complex numbers in the future) |
| `identifier`         | (See below)                                                      |
| `function_call_expr` | `identifier (sum_expr, sum_expr, ...)`                           |
| `atomic_value_expr`  | `function_call_expr` or `constant` or `identifier`               |
| `value_expr`         | `atomic_value_expr` or `'(' sum_expr ')'`                        |
| `factor_expr`        | `value_expr -('**' factor_expr)`                                 |
| `unary_expr`         | `('-' factor_expr) or factor_expr`                               |
| `term_expr`          | `unary_expr *(('*' unary_expr) or ('/' unary_expr))`             |
| `sum_expr`           | `term_expr *(( '+' term_expr) or ('-' term_expr))`               |
| `exp` (top level)    | `sum_expr`                                                       |

TODO:

- `--1` should be an error.

## Identifier Naming Rule

- First character must be a letter (a-z, A-Z) or underscore (\_)
- Subsequent characters can be letters, digits (0-9), or underscores
