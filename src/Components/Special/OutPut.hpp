#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>

namespace nts {
class OutPut : public AComponent {
    public:
        OutPut(const std::string& name);
        ~OutPut() override = default;

        nts::Tristate compute(std::size_t pin) override;
    };
}