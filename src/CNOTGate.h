#ifndef CNOTGATE_H
#define CNOTGATE_H

#include <unsupported/Eigen/KroneckerProduct>
#include "QubitRegister.h"
#include "Gate.h"

class CNOTGate : public Gate {
    private:
    Eigen::MatrixXcd kronProd;

    void initKroneckerProduct (int numQ);

    public:
    CNOTGate (int control, int target, int numQ);

    void apply (QubitRegister*& QR) override;
};

#endif