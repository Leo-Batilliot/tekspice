#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>

namespace nts {
class Hc4017 : public AComponent {
    public:
        Hc4017(const std::string name);
        ~Hc4017() override = default;

        nts::Tristate compute(std::size_t pin) override;
        void simulate(std::size_t tick) override;

    private:
        char _state = 0;
        nts::Tristate _prevCp0 = nts::Tristate::Undefined;
        nts::Tristate _prevCp1 = nts::Tristate::Undefined;
    };
}