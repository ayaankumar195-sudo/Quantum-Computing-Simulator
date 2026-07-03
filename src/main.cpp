#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <bitset>
#include "Circuit.h"

#define RSET "\033[0m"
#define BOLD "\033[1m"
#define CYN  "\033[36m"
#define GRN  "\033[32m"
#define YEL  "\033[33m"
#define MAG  "\033[35m"
#define RED  "\033[31m"
#define BLU  "\033[34m"

void printHeader() {
    std::cout << CYN << BOLD;
    std::cout << " +----------------------------------------------+\n";
    std::cout << " |          QUANTUM COMPUTER SIMULATOR          |\n";
    std::cout << " +----------------------------------------------+\n" << RSET;
}

int main() {
    srand(time(0));
    int QNums;
    bool valid = false;

    printHeader();

    do {
        std::cout << BOLD << " > Number of Qubits (1-5): " << RSET;
        if (!(std::cin >> QNums)) {
            std::cout << RED << " [!] Input Error: Please enter an integer." << RSET << "\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (QNums < 1) {
            std::cout << RED << " [!] Error: Minimum 1 Qubit required." << RSET << "\n";
        } else if (QNums > 5) {
            std::cout << YEL << " [!] Memory Limit: Max 5 Qubits for this simulation." << RSET << "\n";
        } else {
            valid = true;
        }
    } while (!valid);

    std::cout << "\n " << BLU << ">>>" << RSET << " INITIALIZING " << BOLD << QNums << RSET << " QUBITS...\n";
    Circuit QCircuit(QNums);

    int choice = 0;
    do {
        std::cout << "\n" << BOLD << CYN << " COMMAND MENU" << RSET << "\n";
        std::cout << " " << CYN << "1." << RSET << " Display Info     " << CYN << "4." << RSET << " Show Circuit\n";
        std::cout << " " << CYN << "2." << RSET << " Randomize        " << CYN << "5." << RSET << " Execute\n";
        std::cout << " " << CYN << "3." << RSET << " Add Gate         " << CYN << "6." << RSET << " Measure\n";
        std::cout << " " << RED << "0. Shutdown System" << RSET << "\n";
        std::cout << "\n " << BOLD << "User@Quantum:~$ " << RSET;

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 1) {
            int infoID;
            std::cout << "\n " << BOLD << "[1] Probabilities | [2] State Vector: " << RSET;
            std::cin >> infoID;

            if (infoID == 1) {
                int i;
                std::cout << " Target Qubit index: ";
                std::cin >> i;
                QCircuit.displayQubitProb(i);
            } else if (infoID == 2) {
                QCircuit.display();
            }
        } 
        else if (choice == 2) {
            std::cout << MAG << " [!] Randomizing..." << RSET << "\n";
            QCircuit.randomize();
            QCircuit.display();
        } 
        else if (choice == 3) {
            std::cout << "\n" << BOLD << " GATE SELECTION" << RSET << "\n";
            std::cout << " [H] Hadamard " << YEL << "|" << RSET << " [X] Pauli-X " << YEL << "|" << RSET << " [C] C-NOT\n Choice: ";
            char gType;
            std::cin >> gType;
            
            if (gType == 'H' || gType == 'h') {
                int idx; 
                std::cout << " Qubit index: "; 
                std::cin >> idx;
                QCircuit.addGate('H', idx);
                std::cout << "\n" << GRN << "[H] Hadamard Gate applied to " << idx << "th Qubit in circuit." << RSET << "\n";
            } else if (gType == 'X' || gType == 'x') {
                int idx; 
                std::cout << " Qubit index: "; 
                std::cin >> idx;
                QCircuit.addGate('X', idx);
                std::cout << "\n" << MAG << "[H] Hadamard Gate applied to " << idx << "th Qubit in circuit." << RSET << "\n";
            } else if (gType == 'C' || gType == 'c') {
                int ctrl, targ;
                std::cout << " Control: "; 
                std::cin >> ctrl;
                std::cout << " Target:  "; 
                std::cin >> targ;
                QCircuit.addGate('C', ctrl, targ);
                std::cout << "\n" << BLU << "[C] C-NOT Gate applied to [" << ctrl << "]---o--->[" << targ << "] in the circuit." << RSET << "\n";
            }
        } 
        else if (choice == 4) {
            std::vector<std::string> gates = QCircuit.getGatesInfo();
            std::cout << "\n" << BOLD << " [ CIRCUIT SEQUENCE ]" << RSET << "\n";
            if (gates.empty()) std::cout << "  (Empty)\n";
            for(size_t i=0; i<gates.size(); ++i) 
                std::cout << "  Step " << i << ": " << GRN << gates[i] << RSET << "\n";
        } 
        else if (choice == 5) {
            std::cout << MAG << " [!] Executing Quantum Gates..." << RSET << "\n";
            QCircuit.execute();
            std::cout << "\nState Vector after execution:\n";
            QCircuit.display();
        } 
        else if (choice == 6) {
            std::cout << RED << " [!] Collapsing Wavefunction (Measuring)..." << RSET << "\n";
            QCircuit.measure();
            QCircuit.display();
        }

    } while (choice != 0);

    std::cout << BOLD << RED << "\n [ SYSTEM TERMINATED ]\n" << RSET;
    return 0;
}