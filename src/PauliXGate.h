#ifndef PAULIX_H
#define PAULIX_H

#include "Gate.h"
#include "QubitRegister.h"

class PauliXGate : public Gate {
    private:
    //

    public:
    PauliXGate (int index);

    void apply (QubitRegister*& QR) override;
};

#endif