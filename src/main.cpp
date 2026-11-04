#include <iostream>
#include "ErrorHandling.hpp"
#include "Factory.hpp"
#include "Parsing.hpp"
#include "Sim.hpp"

int main(int ac, char **av)
{
    try {
        if (ac != 2)
            throw NanoException("Usage: ./nanotekspice <file>.nts");

        // Set Path for Parsing
        std::string path = av[1];

        // Init factory;
        nts::Factory factory;

        // Init and Run parsing
        nts::Parsing parsing(path);
        auto &components = parsing.run();
    
        if (components.empty()) {
            throw NanoException("No components found in the .nts file");
        }
        // Simulation
        nts::Sim sim(components);

        // Run simulation
        sim.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}