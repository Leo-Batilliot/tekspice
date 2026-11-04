#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>

namespace nts {
class Cd4514bc : public AComponent {
    public:
        Cd4514bc(const std::string name);
        ~Cd4514bc() override = default;

        nts::Tristate compute(std::size_t pin) override;
    };
}