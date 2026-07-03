#include <unsupported/Eigen/KroneckerProduct>
#include "QubitRegister.h"
#include "Gate.h"
#include "HadamardGate.h"

HadamardGate::HadamardGate (int index, int numQ) {
    this->targets.push_back(index);
    this->initKroneckerProduct(numQ);
}

void HadamardGate::initKroneckerProduct (int numQ) {
    Eigen::Matrix2cd H;

    std::complex<double> s = 1.0 / std::sqrt(2.0);

    H << s , s , s , -s;

    Eigen::Matrix2cd I = Eigen::Matrix2cd::Identity();

    this->kronProd = (this->targets[0] == 0) ? H : I;

    for (int i = 1; i < numQ; i++) {
        if (i == this->targets[0]) {
            this->kronProd = kroneckerProduct(H, this->kronProd).eval();
        } else {
            this->kronProd = kroneckerProduct(I, this->kronProd).eval();
        }
    }
}

void HadamardGate::apply (QubitRegister*& QR) {
    StateVector state = QR->getState();
    QR->getState() = this->kronProd * state;

    QR->normalize();
}