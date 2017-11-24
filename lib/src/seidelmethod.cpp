#include <iostream>
#include <cmath>
#include "lib/src/seidelmethod.h"
#include <QString>
using namespace std;



std::vector<double> SeidelMethod::compute(const Matrix &matrix,
                                          const std::vector<double> &b) {
    Matrix A(matrix.size());
    A = multiplicationMatrix(matrix);
    vector<double> B = multiplicationMatVec(matrix, b);

    Matrix D(matrix.size());
    for(int i = 0; i < D.size(); i++) {
        D[i].resize(D.size());
        for (int j = 0; j < D.size(); j++) {
            if (i == j)
                D[i][j] = 0;
            else {
                if (A[i][i] == 0){
                    QString("Система не имеет единственного решения!");

                }
                D[i][j] = (-1) * A[i][j] / A[i][i];
            }
        }
        B[i] /= A[i][i];
    }
    vector<double> xNext(matrix.size());
    vector<double> xPrev(A.size());
    double  norma = epsilon;
    copy(B.begin(), B.end(), xNext.begin());
    int iteration = 0;
    do{
        copy(xNext.begin(), xNext.end(), xPrev.begin());
        fill(xNext.begin(), xNext.end(), 0.0);

        for (int i =0; i < A.size(); i++){
            for(int j = 0; j < A.size(); j++){
                if(j < i)
                    xNext[i] += D[i][j] * xNext[j];
                else
                    xNext[i] += D[i][j] * xPrev[j];
            }
            xNext[i] +=B[i];
            if (norma < fabs(xNext[i] - xPrev[i]))
                norma = fabs(xNext[i] - xPrev[i]);
        }
        iteration++;
    } while (norma >= epsilon && iteration < 1000);

    return xNext;
}

void SeidelMethod::transpose(const Matrix &input, Matrix &output) {
    for (int i = 0; i < input.size(); i++){
        for (int j = 0; j < input.size(); j++) {
            output[i][j] = input[j][i];
        }
    }
}

Matrix SeidelMethod::multiplicationMatrix(const Matrix &matrix) {
    Matrix result(matrix.size());
    for(int i = 0; i < matrix.size(); i++) {
        result[i].resize(matrix.size());
        fill(result[i].begin(), result[i].end(), 0.0);
    }
    Matrix trans = matrix;
    transpose(matrix, trans);
    cout << "A' * A = " << endl;

    for(int i = 0; i < trans.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            for (int r = 0; r < matrix[i].size(); r++){
                result[i][j] += trans[i][r] * matrix[r][j];
            }
        }
    }
    for(int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result.size(); j++)
            cout << result[i][j] << " ";
        cout << endl;
    }
    return result;
}

std::vector<double> SeidelMethod::multiplicationMatVec(const Matrix &matrix, const vector<double> &b) {
    std::vector<double> result(b.size());
    Matrix trans = matrix;
    transpose(matrix, trans);
    cout << endl;
    for(int i = 0; i < matrix.size(); i++){
        result[i] = 0.0;
        for(int j = 0; j < b.size(); j++){
            result[i] += trans[i][j] * b[j];
        }
        cout << result[i] << " ";
    }
    return  result;
}
