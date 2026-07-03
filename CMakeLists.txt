cmake_minimum_required(VERSION 3.10)

project(Quantum_Computing_Simulator)

find_package(Eigen3 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Quantum_Computing_Simulator
    src/Circuit.cpp
    src/Gate.cpp
    src/PauliXGate.cpp
    src/HadamardGate.cpp
    src/CNOTGate.cpp
    src/GateFactory.cpp
    src/QubitRegister.cpp
    src/main.cpp
)

target_link_libraries(Quantum_Computing_Simulator 
    PRIVATE 
    Eigen3::Eigen
)

target_include_directories(Quantum_Computing_Simulator PRIVATE src)