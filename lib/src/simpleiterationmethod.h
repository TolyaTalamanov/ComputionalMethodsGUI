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

private:
    virtual bool stopIter(vector<double> a, vector<double>b);
private:
    double epsilon = 0.001;

};


#endif //COMPUTATIONALMETHODS_SIMPLEITERATIONMETHOD_H
