#include "AComponent.hpp"
#include "IComponent.hpp"
#include <array>
#include <cstddef>
#include <map>
#include <utility>
#include <vector>
#include "4801.hpp"

namespace nts {

Mk4801a::Mk4801a(const std::string name) : AComponent(name, 24) {
    // Init RAM with Undefined
    for (auto &byte : _Data)
        byte.fill(nts::Tristate::Undefined);
}

std::size_t Mk4801a::getAddr()
{
    std::size_t addr = 0;
    std::size_t i = 1;
    static const std::vector<std::size_t> vecs = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22};
    for (std::size_t k = 0; k < vecs.size(); k++) {
        nts::Tristate tmp = this->getLink(vecs[k]);
        if (tmp == nts::Tristate::Undefined)
            return 1025;

        std::size_t val = (tmp == nts::Tristate::True) ? 1 : 0;
        addr += val * i;
        i = i + i;
    }
    return addr;
}

nts::Tristate Mk4801a::compute(std::size_t pin) {
    // Pins, num
    static const std::map<std::size_t, std::size_t> Data = {
        {9, 0},
        {10, 1},
        {11, 2},
        {13, 3},
        {14, 4},
        {15, 5},
        {16, 6},
        {17, 7}
    };

    // Check PINS
    auto it = Data.find(pin);
    if (it == Data.end()) {
        storeValue(pin, nts::Tristate::Undefined);
        return nts::Tristate::Undefined;
    }

    // CHeck cache
    if (!shouldCompute(pin)) return cachedValue(pin);

    nts::Tristate ce = getLink(18);
    nts::Tristate oe = getLink(20);
    nts::Tristate we = getLink(21);

    if (ce == nts::Tristate::False && oe == nts::Tristate::False && we == nts::Tristate::True) {
        std::size_t addr = this->getAddr();
        if (addr == 1025) {
            storeValue(pin, nts::Tristate::Undefined);
            return nts::Tristate::Undefined;
        }
        nts::Tristate res = _Data[addr][it->second];
        storeValue(pin, res);
        return res;
    }
    // High-Z
    storeValue(pin, nts::Tristate::Undefined);
    return nts::Tristate::Undefined;
}

void Mk4801a::simulate(std::size_t tick) {
    (void)tick;
    nts::Tristate ce = getLink(18);
    nts::Tristate we = getLink(21);

    if (ce == nts::Tristate::False && we == nts::Tristate::False) {
        std::size_t addr = this->getAddr();
        if (addr != 1025) {
            static const std::size_t qPins[] = {9, 10, 11, 13, 14, 15, 16, 17};
            for (int i = 0; i < 8; i++) {
                _Data[addr][i] = getLink(qPins[i]);
            }
        }
    }
}

}