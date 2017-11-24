#ifndef COMPUTATIONALMETHODS_UPPERRELAXATIONMETHOD_H
#define COMPUTATIONALMETHODS_UPPERRELAXATIONMETHOD_H

#include "lib/include/icomputionalmethods.h"

class UpperRelaxationMethod : public IComputionalMethod {
public:
    std::vector<double> compute(const Matrix &matrix, const std::vector<double> &b) override;
    virtual void setOmega(double omg) override{
        omega = omg;
    }
    virtual void setEpsilon(double eps){
        epsilon = eps;
    }

private:
    void transpose(const Matrix &input, Matrix &output);
    Matrix multiplicationMatrix(const Matrix &matrix);
    std::vector<double> multiplicationMatVec(const Matrix &matrix,  const std::vector<double> &b);
private:
    double epsilon;
    double omega;
};

#endif //COMPUTATIONALMETHODS_UPPERRELAXATIONMETHOD_H
