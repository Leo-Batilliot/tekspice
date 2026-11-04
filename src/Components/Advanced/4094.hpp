#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <array>
#include <cstddef>

namespace nts {
class Cd4094bc : public AComponent {
    public:
        Cd4094bc(const std::string name);
        ~Cd4094bc() override = default;

        nts::Tristate compute(std::size_t pin) override;
    
        void simulate(std::size_t tick) override;

    private:
        nts::Tristate _prevClock = nts::Tristate::Undefined;
        std::array<nts::Tristate, 8> _shift;
        std::array<nts::Tristate, 2> _outputs;
    };
}