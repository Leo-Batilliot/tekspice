#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>

namespace nts {
class Cd4069ubc : public AComponent {
    public:
        Cd4069ubc(const std::string name);
        ~Cd4069ubc() override = default;

        nts::Tristate compute(std::size_t pin) override;
    };
}