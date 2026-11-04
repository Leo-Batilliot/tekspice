#include "AComponent.hpp"
#include "Not.hpp"

namespace nts {

Not::Not(const std::string name) : AComponent(name, 2) {}

nts::Tristate Not::compute(std::size_t pin) {
    if (pin != 2) {
        throw NanoException("Pin is not a valid output pin");
    }

    if (!shouldCompute(pin)) return cachedValue(pin);

    nts::Tristate a = getLink(1);

    if (a == nts::Tristate::Undefined) {
        storeValue(pin, nts::Tristate::Undefined);
        return nts::Tristate::Undefined;
    }

    if (a == nts::Tristate::True) {
        storeValue(pin, nts::Tristate::False);
        return nts::Tristate::False;
    }

    storeValue(pin, nts::Tristate::True);
    return nts::Tristate::True;
}

}