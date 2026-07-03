#include "QubitRegister.h"
#include "Gate.h"
#include "PauliXGate.h"

PauliXGate::PauliXGate (int index) {
    this->targets.push_back(index);
}

void PauliXGate::apply (QubitRegister*& QR) {
    StateVector state = QR->getState();

    for (int i = 0; i < state.size(); i++) {
        if (!(i & (1 << this->targets[0]))) {
            int j = i | (1 << this->targets[0]);

            std::complex<double> temp = state[i];
            state[i] = state[j];
            state[j] = temp;
        }
    }

    QR->getState() = state;
    QR->normalize();
}