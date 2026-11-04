#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>

namespace nts {
class Cd4030c : public AComponent {
    public:
        Cd4030c(const std::string name);
        ~Cd4030c() override = default;

        nts::Tristate compute(std::size_t pin) override;
    };
}