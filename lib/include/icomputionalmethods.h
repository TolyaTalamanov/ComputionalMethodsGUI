#ifndef COMPUTATIONALMETHODS_COMPUTIONALMETHODS_H
#define COMPUTATIONALMETHODS_COMPUTIONALMETHODS_H

#include <vector>
#include <memory>
#include <cmath>
#define EPS 0.001
enum class Implementation{
    GAUSS,
    KRAMMER,
    SEIDEL,
    SIMPLE_ITERATION,
    UPPER_RELAXATION
};

using Matrix = std::vector<std::vector<double>>;
using std::vector;
using std::pair;
class  IComputionalMethod{
public:
    virtual std::vector<double> compute(const Matrix& matrix,
                                        const std::vector<double>& b) = 0;

    static std::unique_ptr<IComputionalMethod> create(Implementation impl);
    virtual void setOmega(double omega){

    }
    virtual void setEpsilon(double eps){

    }
    virtual double determinant(vector<vector<double>>A) {
                    double result = 1;
                    double d = 0;
                    vector<double> vect = A[0];
                    for (int k = 0; k < vect.size(); k++) { // ïðÿìîé õîä
                            for (int j = k + 1; j < vect.size(); j++) {
                                    d = A[j][k] / A[k][k]; // ôîðìóëà (1)
                                    for (int i = k; i < A.size(); i++) {
                                            A[j][i] = A[j][i] - d * A[k][i]; // ôîðìóëà (2)
                                    }
                            }
                    }
                    for (int i = 0; i < A.size(); i++) {
                            double tmp = A[i][i];
                            result *= tmp;
                    }
                    return result;
            }

            virtual double vectorNorm(vector<double> a) {
                    double norm = 0;
                    for (int i = 0; i < a.size(); i++) {
                            double tmp = abs(a[i]);
                            if (norm < tmp) {
                                    norm = tmp;
                            }
                    }
                    return norm;
            }

            vector<vector<double>> createSpecialMatrix(vector<vector<double>> A, vector<double> B, int pos) {
                    for (int i = 0; i < B.size(); i++) {
                            A[i][pos] = B[i];
                    }
                    return A;
            }

            virtual bool checkForDiagonal(vector<vector<double>> A) { //âîçìîæíà õóåòà
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

            virtual pair<vector<vector<double>>, vector<double>> makeDiagonal(vector<vector<double>> A, vector<double> B) {
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

            virtual bool stopIter(vector<double> a, vector<double>b) {
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



};

#endif //COMPUTATIONALMETHODS_COMPUTIONALMETHODS_H
