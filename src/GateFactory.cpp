#include <vector>
#include <stdexcept>
#include <functional>
#include "GateFactory.h"

GateFactory::GateFactory (int numQ) : numOfQubits(numQ)  {}

GateFactory::~GateFactory () {
    for (int i = 0; i < this->gate_operations.size(); i++) {
        delete this->gate_operations[i];

        this->gate_operations[i] = nullptr;
    }
}

void GateFactory::addGate (char type, int index) {
    Gate* n_gate = nullptr;

    if (type == 'X' || type == 'x') {
        n_gate = new PauliXGate(index);
        this->gates_info.push_back("PauliX -> " + std::to_string(index));
    } else if (type == 'H' || type == 'h') {
        n_gate = new HadamardGate(index, this->numOfQubits);
        this->gates_info.push_back("Hadamard -> " + std::to_string(index));
    } else if (type == 'C' || type == 'c') {
        throw std::invalid_argument("CNOT Gate is a 2-qubit Gate, can not create with a single qubit");
    } else {
        throw std::invalid_argument("Can not identify such single-qubit Gate");
    }

    this->gate_operations.push_back(n_gate);

    this->numOfGates = this->gate_operations.size();
}

void GateFactory::addGate (char type, int control, int target) {
    Gate* n_gate = nullptr;

    if (type == 'C' || type == 'c') {
        n_gate = new CNOTGate(control, target, this->numOfQubits);
        this->gates_info.push_back("CNOT -> " + std::to_string(control) + " | " + std::to_string(target));
    } else {
        throw std::invalid_argument("Can not identify such 2-qubit Gate");
    }

    this->gate_operations.push_back(n_gate);

    this->numOfGates = this->gate_operations.size();
}

void GateFactory::execute (QubitRegister*& QR, int gate_index) const {
    this->gate_operations[gate_index]->apply(QR);
}

int GateFactory::getNumOfGates () const { return this->numOfGates; }

std::vector<std::string> GateFactory::getGatesInfo () const {
    return this->gates_info;
}

// std::ostream& operator<< (std::ostream& out, const GateFactory& other) {
//     for (int i = 0; i < other.gate_operations.size(); i++) {
//         //
//     }

//     return out;
// }