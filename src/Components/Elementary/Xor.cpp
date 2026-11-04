#include "Xor.hpp"

namespace nts {

XorComp::XorComp(const std::string name) : AComponent(name, 3) {}

nts::Tristate XorComp::compute(std::size_t pin) {
    if (pin != 3) {
        throw NanoException("Pins must be in avalaible pins of output");
    }

    if (!shouldCompute(pin)) return cachedValue(pin);

    nts::Tristate a = getLink(1);
    nts::Tristate b = getLink(2);

    if (a == nts::Tristate::Undefined || b == nts::Tristate::Undefined) {
        storeValue(pin, nts::Tristate::Undefined);
        return nts::Tristate::Undefined;
    }

    if (a == b) {
        storeValue(pin, nts::Tristate::False);
        return nts::Tristate::False;
    }

    storeValue(pin, nts::Tristate::True);
    return nts::Tristate::True;
};

}