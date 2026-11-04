#pragma once

#include "AComponent.hpp"
#include "ErrorHandling.hpp"
#include "IComponent.hpp"
#include <cstddef>
#include <ios>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>

namespace nts {
class logger : public AComponent {
    public:
        logger(const std::string name);
        ~logger() override = default;

        nts::Tristate compute(std::size_t pin) override;
        void simulate(std::size_t tick) override;
        int calculAddr();

    private:
        nts::Tristate _prevClock = nts::Tristate::Undefined;
        std::string _filePath;
    };
}