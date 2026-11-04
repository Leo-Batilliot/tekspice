#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>

namespace nts {
class Mc14040b : public AComponent {
    public:
        Mc14040b(const std::string name);
        ~Mc14040b() override = default;

        nts::Tristate compute(std::size_t pin) override;
        void simulate(std::size_t tick) override;

    private:
        int _count = 0;

        nts::Tristate _prevClock = nts::Tristate::Undefined;
    };
}