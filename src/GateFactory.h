#ifndef GATE_FACTORY_H
#define GATE_FACTORY_H

#include <vector>
#include <functional>
#include "QubitRegister.h"
#include "Gate.h"
#include "PauliXGate.h"
#include "HadamardGate.h"
#include "CNOTGate.h"

class GateFactory {
    private:
    std::vector<Gate*> gate_operations;
    std::vector<std::string> gates_info;
    int numOfQubits;
    int numOfGates;

    public:
    GateFactory (int numQ);
    ~GateFactory ();

    void addGate (char type, int index);
    void addGate (char type, int control, int target);

    void execute (QubitRegister*& QR, int gate_index) const;

    int getNumOfGates () const;

    std::vector<std::string> getGatesInfo () const;

    // friend std::ostream& operator<< (std::ostream& out, const GateFactory& other);
};

#endif