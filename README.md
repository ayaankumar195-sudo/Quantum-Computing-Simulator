# Qubit-Simulator

## Plan
We have designed an **MVP** (Minimal Viable Product) for a Quantum Computer Simulation.
This project simulates a multi-qubit system of 5 Qubits on consumer-grade Laptops.
However, this number can be extended considering the limitation of memory.


## Progress

### Classes / Structure

* [x] `QubitRegister`: Manages a Qubit-Register, and stores the state vector for that Qubit. 
* [x] `Gate`: An abstract class for gates, it must have a pure virtual function for `apply()`.
  * [x] `HadamardGate`
  * [x] `CNOTGate`
  * [x] `PauliXGate` 
* [X] `GateFactory`: It stores and manages all objects of `Gate`
* [X] `Circuit`: a class to manage a `GateFactory` and (maybe multiple) `QubitRegister` objects. Needed to sequentially execute the `QubitRegister` on the list of `Gate`.

### Algorithms

* [x] **Superposition**: Apply `HadamardGate` to a zero-state. 
* [x] **Entanglement**: Apply `HadamardGate` to a qubit, then `CNOTGate` to observe its effects.
* [x] **Measurement**: Implement a function that collapses the state based on probabilities.

## How to use

* Clone this repository: ``` git clone https://github.com/ayaankumar195-sudo/Quantum-Computing-Simulator ``` 
* Navigate to the Project directory: ``` cd Quantum-Computing-Simulator ```
* Create a build directory: ``` mkdir build && cd build ```
* Generate the build system: ``` cmake .. ```
* Compile the code: ``` cmake --build . ```
* Run the executable,
  # For Linux/macOS

  ./Quantum_Computing_Simulator
  
  # For Windows

  .\Quantum_Computing_Simulator.exe

## Contribution & Team

This project was developed as a collaborative coursework assignment at the **School Of Mathematics and Computer Science, IBA Karachi**.

## Development Team

* **Ayaan Kumar** ([@ayaankumar195-sudo](https://github.com/ayaankumar195-sudo)) — Core Quantum State Vector Representation & Optimization 
  * Designed the fundamental mathematical representation of quantum registers (`QubitRegister`) using Eigen3 dense vector structures.
  * Implemented state vector normalization and random state preparation algorithms.
  * Designed a highly optimized, bitwise state-swapping approach for the single-qubit `PauliXGate` to maximize execution efficiency.

* **Muhammad Ishaque** ([@IshaqJunejo](https://github.com/IshaqJunejo)) — Kronecker Product Engine & Circuit Flow Architecture
  * Developed the multi-qubit operator construction engine using Kronecker tensor products for both `HadamardGate` and the 2-qubit `CNOTGate`.
  * Designed the core orchestration pipeline in the `Circuit` class to sequence and pipeline gate execution.
  * Implemented the structural factory design pattern in `GateFactory` to safely manage runtime allocation and garbage collection of quantum gates.

* **Muhaimin Mairaj** ([@Muhaimin-Mairaj](https://github.com/Muhaimin-Mairaj)) — Measurement Mechanics & Interactive Console Client
  * Programmed the wavefunction collapse logic (`QubitRegister::measure`) and partial probability calculator (`probabilityOf`) based on quantum measurement theory.
  * Developed the main command-line interface (CLI) execution loop in `main.cpp`, featuring input validation, user system navigation, and color-coded state vector logging.
  * Established helper utilities for visualizing target qubit probabilities and circuit sequences during runtime execution.

Note on Contribution History: This simulator was a collaborative team effort. Because the codebase was primarily built and tested on a shared workstation, the original commits were pushed under a co-developer's account. This repository is hosted here to showcase the completed project in my personal portfolio.

## License

This project is licensed as **MIT LICENSE**, see [LICENSE](./LICENSE) for more info.