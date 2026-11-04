#include "Components/Special/OutPut.hpp"
#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>

namespace nts {

OutPut::OutPut(const std::string& name) : AComponent(name, 1) {}

nts::Tristate OutPut::compute(std::size_t pin) {
    if (pin != 1) {
        throw NanoException("Pin is not a valid output pin");
    }
    if (!shouldCompute(pin)) return cachedValue(pin);
    nts::Tristate val = this->getLink(1);
    storeValue(pin, val);
    return val;
}

}