#include "Components/Elementary/And.hpp"
#include "AComponent.hpp"
#include <cstddef>

namespace nts {

And::And(const std::string name) : AComponent(name, 3) {}

nts::Tristate And::compute(std::size_t pin) {
    if (pin != 3) {
        throw NanoException("Pin is not a valid output pin");
    }

    if (!shouldCompute(pin)) return cachedValue(pin);

    nts::Tristate a = getLink(1);
    nts::Tristate b = getLink(2);

    if (a == nts::Tristate::True && b == nts::Tristate::True) {
        storeValue(pin, nts::Tristate::True);
        return nts::Tristate::True;
    }

    if (a == nts::Tristate::False || b == nts::Tristate::False) {
        storeValue(pin, nts::Tristate::False);
        return nts::Tristate::False;
    }

    storeValue(pin, nts::Tristate::Undefined);
    return nts::Tristate::Undefined;
}

}