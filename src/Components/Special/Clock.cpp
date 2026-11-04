#include "AComponent.hpp"
#include "IComponent.hpp"
#include "Clock.hpp"

namespace nts {

Clock::Clock(const std::string& name) : AComponent(name, 1) {}

nts::Tristate Clock::compute(std::size_t pin) {
    if (pin != 1) {
        throw NanoException("Pin is not a valid output pin");
    }
    if (!shouldCompute(pin)) return cachedValue(pin);
    
    storeValue(pin, _value);
    return _value;
}

void Clock::simulate(size_t tick) {
    (void)tick;

    if (_next) {
        _value = _saveValue;
        _next = false;
        return;
    }

    if (_value == nts::Tristate::Undefined)
        return;
    _value = (_value == nts::Tristate::True ? nts::Tristate::False : nts::Tristate::True);
}

void Clock::saveValue(nts::Tristate value) {
    _saveValue = value;
    _next = true;
}

}