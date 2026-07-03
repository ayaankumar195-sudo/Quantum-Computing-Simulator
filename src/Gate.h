#ifndef GATE_H
#define GATE_H

#include <vector>
#include <unsupported/Eigen/KroneckerProduct>
#include "QubitRegister.h"

class Gate {
    protected:
    std::vector<int> targets;

    public:
    Gate ();

    ~Gate () = default;

    virtual void apply (QubitRegister*& QR) = 0;
};

#endif