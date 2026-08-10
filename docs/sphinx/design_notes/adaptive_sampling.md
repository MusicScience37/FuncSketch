# Adaptive Sampling of Function Values for Plotting

## Situations to Handle

- Regions near singularities where the value changes sharply (e.g. singularities of the Gamma function).
- Edges of the domain (e.g. the edges of `asin`, `acos`).
- Regions of rapid oscillation (e.g. functions like `sin(1/x)`).
- Regions with a jump discontinuity (e.g. the `floor` function).

The basic approach is to sample at a fixed resolution in `x` first,
then insert additional points between samples as needed to satisfy the required accuracy.

## Criteria for Adding a Point Between Two Samples

- The change in coordinates between two adjacent points is large.
  - A threshold is set on the change in the `y` coordinate.
    - The threshold is a value relative to the range of `y` shown in the plot.
- The change across three consecutive points is large.
  - The slope between each pair of adjacent points is computed, and a threshold is set on the change in slope.
    - The threshold is specified relative to the plot area: the slope is computed as the ratio of the change in `y` to the change in `x`, each normalized by the plot area.
- A point inside the plot range is adjacent to a point that is `inf` or `nan`.
  - Without an inserted point, the line would be cut off instead of connecting to the edge of the plot.

## Criteria for Not Adding a Point

- Both of two adjacent points are outside the plot range, or are `inf` or `nan`.
  - If only one of the two is inside the range, a point is still added (see above).
- The `x` distance between two adjacent points is already too small.
  - This prevents an infinite loop of repeatedly subdividing around a singularity.
    - This threshold is set relative to the range of `x`.
  - A lower bound is set on this threshold to limit the number of recursions (roughly 1/1000 of the size of the domain).
  - Whether to connect the two points with a line when this threshold is reached needs further consideration:
    - When the change in `y` is large, the function is likely piecewise, so the points should not be connected with a line (this is handled in the plotting step).
- The total number of points becomes too large.
  - Even after applying the criteria above, a maximum point count is set as a last resort to give up further subdivision.
    - A feature to warn the user when this limit is reached would be useful.

## Constraints

- A spike within an extremely narrow range cannot be handled reliably.
  - Handling this in general would require prior knowledge of the function, so instead the number of initial samples is made tunable, leaving the trade-off to the user.

## Requirements for the Algorithm

- Keep processing time low.
  - Repeatedly inserting points into the middle of a `vector` that already holds many elements is slow.
    Therefore, the initial sampling is kept in a separate `vector` from the final `vector` that includes the inserted points,
    to reduce the amount of copying within a `vector`.
