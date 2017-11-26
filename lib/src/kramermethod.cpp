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





