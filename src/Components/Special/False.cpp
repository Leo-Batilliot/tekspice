#include "Components/Special/False.hpp"
#include "AComponent.hpp"
#include "IComponent.hpp"

namespace nts {

FalseComp::FalseComp(const std::string& name) : AComponent(name, 1) {}

nts::Tristate FalseComp::compute(std::size_t pin) {
    if (pin != 1) {
        throw NanoException("Pin is not a valid output pin");
    }
    if (!shouldCompute(pin)) return cachedValue(pin);

    storeValue(pin, nts::Tristate::False);
    return nts::Tristate::False;
}

}
