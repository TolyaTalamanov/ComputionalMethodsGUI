
#include <numeric>
#include <algorithm>
#include <iostream>
#include "lib/include/icomputionalmethods.h"
#include "simpleiterationmethod.h"
#include "QString"

using namespace std;
std::vector<double> SimpleIterationMethod::compute(const Matrix &matrix,
                                                   const std::vector<double> &b) {
    double det = determinant(matrix);
    if (det == 0){
        throw QString("Определитель матрицы равен нулю!");
    }
    pair<vector<vector<double>>, vector<double>> pair;
        vector<double> result(matrix.size());
        result.assign(b.size(), 0);

        vector<vector<double>> A = matrix;
        vector<double> B = b;

        vector<vector<double>> _A = A;
        vector<double> _B = B;

        for (int i = 0; i < A.size(); i++) {
            if (A[i][i] != 0) {
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
                for (int j = 0; j < A.size(); j++) {
                    cur_iter[i] = +A[i][j] * prev_iter[i];
                }
                cur_iter[i] += B[i];
            }
            while (stopIter(cur_iter, prev_iter)) {
                prev_iter = cur_iter;
                cur_iter.assign(A.size(), 0);
                for (int i = 0; i < A.size(); i++) {
                    for (int j = 0; j < A.size(); j++) {
                        cur_iter[i] += A[i][j] * prev_iter[j];
                    }
                    cur_iter[i] += B[i];
                }

            }
            result = cur_iter;
        }
        else {
            //throw QString(" Эта матрица не является диагональным преобладанием");
            pair = makeDiagonal(_A, _B);
            for (int i = 0; i < pair.first.size(); i++) {
                result[i] = pair.second[i] / pair.first[i][i];
            }
        }

    return result;
}

bool SimpleIterationMethod::stopIter(vector<double> a, vector<double> b){
    vector<double>c = a;
    for (int i = 0; i < a.size(); i++) {
            c[i] -= b[i];
    }
    return !(vectorNorm(c) < epsilon);
}
