#include "Or.hpp"

namespace nts {

Or::Or(const std::string name) : AComponent(name, 3) {}

nts::Tristate Or::compute(std::size_t pin) {
    if (pin != 3) {
        throw NanoException("Pins must be in avalaible pins of output");
    }

    if (!shouldCompute(pin)) return cachedValue(pin);

    nts::Tristate a = getLink(1);
    nts::Tristate b = getLink(2);

    if (a == nts::Tristate::True || b == nts::Tristate::True) {
        storeValue(pin, nts::Tristate::True);
        return nts::Tristate::True;
    }

    if (a == nts::Tristate::False && b == nts::Tristate::False) {
        storeValue(pin, nts::Tristate::False);
        return nts::Tristate::False;
    }

    storeValue(pin, nts::Tristate::Undefined);
    return nts::Tristate::Undefined;
}

}