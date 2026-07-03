#include <cmath>
#include <Eigen/Dense>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <bitset>
#include "QubitRegister.h"

#define YEL  "\033[33m"
#define RSET "\033[0m"

typedef std::complex<double> Complex;
typedef Eigen::VectorXcd StateVector;

QubitRegister::QubitRegister () : numOfQubits(1) {
    state = StateVector::Zero(2);
    state(0) = 1.0;
}

QubitRegister::QubitRegister (int size) : numOfQubits(size) {
    state = StateVector::Zero(1 << size);
    state(0) = 1.0;
}

void QubitRegister::randomize(){
    double random;
    for (int i = 0; i < (1 << numOfQubits); i++){
        random = rand() % 100;
        random /= 99;
        state(i) = random;
    }

    normalize();
}

void QubitRegister::normalize(){
    double sum = 0;

    for (int i = 0; i < (1 << numOfQubits); i++){
        sum += std::norm(state(i));
    }

    sum = std::sqrt(sum);

    for (int i = 0; i < (1 << numOfQubits); i++){
        state(i) = (sum != 0.0) ? (state(i) / sum) : 0.0;
    }
}


double QubitRegister::probabilityOf(int n, bool target) const {
    if (n < 0 || n >= numOfQubits)
        throw std::invalid_argument("Invalid qubit index");

    double prob = 0.0;
    int indent = (target)? 0 : (1 << n);

    for (int i = 0; i < (1 << numOfQubits); i++) {
        if (((i - indent) >> n) & 1) {
            prob += std::norm(state(i));
        }
    }

    return prob;
}

void QubitRegister::measure(int n) {
    if (n < 0 || n >= numOfQubits) 
        throw std::invalid_argument("Invalid qubit index");

    double prob = probabilityOf(n, true);

    double random = (rand() % 100) / 100.0;
    int indent = (random < prob)? (1 << n) : 0;

    for (int i = 0; i < (1 << numOfQubits); i++) {
        if (((i - indent) >> n) & 1) {
            state(i) = 0.0;
        }
    }

    normalize();
}

StateVector& QubitRegister::getState() {
    return this->state;
}

int QubitRegister::getNumOfQubits () const { return this->numOfQubits; }

std::ostream& operator<<(std::ostream& out, const QubitRegister& other) {
    for (int i = 0; i < (1 << other.numOfQubits); i++){
        std::string binary = std::bitset<5>(i).to_string().substr(5 - other.numOfQubits);
        out << YEL << " |" << binary << ">" << RSET << " Prob: " << std::norm(other.state(i)) << "\n";
    }

    double prob, notProb;

    for (int i = 0; i < other.numOfQubits; i++) {
        prob = other.probabilityOf(i, true);
        notProb = other.probabilityOf(i, false);

        out << "Qubit index: " << i << "\tTrue: " << prob << "\tFalse: " << notProb << "\n";
    }

    return out;
}