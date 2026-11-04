#include "Sim.hpp"
#include "Clock.hpp"
#include "IComponent.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include "Input.hpp"
#include "OutPut.hpp"
#include <vector>
#include <csignal>

// global counter used to avoid infinite recursive computes
std::size_t nts::gEvalId = 0;


nts::Tristate nts::Sim::convertToTristate(std::string name)
{
    if (name == "0")
        return nts::Tristate::False;
    if (name == "1")
        return nts::Tristate::True;
    if (name == "U")
        return nts::Tristate::Undefined;

    std::cerr << "The value of " << name << " must be : 1, 0 or U" << std::endl;
    return nts::Tristate::Undefined;
}

void nts::Sim::displayCmd()
{
    gEvalId++;
    std::cout << "tick: " << _tick << std::endl;
    std::cout << "input(s):" << std::endl;

    // Set vector for sort
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;

    // add value in vector for sort
    for (const auto& [name, comp] : _components) {
        if (dynamic_cast<nts::Input *>(comp.get()) || dynamic_cast<nts::Clock *>(comp.get()))
            inputs.push_back(name);
        else if (dynamic_cast<nts::OutPut *>(comp.get()))
            outputs.push_back(name);
    }

    // Sort inputs and outputs
    std::sort(inputs.begin(), inputs.end());
    std::sort(outputs.begin(), outputs.end());

    // Display inputs
    for (const auto& name : inputs) {
        // get ptr
        std::unique_ptr<nts::IComponent>& comp = _components.at(name);
        // get Val of ptr
        nts::Tristate val = comp->compute(1);
        // white space
        std::cout << "  " << name << ": ";
        // print
        std::cout << ((val == nts::Tristate::Undefined) ? 'U' : (val == nts::Tristate::True) ? '1' : '0') << std::endl;
    }
    std::cout << "output(s):" << std::endl;

    for (const auto& name : outputs) {
        // get ptr
        std::unique_ptr<nts::IComponent>& comp = _components.at(name);
        // getValue
        nts::Tristate val = comp->compute(1);
        // white space
        std::cout << "  " << name << ": ";
        // print
        std::cout << ((val == nts::Tristate::Undefined) ? 'U' : (val == nts::Tristate::True) ? '1' : '0') << std::endl;
    }
}

void nts::Sim::simulateCmd()
{    
    gEvalId++;
    _tick++;
    for (const auto& [name, comp] : _components)
        comp->simulate(_tick);
}

void nts::Sim::setValueCmd(std::string cmd)
{
    std::size_t count = std::count(cmd.begin(), cmd.end(), '=');
    if (count != 1) {
        std::cerr << "Unknown command : " << cmd << std::endl;
        return;
    }
    // Check integrality of the line
    std::size_t pos = cmd.find("=");
    std::string name = cmd.substr(0, pos);

    if (name == "") {
        std::cerr << "For attribute a variable you shall write a pattern like this : input=1" << std::endl;
        return;
    }

    auto it = _components.find(name);
    if (it == _components.end() || !it->second) {
        std::cerr << "Component " << name << " does not existe" << std::endl;
        return;
    }

    nts::Tristate value = this->convertToTristate(cmd.substr(pos + 1));
    nts::IComponent* comp = it->second.get();

    if (auto* input = dynamic_cast<nts::Input*>(comp)) {
        input->saveValue(value);
        return;
    }
    if (auto* clock = dynamic_cast<nts::Clock*>(comp)) {
        clock->saveValue(value);
        return;
    }
    std::cerr << "Objet componet can't be attribute a value" << std::endl;
}

void nts::Sim::run()
{
    std::string line;
    std::cout << "> " << std::flush;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::vector<std::string> tokens;
        std::string token;

        while (ss >> token)
            tokens.push_back(token);

        if (tokens.empty()) {
            std::cout << "> " << std::flush; 
            continue;
        }

        if (tokens.size() != 1) {
            std::cout << "> " << std::flush;
            continue;
        }

        std::string cmd = tokens[0];

        
        if (cmd == "display")
            this->displayCmd();
        else if (cmd == "simulate")
            this->simulateCmd();
        else if (cmd == "exit")
            break;
        else if (cmd == "loop") {
            static bool run = false;
            
            run = false;
            std::signal(SIGINT, [](int) { run = true; });

            while (!run) {
                simulateCmd();
                displayCmd();
            }
        }
        else
            this->setValueCmd(cmd);
        std::cout << "> " << std::flush;
    }
}