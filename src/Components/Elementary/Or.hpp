#pragma once

#include "AComponent.hpp"

namespace nts {
class Or : public AComponent {
    public:
        Or(const std::string name);
        ~Or() override = default;

        nts::Tristate compute(std::size_t pin) override;
    };
}