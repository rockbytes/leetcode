// Complexity:
// - Time: O(m*n*logm*logn), where m is the number of rows and n is the number of columns
// - Space: O(m*n)
//
// Improvement:
// - The data member _matrix in class NumMatrix is not need. The current value can be calculate by: 
//   _tree[row+1][col+1] - _tree[row][col+1] - _tree[row+1][col] + _tree[row][col]

class BinaryIndexedTree2D {
public:
    BinaryIndexedTree2D(const vector<vector<int>> &matrix) {
        int m = matrix.size(), n = 0;
        if (m > 0) n = matrix[0].size();

        _tree = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                add(i + 1, j + 1, matrix[i][j]);
            }
        }
    }

    int lowBit(int index) {
        return index & -index;
    }

    void add(int row, int col, int val) {
        for (int i = row; i < _tree.size(); i += lowBit(i)) {
            for (int j = col; j < _tree[0].size(); j += lowBit(j)) {
                _tree[i][j] += val;
            }
        }
    }

    int query(int row, int col) {
        int sum = 0;
        for (int i = row; i > 0; i -= lowBit(i)) {
            for (int j = col; j > 0; j -= lowBit(j)) {
                sum += _tree[i][j];
            }
        }

        return sum;
    }

private:
    vector<vector<int>> _tree;
};

class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) : _bit2D(matrix) {
        _matrix.swap(matrix);
    }
    
    void update(int row, int col, int val) {
        _bit2D.add(row + 1, col + 1, val - _matrix[row][col]);
        _matrix[row][col] = val;
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return _bit2D.query(row2 + 1, col2 + 1) - 
            _bit2D.query(row1, col2 + 1) -
            _bit2D.query(row2 + 1, col1) +
            _bit2D.query(row1, col1);
    }

private:
    BinaryIndexedTree2D _bit2D;
    vector<vector<int>> _matrix;
};
