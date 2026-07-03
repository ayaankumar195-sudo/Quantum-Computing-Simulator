#ifndef QUBIT_REGISTER_H
#define QUBIT_REGISTER_H

#include <Eigen/Dense>
// #include "Gate.h"

typedef std::complex<double> Complex;
typedef Eigen::VectorXcd StateVector;

class QubitRegister {
    private:
    int numOfQubits;
    StateVector state;

    public:
    QubitRegister();
    QubitRegister(int size);
    void randomize();
    double probabilityOf(int n, bool target) const;
    void measure(int n);
    void normalize();
    StateVector& getState ();
    int getNumOfQubits () const;
    friend std::ostream & operator<<(std::ostream & out, const QubitRegister & other);
};

#endif