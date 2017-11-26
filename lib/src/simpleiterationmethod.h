#ifndef COMPUTATIONALMETHODS_SIMPLEITERATIONMETHOD_H
#define COMPUTATIONALMETHODS_SIMPLEITERATIONMETHOD_H
#include <cmath>
#include "lib/include/icomputionalmethods.h"
using std::vector;
using std::pair;

#define EPS 0.001

class SimpleIterationMethod : public IComputionalMethod {
public:
    std::vector<double> compute(const Matrix &matrix,
                                const std::vector<double> &b) override;
    virtual void setEpsilon(double eps) override{
        epsilon = eps;
    }
    bool checkForDiagonal(vector<vector<double>> A) {
            double norm = 0;
            for (int i = 0; i < A.size(); i++) {
                for (int j = 0; j < A[0].size(); j++) {
                    norm += A[i][j] * A[i][j];
                }
            }
            if (sqrt(norm) < 1)
                return true;
            else
                return false;
        }

        pair<vector<vector<double>>, vector<double>> makeDiagonal(vector<vector<double>> A, vector<double> B) {
            //çàáèòü è ñäåëàòü â èòåðàöèÿõ?
            double d;
            pair<vector<vector<double>>, vector<double>> result;
            for (int k = 0; k < A.size(); k++) {
                for (int j = k + 1; j < A[0].size(); j++) {
                    d = A[j][k] / A[k][k];
                    for (int i = k; i < A.size(); i++) {
                        A[j][i] = A[j][i] - d * A[k][i];
                    }
                    B[j] = B[j] - d*B[k];
                }
            }
            for (int k = A.size() - 1; k >= 0; k--) { // need >=    ?
                for (int j = k - 1; j >= 0; j--) {
                    d = A[j][k] / A[k][k];
                    for (int i = k; i >= 0; i--) {
                        A[j][i] = A[j][i] - d*A[k][i];
                    }
                    B[j] = B[j] - d*B[k];
                }
            }
            result.first = A;
            result.second = B;
            return result;
        }

        bool stopIter(vector<double> a, vector<double>b) {
            vector<double>c = a;
            for (int i = 0; i < a.size(); i++) {
                c[i] -= b[i];
            }
            if (vectorNorm(c) < EPS) {
                return false;
            }
            else {
                return true;
            }
    }
    double vectorNorm(vector<double> a) {
                double norm = 0;
                for (int i = 0; i < a.size(); i++) {
                    double tmp = abs(a[i]);
                    if (norm < tmp) {
                        norm = tmp;
                    }
                }
                return norm;
        }
private:
    double epsilon;

};


#endif //COMPUTATIONALMETHODS_SIMPLEITERATIONMETHOD_H
