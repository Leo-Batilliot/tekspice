#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>
#include <map>
#include <utility>
#include "4512.hpp"

namespace nts {

Cd4512bm::Cd4512bm(const std::string name) : AComponent(name, 16) {}

nts::Tristate Cd4512bm::compute(std::size_t pin) {
    if (!shouldCompute(pin)) return cachedValue(pin);
    // check pin 14
    if (pin != 14) {
        storeValue(pin, nts::Tristate::Undefined);
        return nts::Tristate::Undefined;
    }

    // check oe
    nts::Tristate oe = this->getLink(15);
    if (oe != nts::Tristate::False) {
        storeValue(pin, nts::Tristate::Undefined);
        return nts::Tristate::Undefined;
    }

    // check inhibit
    nts::Tristate inhibit = this->getLink(10);
    if (inhibit == nts::Tristate::True) {
        storeValue(pin, nts::Tristate::False);
        return nts::Tristate::False;
    }

    if (inhibit == nts::Tristate::Undefined) {
        storeValue(pin, nts::Tristate::Undefined);
        return nts::Tristate::Undefined;
    }

    // init abc
    nts::Tristate a = this->getLink(11);
    nts::Tristate b = this->getLink(12);
    nts::Tristate c = this->getLink(13);

    // check if one of them is undefine
    if (a == nts::Tristate::Undefined || b == nts::Tristate::Undefined || c == nts::Tristate::Undefined) {
        storeValue(pin, nts::Tristate::Undefined);
        return nts::Tristate::Undefined;
    }

    // calcul idx (add of the bit)
    std::size_t index = (a == nts::Tristate::True ? 1 : 0) + (b == nts::Tristate::True ? 2 : 0) + (c == nts::Tristate::True ? 4 : 0);

    // init pins (ex : index = 2. pins[2] = 3 soit X2 = 3)
    static const std::map<std::size_t, std::size_t> pins = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 5},
        {5, 6},
        {6, 7},
        {7, 9}
    };
    auto search = pins.find(index);

    if (search == pins.end()) {
        storeValue(pin, nts::Tristate::Undefined);
        return nts::Tristate::Undefined;
    }

    nts::Tristate res = this->getLink(search->second);
    storeValue(pin, res);
    return res;
}

}