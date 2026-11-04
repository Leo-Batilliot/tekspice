#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"

namespace nts {
class TrueComp : public AComponent {
    public:
        TrueComp(const std::string& name);
        ~TrueComp() override = default;

        nts::Tristate compute(std::size_t pin) override;
    };
}