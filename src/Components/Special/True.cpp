#include "True.hpp"
#include "AComponent.hpp"
#include "IComponent.hpp"

namespace nts {

TrueComp::TrueComp(const std::string& name) : AComponent(name, 1) {}

nts::Tristate TrueComp::compute(std::size_t pin) {
    if (pin != 1) {
        throw NanoException("Pin is not a valid output pin");
    }
    if (!shouldCompute(pin)) return cachedValue(pin);
    storeValue(pin, nts::Tristate::True);
    return nts::Tristate::True;
}

}