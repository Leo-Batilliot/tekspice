#pragma once

#include "AComponent.hpp"
#include "IComponent.hpp"
#include <array>
#include <cstddef>

namespace nts {
class Mm2716e : public AComponent {
    public:
        Mm2716e(const std::string name);
        ~Mm2716e() override = default;

        nts::Tristate compute(std::size_t pin) override;

        void parseRom();
        int loadAddr();

    private:
        std::string _file;
        std::size_t _size;
        std::array<std::array<nts::Tristate, 8>, 2048> _data;
    };
}