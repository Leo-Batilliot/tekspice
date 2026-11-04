#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"

namespace nts {
class Clock : public AComponent {
    public:
        Clock(const std::string& name);
        ~Clock() override = default;

        nts::Tristate compute(std::size_t pin) override;
        void simulate(size_t tick) override;
        void saveValue(nts::Tristate value);

    private:
        nts::Tristate _saveValue = nts::Tristate::Undefined;
        bool _next = false;
        nts::Tristate _value = nts::Tristate::Undefined;
    };
}