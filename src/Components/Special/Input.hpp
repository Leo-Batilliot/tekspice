#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"

namespace nts {
class Input : public AComponent {
    public:
        Input(const std::string name);
        ~Input() override = default;

        nts::Tristate compute(std::size_t pin) override;
        void simulate(std::size_t tick) override;
        void saveValue(nts::Tristate value);

    private:
        nts::Tristate _saveValue = nts::Tristate::Undefined;
        Tristate _value = nts::Tristate::Undefined;
    };
}