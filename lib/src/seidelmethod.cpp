#include <iostream>
#include <cmath>
#include "lib/src/seidelmethod.h"
#include <QString>
using namespace std;



vector<double> SeidelMethod::compute(const Matrix &matrix,
                                          const vector<double> &b) {
    double det = determinant(matrix);
    if (det == 0){
        throw QString("Определитель матрицы равен нулю!");
    }
    pair<vector<vector<double>>, vector<double>> pair;

        vector<vector<double>> A = matrix;
        vector<double> B = b;

        vector<double> result(A.size());
        result.assign(result.size(), 0);

        vector<vector<double>> _A = A;
        vector<double> _B = B;

        for (int i = 0; i < A.size(); i++) {
            if (A[i][i] != 0) { //âîò çäåñü ïðîâåðêà íà 0 è óìíîæåíèå íà -1
                for (int j = 0; j < A.size(); j++) {
                    if (i != j) {
                        A[i][j] /= -A[i][i];
                    }
                }
                B[i] /= A[i][i];
                A[i][i] = 0;
            }
        }

        vector<double> cur_iter(A.size());
        vector<double> prev_iter(A.size());

        if (checkForDiagonal(A)) {
            prev_iter.assign(prev_iter.size(), 0);
            for (int i = 0; i < A.size(); i++) {
                prev_iter = cur_iter;
                for (int j = 0; j < A.size(); j++) {
                    cur_iter[i] += A[i][j] * prev_iter[j];
                }
                cur_iter[i] += B[i];
                prev_iter.assign(prev_iter.size(), 0);
            }
            while (stopIter(cur_iter, prev_iter)) {
                prev_iter = cur_iter;
                cur_iter.assign(A.size(), 0);
                for (int i = 0; i < A.size(); i++) {
                    if (i > 0) {
                        prev_iter[i - 1] = cur_iter[i - 1];
                    }
                    for (int j = 0; j < A.size(); j++) {
                        cur_iter[i] += A[i][j] * prev_iter[j];
                    }
                    cur_iter[i] += B[i];
                }

            }
            result = cur_iter;
        }
        else {
            cout << "this matrix is not diagonal predominance" << endl;
            pair = makeDiagonal(_A, _B);
            for (int i = 0; i < pair.first.size(); i++) {
                result[i] = pair.second[i] / pair.first[i][i];
            }
        }
    return result;
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

vector<double> SeidelMethod::multiplicationMatVec(const Matrix &matrix, const vector<double> &b) {
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
bool SeidelMethod::stopIter(vector<double> a, vector<double> b){
    vector<double>c = a;
    for (int i = 0; i < a.size(); i++) {
            c[i] -= b[i];
    }
    return !(vectorNorm(c) < epsilon);
}
