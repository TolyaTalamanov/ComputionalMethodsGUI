#include "lib/include/icomputionalmethods.h"
#ifndef COMPUTATIONALMETHODS_GAUSSMETHOD_H
#define COMPUTATIONALMETHODS_GAUSSMETHOD_H

class GaussMethod : public IComputionalMethod {
public:
    std::vector<double> compute(const Matrix& matrix,
                                const std::vector<double>& b) override;
private:
    int getMaxRow(const Matrix& matrix, int row);
};

#endif //COMPUTATIONALMETHODS_GAUSSMETHOD_H
