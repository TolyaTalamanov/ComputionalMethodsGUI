#ifndef COMPUTATIONALMETHODS_SIMPLEITERATIONMETHOD_H
#define COMPUTATIONALMETHODS_SIMPLEITERATIONMETHOD_H

#include "lib/include/icomputionalmethods.h"

class SimpleIterationMethod : public IComputionalMethod {
public:
    std::vector<double> compute(const Matrix &matrix,
                                const std::vector<double> &b) override;
    virtual void setEpsilon(double eps) override{
        epsilon = eps;
    }
private:
    double epsilon;

};


#endif //COMPUTATIONALMETHODS_SIMPLEITERATIONMETHOD_H
