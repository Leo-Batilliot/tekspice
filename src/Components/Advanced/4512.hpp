#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>

namespace nts {
class Cd4512bm : public AComponent {
    public:
        Cd4512bm(const std::string name);
        ~Cd4512bm() override = default;

        nts::Tristate compute(std::size_t pin) override;
    };
}