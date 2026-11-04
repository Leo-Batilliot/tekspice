# NanoTekSpice

## Introduction
Hello and welcome to the **NanoTekSpice** project.
This project was developed by **Gabin Wilson** and **Léo Batilliot** as part of our second year at Epitech.

NanoTekSpice is a **logic circuit simulator** developed in **C++**.

## Download & Dependencies
To clone the repository:

```bash
git clone https://github.com/EpitechPGE2-2025/G-OOP-400-LIL-4-1-tekspice-11.git
cd G-OOP-400-LIL-4-1-tekspice-11/
```

You must have the following dependencies installed:
- cmake
- g++
- make
- git

To install them:
- FEDORA : ```sudo dnf install gcc-c++ cmake make git```
- Ubuntu / Debian : ```sudo apt install g++ cmake make git```
- Arch : ```sudo pacman -S gcc cmake make git```

## Compilation
Now you can compile the project by using these new commands:

```bash
cmake -S . -B build
cmake --build build
```

The executable will be generated in the build directory.

## Tests
We have set up a list of unit tests.
To run these tests, use the following commands:

```bash
cd tests/
cmake --build build
ctest --test-dir build -V
```

## HOW IT WORKS
NanoTekSpice simulates **digital logic circuits** described in configuration files with the **.nts** extension.

These files describe:
- the __components__ used in the circuit
- the __connections__ between these components

The program reads the file, creates the corresponding components, links them together and then simulates the circuit.

Example of a .nts file:
```bash
.chipsets:
input a
input b
and gate
output out

.links:
a:1 gate:1
b:1 gate:2
gate:3 out:1
```

### START OF SIMULATION
To start the simulation you must use these command:
```bash
./build/nanotekspice [.nts]
```

__**Interactive Mode**__:
To start the simulation, use the following command:
- simulate = run one simulation tick
- display = display the current state of input / output / clock
- loop = run the simulation continuously (display, simulate, display, simulate ...)
- exit = quit the program
- input=value = change value of an input (example: a=0)

By default inputs and outputs are initialized at Undefined.

**List of Components**:
Here is the list of components:

#### Special Components
- input: a component with a single pin directly linked to the command line. Its value is initialized to Undefined
- output: a component with a single pin used as the output of a circuit.
- true: a component with a single pin that is always true.
- false: a component with a single pin that is always false.
- clock: a component that works like an input, except its value is inverted after each simulation.

#### Elementary Components
- and: single AND gate.
- or: single OR gate.
- xor: single XOR gate.
- not: single INVERTER gate

#### Gates Components
- 4001: Four NOR gates.
- 4011: Four NAND gates.
- 4030: Four XOR gates.
- 4069: Six INVERTER gates.
- 4071: Four OR gates.
- 4081: Four AND gates.

#### Advanced Components
- 4008: 4 bits adder.
- 4013: Dual Flip Flop.
- 4017: 10 bits Johnson decade.
- 4040: 12 bits counter.
- 4094: 8 bits shift register.
- 4512: 8 channel data selector.
- 4514: 4 bits decoder.
- 4801: Random access memory.
- 2716: Read only memory (memory initialized from ./rom.bin).

## FOR DEVELOPERS

If you want to add new **components** or learn how the project works internally,
you can read the documentation located in:
```bash
docs/README.md
```
## Bonus - Visual Circuit Simulator

In addition to the command-line simulator, we have developed a **graphical interface** called **NanoBonus** that allows you to build and visualize circuits interactively.

### Features
- **Visual circuit editor** with drag-and-drop components
- **Interactive simulation** in real-time
- **Customizable UI** through [Config.hpp](bonus/src/Config.hpp)
- **Full keyboard and mouse support**

### Quick Start
```bash
cd bonus/
cmake -S . -B build
cmake --build build

./build/NanoBonus
```

📖 **Full documentation**: [bonus/README.md](bonus/README.md)

---

**Thank you for reading.**
