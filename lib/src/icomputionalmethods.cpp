#include "lib/include/icomputionalmethods.h"
#include "gaussmethod.h"
#include "seidelmethod.h"
#include "upperrelaxationmethod.h"
#include "simpleiterationmethod.h"
#include "kramermethod.h"

std::unique_ptr<IComputionalMethod> IComputionalMethod::create(Implementation impl) {
    switch(impl){
        case Implementation::GAUSS :
            return std::unique_ptr<IComputionalMethod>(new GaussMethod());

        case Implementation::KRAMMER :
            return std::unique_ptr<IComputionalMethod>(new KramerMethod());

        case Implementation::SEIDEL :
            return std::unique_ptr<IComputionalMethod>(new SeidelMethod());

        case Implementation::SIMPLE_ITERATION :
            return std::unique_ptr<IComputionalMethod>(new SimpleIterationMethod());

       case Implementation::UPPER_RELAXATION :
            return std::unique_ptr<IComputionalMethod>(new UpperRelaxationMethod());

        default :
            return nullptr;

    }
}
double IComputionalMethod::determinant(const Matrix &matrix){
    Matrix A = matrix;
    double result = 0;
    double d = 0;
    std::vector<double> vect = A[0];
    for (int k = 0; k < vect.size(); k++) {
        for (int j = k + 1; j < vect.size(); j++) {
            if (A[k][k] == 0){
                return result;
            }
            d = A[j][k] / A[k][k];
            for (int i = k; i < A.size(); i++) {
                A[j][i] = A[j][i] - d * A[k][i];
            }
        }
    }
    result = 1;
    for (int i = 0; i < A.size(); i++) {
        result *= A[i][i];
    }
    return result;
}
double IComputionalMethod::vectorNorm(const vector<double> &a){
    double norm = 0;
    for (int i = 0; i < a.size(); i++) {
            double tmp = abs(a[i]);
            if (norm < tmp) {
                    norm = tmp;
            }
    }
    return norm;
}
Matrix IComputionalMethod::createSpecialMatrix(const Matrix &matrix, const vector<double>& b, int pos){
    Matrix A = matrix;
        for (int i = 0; i < b.size(); i++) {
            A[i][pos] = b[i];
        }
    return A;
}
bool   IComputionalMethod::checkForDiagonal(const Matrix &A){
    double norm = 0;
    for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < A[0].size(); j++) {
                    norm += A[i][j] * A[i][j];
            }
    }
    return (sqrt(norm) < 1);
}
pair<Matrix, vector<double> >IComputionalMethod::makeDiagonal(Matrix A, vector<double> B){
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
    result.first  = A;
    result.second = B;
    return result;
}
