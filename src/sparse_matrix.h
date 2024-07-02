#ifndef ALGORITHM_SPARSE_MATRIX_H
#define ALGORITHM_SPARSE_MATRIX_H

#include <iostream>
#include <vector>

class SparseMatrix {
private:
    std::vector<int> values;
    std::vector<int> rows;
    std::vector<int> cols;
    int m;
    int n;

public:
    SparseMatrix(std::vector<std::vector<int>> &matrix) {
        m = matrix.size();
        n = matrix[0].size();

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(matrix[i][j] != 0) {
                    values.push_back(matrix[i][j]);
                    rows.push_back(i);
                    cols.push_back(j);
                }
            }
        }
    }

    int getValue(int row, int col) {
        for(int i = 0; i < values.size(); ++i) {
            if(rows[i] == row && cols[i] == col) {
                return values[i];
            }
        }

        return 0;
    }

    void printMatrix() {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cout << getValue(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif //ALGORITHM_SPARSE_MATRIX_H
