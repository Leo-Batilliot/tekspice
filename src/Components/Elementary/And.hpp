#pragma once

#include "AComponent.hpp"
#include <cstddef>

namespace nts {
class And : public AComponent {
    public:
        And(const std::string name);
        ~And() override = default;

        nts::Tristate compute(std::size_t pin) override;

    };
}