#include "Input.hpp"
#include "AComponent.hpp"
#include "IComponent.hpp"

namespace nts {

Input::Input(const std::string name) : AComponent(name, 1) {}

nts::Tristate Input::compute(std::size_t pin) {
    if (pin != 1) {
        throw NanoException("Pin is not a valid output pin");
    }
    if (!shouldCompute(pin)) return cachedValue(pin);

    storeValue(pin, _value);
    return _value;
}

void Input::simulate(std::size_t tick) {
    (void)tick;

    _value = _saveValue;
}

void Input::saveValue(nts::Tristate value) {
    _saveValue = value;
}

}