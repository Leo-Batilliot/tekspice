#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>

namespace nts {
class Cd4013bc : public AComponent {
    public:
        Cd4013bc(const std::string name);
        ~Cd4013bc() override = default;

        nts::Tristate compute(std::size_t pin) override;

        nts::Tristate invert(nts::Tristate value);

        void simulate(size_t tick) override;
    private:
        nts::Tristate _q[2] = {nts::Tristate::Undefined, nts::Tristate::Undefined};
        nts::Tristate _qb[2] = {nts::Tristate::Undefined, nts::Tristate::Undefined};
        nts::Tristate _prevClock[2] = {nts::Tristate::Undefined, nts::Tristate::Undefined};

    };
}