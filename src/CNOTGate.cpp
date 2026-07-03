#include <unsupported/Eigen/KroneckerProduct>
#include "QubitRegister.h"
#include "Gate.h"
#include "CNOTGate.h"

CNOTGate::CNOTGate (int control, int target, int numQ) {
    this->targets.push_back(control);
    this->targets.push_back(target);

    this->initKroneckerProduct(numQ);
}

void CNOTGate::initKroneckerProduct (int numQ) {
    Eigen::Matrix2cd P0;
    Eigen::Matrix2cd P1;
    Eigen::Matrix2cd X;
    Eigen::Matrix2cd I = Eigen::Matrix2cd::Identity();

    std::complex<double> unit = 1.0;
    std::complex<double> zero = 0.0;

    P0 << unit , zero , zero , zero;
    P1 << zero , zero , zero , unit;
    X << zero , unit , unit , zero;

    Eigen::MatrixXcd comp0 = (this->targets[0] == 0) ? P0 : I;
    for (int i = 1; i < numQ; i++) {
        if (i == this->targets[0]) {
            comp0 = kroneckerProduct(P0, comp0).eval();
        } else {
            comp0 = kroneckerProduct(I, comp0).eval();
        }
    }

    Eigen::MatrixXcd comp1 = (this->targets[0] == 0) ? P1 : ((this->targets[1] == 0) ? X : I);
    for (int i = 1; i < numQ; i++) {
        if (i == this->targets[0]) {
            comp1 = kroneckerProduct(P1, comp1).eval();
        } else if (i == this->targets[1]) {
            comp1 = kroneckerProduct(X, comp1).eval();
        } else {
            comp1 = kroneckerProduct(I, comp1).eval();
        }
    }

    this->kronProd = comp0 + comp1;
}

void CNOTGate::apply (QubitRegister*& QR) {
    StateVector state = QR->getState();
    QR->getState() = this->kronProd * state;

    QR->normalize();
}