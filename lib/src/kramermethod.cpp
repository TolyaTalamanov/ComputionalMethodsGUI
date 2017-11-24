#include<iostream>
#include "lib/src/kramermethod.h"
#include <QString>

std::vector<double> KramerMethod::compute(const Matrix &matrix,
                                          const std::vector<double> &b) {
    std::vector<double> result(b.size());
    std::vector<double> coefdet(b.size());
    double det = determinant(matrix);
    if (det == 0){
        throw QString("Определитель матрицы равен нулю!");

    }
    for (int i = 0; i < matrix[0].size(); i++) {
        coefdet[i] = determinant(createSpecialMatrix(matrix, b, i));  //побочные миноры
        result[i] = coefdet[i] / det;
    }
    return result;
}
int KramerMethod::getMaxRow(const Matrix& matrix, int col) {
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


double KramerMethod::determinant(const Matrix &matrix) {
    Matrix A = matrix;
    double result = 0;
    double d = 0;
    std::vector<double> vect = A[0];
    for (int k = 0; k < vect.size(); k++) { // ïðÿìîé õîä
        for (int j = k + 1; j < vect.size(); j++) {
            if (A[k][k] == 0){
                return result;
            }
            d = A[j][k] / A[k][k]; // ôîðìóëà (1)
            for (int i = k; i < A.size(); i++) {
                A[j][i] = A[j][i] - d * A[k][i]; // ôîðìóëà (2)
            }
        }
    }
    result = 1;
    for (int i = 0; i < A.size(); i++) {
        result *= A[i][i];
    }
    return result;
}

Matrix KramerMethod::createSpecialMatrix(const Matrix &matrix, const std::vector<double> &b, int pos) {
    Matrix A = matrix;
    for (int i = 0; i < b.size(); i++) {
        A[i][pos] = b[i];
    }
    return A;
}
