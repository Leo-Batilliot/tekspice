#pragma once

#include "AComponent.hpp"

namespace nts {
class Not : public AComponent {
    public:
        Not(const std::string name);
        ~Not() override = default;

        nts::Tristate compute(std::size_t pin) override;
    };
}