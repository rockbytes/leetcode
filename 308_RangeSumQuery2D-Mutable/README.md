### Problem
Given a 2D matrix `matrix`, find the sum of the elements inside the rectangle defined by its upper left corner `(row1, col1)` and lower right corner `(row2, col2)`.

Implement the `NumMatrix` class:

- `NumMatrix(int[][] matrix)` initializes the object with the integer matrix `matrix`.
- `void update(int row, int col, int val)` updates the value of `matrix[row][col]` to be val.
- `int sumRegion(int row1, int col1, int row2, int col2)` returns the sum of the elements of the `matrix` array inside the rectangle defined by its upper left corner `(row1, col1)` and lower right corner `(row2, col2)`.

### Example
https://www.geeksforgeeks.org/two-dimensional-binary-indexed-tree-or-fenwick-tree/

**Input**
<br/>
["NumMatrix", "sumRegion", "update", "sumRegion"]
<br />
[[[[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]], [2, 1, 4, 3], [3, 2, 2], [2, 1, 4, 3]]
<br />
**Output**
<br />
[null, 8, null, 10]
