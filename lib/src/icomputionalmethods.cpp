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
