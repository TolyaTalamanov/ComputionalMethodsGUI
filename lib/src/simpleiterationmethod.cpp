
#include <numeric>
#include <algorithm>
#include <iostream>
#include "lib/include/icomputionalmethods.h"
#include "simpleiterationmethod.h"
#include "QString"

using namespace std;
std::vector<double> SimpleIterationMethod::compute(const Matrix &matrix,
                                                   const std::vector<double> &b) {
    vector<int> max_pos(matrix.size());
    int sum = 0;
    for(int i = 0; i < matrix.size(); i++) {
        auto max_it = std::max_element(matrix[i].begin(), matrix[i].end(), [](int a, int b){
            return (std::abs(a) < std::abs(b));
        });
        max_pos[i] = std::distance(matrix[i].begin(), max_it);
        if (*max_it == 0) {
            if (b[*max_it] == 0)
                throw QString("Система имеет бесконечно много решений");
            else
                throw QString("Система не имеет решений");

            exit(-1);
        }
    }
    sum = accumulate(max_pos.begin(), max_pos.end(), 0);

    if(sum != matrix.size() * (matrix.size() - 1) / 2){
       throw QString("Решение не сходится!");

        exit(-1);
    }
    Matrix  A = matrix;
    vector<double> B = b;
    for(int i = 0; i < matrix.size(); i++) {
        copy(matrix[i].begin(), matrix[i].end(), A[max_pos[i]].begin());
        B[max_pos[i]] = b[i];
    }

    Matrix D(matrix.size());
    for(int i = 0; i < D.size(); i++) {
        D[i].resize(D.size());
        for (int j = 0; j < D.size(); j++) {
            if (i == j)
                 D[i][j] = 0;
            else {
               D[i][j] = (-1) * A[i][j] / A[i][i];
            }
        }
        B[i] /= A[i][i];
    }
    for(int i = 0; i < D.size(); i++) {
        for (int j = 0; j < D.size(); j++)
            cout << D[i][j] << " ";
        cout << endl;
    }
    for(int i = 0; i < matrix.size(); i++) {
        cout << B[i] << " ";
    }
    cout << endl;
    double sumRow ;
    double  maxSum = 0;
    for(int i = 0; i < D.size(); i++) {
        sumRow = 0;
        for (int j = 0; j < D.size(); j++) {
            sumRow += std::abs(D[i][j]);
        }
        if (sumRow > maxSum)
            maxSum = sumRow;
    }
    if (maxSum >= 1){
        throw QString("Решение не сходится!!");

        exit(-1);
    }
    vector<double> xNext(matrix.size());
    vector<double> xPrev(A.size());
    double  norma = epsilon;
    copy(B.begin(), B.end(), xNext.begin());
    int iteration = 0;
    do{
        copy(xNext.begin(), xNext.end(), xPrev.begin());
        fill(xNext.begin(), xNext.end(), 0.0);

        for (int i = 0; i < A.size(); i++){
            for(int j = 0; j < A.size(); j++){
                xNext[i] += D[i][j] * xPrev[j];
            }
            xNext[i] += B[i];
            if (norma < fabs(xNext[i] - xPrev[i]))
                norma = fabs(xNext[i] - xPrev[i]);
        }
        iteration++;
    } while (norma >= epsilon && iteration < 1000);

    return xNext;
}

