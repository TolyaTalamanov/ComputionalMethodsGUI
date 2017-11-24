#ifndef COMPUTATIONALMETHODS_COMPUTIONALMETHODS_H
#define COMPUTATIONALMETHODS_COMPUTIONALMETHODS_H

#include <vector>
#include <memory>

enum class Implementation{
    GAUSS,
    KRAMMER,
    SEIDEL,
    SIMPLE_ITERATION,
    UPPER_RELAXATION
};

using Matrix = std::vector<std::vector<double>>;
class  IComputionalMethod{
public:
    virtual std::vector<double> compute(const Matrix& matrix,
                                        const std::vector<double>& b) = 0;

    static std::unique_ptr<IComputionalMethod> create(Implementation impl);
    virtual void setOmega(double omega){

    }
    virtual void setEpsilon(double eps){

    }

};

#endif //COMPUTATIONALMETHODS_COMPUTIONALMETHODS_H
