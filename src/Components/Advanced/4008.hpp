#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>

namespace nts {
class Cd4008bms : public AComponent {
    public:
        Cd4008bms(const std::string name);
        ~Cd4008bms() override = default;

        nts::Tristate compute(std::size_t pin) override;
    };
}