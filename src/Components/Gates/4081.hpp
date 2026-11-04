#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>
#include <map>
#include <utility>

namespace nts {
class Hcf4081b : public AComponent {
    public:
        Hcf4081b(const std::string name);
        ~Hcf4081b() override = default;

        nts::Tristate compute(std::size_t pin) override;
    };
}