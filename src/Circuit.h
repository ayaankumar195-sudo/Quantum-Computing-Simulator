#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "QubitRegister.h"
#include "Gate.h"
#include "PauliXGate.h"
#include "HadamardGate.h"
#include "CNOTGate.h"
#include "GateFactory.h"

class Circuit {
    private:
    GateFactory* factory;
    QubitRegister* QRegister;
    int numOfQubits;
    bool isExecuted;
    bool isMeasured;

    public:
    Circuit (int numQ);

    ~Circuit ();

    void addGate (char type, int index);
    void addGate (char type, int control, int target);

    void execute ();

    void measure ();

    void randomize ();
    
    void display () const;

    void displayQubitProb (int i) const;

    std::vector<std::string> getGatesInfo () const;

    const StateVector& getStateVector () const;
};

#endif