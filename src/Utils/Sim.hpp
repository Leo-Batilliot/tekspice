#pragma once

#include <cstddef>
#include <iostream>
#include "Factory/Factory.hpp"
#include "IComponent.hpp"


namespace nts {

extern std::size_t gEvalId;

class Sim {
    public:
        Sim(std::unordered_map<std::string, std::unique_ptr<nts::IComponent>>& comps) : _components(comps), _tick(0) {}

        void displayCmd();
        void simulateCmd();
        void setValueCmd(std::string cmd);
        nts::Tristate convertToTristate(std::string);
        void run();
    
    private:
        std::unordered_map<std::string, std::unique_ptr<nts::IComponent>>& _components;
        std::size_t _tick;
};
}