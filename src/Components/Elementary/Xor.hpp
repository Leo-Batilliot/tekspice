#pragma once

#include "AComponent.hpp"

namespace nts {
class XorComp : public AComponent {
    public:
        XorComp(const std::string name);
        ~XorComp() override = default;

        nts::Tristate compute(std::size_t pin) override;
    };
}