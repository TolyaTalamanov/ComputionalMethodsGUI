#include <algorithm>
#include <iterator>
#include <iostream>
#include "lib/src/gaussmethod.h"
#include <iostream>
std::vector<double> GaussMethod::compute(const Matrix &matrix,
                                         const std::vector<double>& b) {
    Matrix A = matrix;
    std::vector<double> B = b;
    int swapRow;
    int size = A.size();
    double coeff;
    for(int i = 0; i < size - 1; i++){
        swapRow = getMaxRow(A, i);
        std::iter_swap(A.begin() + swapRow, A.begin() + i);
        std::iter_swap(B.begin() + swapRow, B.begin() + i);

        for(int k  = i; k < size - 1; k++ ){
            coeff = A[k + 1][i] / A[i][i];
            B[k + 1] -= B[i] * coeff;
            for(int j = 0;j < size; j++){
                A[k + 1][j] -= A[i][j] * coeff;
            }
        }

    }

    std::vector<double> x(size);
    x[size - 1] = B[size - 1] / A[size - 1][size - 1];
    for(int i = size - 2; i >= 0; i--){
        x[i] = B[i];
        for(int j = size - 1; j > i; j--){
            x[i] = x[i] - x[j] * A[i][j];
        }
        x[i] /= A[i][i];
    }
    return x;
}

int GaussMethod::getMaxRow(const Matrix& matrix, int col) {
    double max = matrix[col][col];
    int imax = col;
    for(int i = col + 1; i < matrix.size(); i++){
        if(abs(matrix[i][col]) > max){
            max = abs(matrix[i][col]);
            imax = i;
        }
    }
    return imax;
}

