#ifndef COMPUTATIONALMETHODS_SEIDELMETHOD_H
#define COMPUTATIONALMETHODS_SEIDELMETHOD_H

#include "lib/include/icomputionalmethods.h"

class SeidelMethod : public IComputionalMethod {
public:
    std::vector<double> compute(const Matrix &matrix,
                                const std::vector<double> &b) override;
    virtual void setEpsilon(double eps) override{
        epsilon = eps;
    }

private:
    void transpose(const Matrix &input, Matrix &output);
    Matrix multiplicationMatrix(const Matrix &matrix);
    std::vector<double> multiplicationMatVec(const Matrix &matrix,  const std::vector<double> &b);
private:
    double epsilon;
};

#endif //COMPUTATIONALMETHODS_SEIDELMETHOD_H
