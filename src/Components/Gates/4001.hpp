#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>

namespace nts {
class Hef4001b : public AComponent {
    public:
        Hef4001b(const std::string name);
        ~Hef4001b() override = default;

        nts::Tristate compute(std::size_t pin) override;
    };
}