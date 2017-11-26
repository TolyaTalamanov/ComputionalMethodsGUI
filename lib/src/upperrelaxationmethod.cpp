#include "lib/src/upperrelaxationmethod.h"
#include <iostream>
#include<math.h>
#include <QString>
using  namespace std;



std::vector<double> UpperRelaxationMethod::compute(const Matrix &matrix,
                                                   const std::vector<double> &b) {
    double det = determinant(matrix);
    if (det == 0){
        throw QString("Определитель матрицы равен нулю!");
    }
    if (omega <=0 || omega >=2){
        throw QString("Омега введена некорректно!");
    }
    double relaxCoeff = omega;
    vector<vector<double>> A = matrix;
    vector<double> B = b;

    pair<vector<vector<double>>, vector<double>> pair;
        vector<double> result(A.size());
        result.assign(result.size(), 0);

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
        int count = 0;

        if (checkForDiagonal(A)) {
            prev_iter.assign(prev_iter.size(), 0);
            for (int i = 0; i < A.size(); i++) {
                prev_iter = cur_iter;
                for (int j = 0; j < A.size(); j++) {
                    if (i == j)
                        cur_iter[i] += prev_iter[j] * (1 - relaxCoeff);
                    else
                        cur_iter[i] += A[i][j] * prev_iter[j] * relaxCoeff;
                }
                cur_iter[i] += B[i] * relaxCoeff;
                prev_iter.assign(prev_iter.size(), 0);
            }
            count++;
            while (stopIter(cur_iter, prev_iter)) {
                prev_iter = cur_iter;
                cur_iter.assign(A.size(), 0);
                for (int i = 0; i < A.size(); i++) {
                    if (i > 0) {
                        prev_iter[i - 1] = cur_iter[i - 1];
                    }
                    for (int j = 0; j < A.size(); j++) {
                        if (i == j)
                            cur_iter[i] += prev_iter[j] * (1 - relaxCoeff);
                        else
                            cur_iter[i] += A[i][j] * prev_iter[j] * relaxCoeff;
                    }
                    cur_iter[i] += B[i] * relaxCoeff;
                }
                count++;
            }
            cout << "Number of Iterations=" << count << endl;
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

//    Matrix A(matrix.size());
//    A = multiplicationMatrix(matrix);
//    vector<double> B = multiplicationMatVec(matrix, b);

//    Matrix D(matrix.size());
//    for(int i = 0; i < D.size(); i++) {
//        D[i].resize(D.size());
//        for (int j = 0; j < D.size(); j++) {
//            if (i == j)
//                D[i][j] = 0;
//            else {
//                if (A[i][i] == 0){
//                    throw QString("Система не имеет единственного решения!");
//                }
//                D[i][j] = (-1) * A[i][j] / A[i][i];
//            }
//        }
//        B[i] /= A[i][i];
//    }
//    vector<double> xNext(matrix.size());
//    vector<double> xPrev(A.size());
//    double  norma = epsilon;
//    copy(B.begin(), B.end(), xNext.begin());
//    int iteration = 0;
//    do{
//        copy(xNext.begin(), xNext.end(), xPrev.begin());
//        fill(xNext.begin(), xNext.end(), 0.0);

//        for (int i =0; i < A.size(); i++){
//            for(int j = 0; j < A.size(); j++){
//                if(j < i)
//                    xNext[i] += omega * D[i][j] * xNext[j];
//                else if (j == i)
//                    xNext[i] += (omega - 1) * D[i][j] * xPrev[j];
//                else
//                    xNext[i] += omega * D[i][j] * xPrev[j];
//            }
//            xNext[i] +=B[i];
//            if (norma < fabs(xNext[i] - xPrev[i]))
//                norma = fabs(xNext[i] - xPrev[i]);
//        }
//        iteration++;
//    } while (norma >= epsilon && iteration < 1000);

//    return xNext;
}

std::vector<double> UpperRelaxationMethod::multiplicationMatVec(const Matrix &matrix, const std::vector<double> &b) {
    std::vector<double> result(b.size());
    Matrix trans = matrix;
    transpose(matrix, trans);
    //cout << endl;
    for(int i = 0; i < matrix.size(); i++){
        result[i] = 0.0;
        for(int j = 0; j < b.size(); j++){
            result[i] += trans[i][j] * b[j];
        }
        //cout << result[i] << " ";
    }
    return  result;
}

Matrix UpperRelaxationMethod::multiplicationMatrix(const Matrix &matrix) {
    Matrix result(matrix.size());
    for(int i = 0; i < matrix.size(); i++) {
        result[i].resize(matrix.size());
        fill(result[i].begin(), result[i].end(), 0.0);
    }
    Matrix trans = matrix;
    transpose(matrix, trans);


    for(int i = 0; i < trans.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            for (int r = 0; r < matrix[i].size(); r++){
                result[i][j] += trans[i][r] * matrix[r][j];
            }
        }
    }
//    for(int i = 0; i < result.size(); i++) {
//        for (int j = 0; j < result.size(); j++)
//            cout << result[i][j] << " ";
//        cout << endl;
//    }
    return result;
}

void UpperRelaxationMethod::transpose(const Matrix &input, Matrix &output) {
    for (int i = 0; i < input.size(); i++){
        for (int j = 0; j < input.size(); j++) {
            output[i][j] = input[j][i];
        }
    }
}
bool UpperRelaxationMethod::stopIter(vector<double> a, vector<double> b){
    vector<double>c = a;
    for (int i = 0; i < a.size(); i++) {
            c[i] -= b[i];
    }
    return !(vectorNorm(c) < epsilon);
}
