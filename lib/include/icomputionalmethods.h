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
protected:
    virtual double determinant(const Matrix& matrix);
    virtual double vectorNorm( const vector<double>& a);
    virtual Matrix createSpecialMatrix(const Matrix& matrix, const vector<double>& b, int pos);
    virtual bool   checkForDiagonal(const Matrix& A);
    virtual pair<Matrix, vector<double>> makeDiagonal(Matrix A, vector<double> B);
};

#endif //COMPUTATIONALMETHODS_COMPUTIONALMETHODS_H
