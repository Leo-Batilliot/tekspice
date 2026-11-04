#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>

namespace nts {
class Cd4011b : public AComponent {
    public:
        Cd4011b(const std::string name);
        ~Cd4011b() override = default;

        nts::Tristate compute(std::size_t pin) override;
    };
}