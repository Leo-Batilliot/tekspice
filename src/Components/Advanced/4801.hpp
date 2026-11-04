#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <array>
#include <cstddef>

namespace nts {
class Mk4801a : public AComponent {
    public:
        Mk4801a(const std::string name);

        ~Mk4801a() override = default;

        // 1024 (octet) = 1024 * 8
        nts::Tristate compute(std::size_t pin) override;
        void simulate(std::size_t tick) override;

        std::size_t getAddr();

    private:
        std::array<std::array<nts::Tristate, 8>, 1024> _Data;
    };
}