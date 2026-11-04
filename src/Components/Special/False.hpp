#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"

namespace nts {
class FalseComp : public AComponent {
    public:
        FalseComp(const std::string& name);
        ~FalseComp() override = default;

        nts::Tristate compute(std::size_t pin) override;
    };
}