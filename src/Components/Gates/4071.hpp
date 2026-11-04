#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>
#include <map>
#include <utility>

namespace nts {
class Hef4071b : public AComponent {
    public:
        Hef4071b(const std::string name);
        ~Hef4071b() override = default;

        nts::Tristate compute(std::size_t pin) override;
    };
}