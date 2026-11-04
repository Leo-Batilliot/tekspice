#include "AComponent.hpp"
#include "IComponent.hpp"
#include <array>
#include <cstddef>
#include <map>
#include <utility>
#include "4094.hpp"

namespace nts {

Cd4094bc::Cd4094bc(const std::string name) : AComponent(name, 18) {
    _shift.fill(nts::Tristate::Undefined);
    _outputs.fill(nts::Tristate::Undefined);
}

nts::Tristate Cd4094bc::compute(std::size_t pin) {
    if (!shouldCompute(pin)) return cachedValue(pin);
    if (pin == 9) {
        nts::Tristate val = _outputs[0];
        storeValue(pin, val);
        return val;
    }
    if (pin == 10) {
        nts::Tristate val = _outputs[1];
        storeValue(pin, val);
        return val;
    }

    // init
    nts::Tristate outputEnable = this->getLink(15);
    const static std::map<std::size_t, std::size_t> Map = {
        {4, 1},
        {5, 2},
        {6, 3},
        {7, 4},
        {14, 5},
        {13, 6},
        {12, 7},
        {11, 8}
    };

    auto it = Map.find(pin);

    if (it == Map.end()) {
        throw NanoException("Pin is not a valid output pin");
    }

    if (outputEnable != nts::Tristate::True) {
        storeValue(pin, nts::Tristate::Undefined);
        return nts::Tristate::Undefined;
    }

    nts::Tristate val = _shift[it->second - 1];
    storeValue(pin, val);
    return val;
}


void Cd4094bc::simulate(std::size_t tick) {
    (void)tick;
    
    // init
    nts::Tristate strobe = this->getLink(1);
    nts::Tristate data = this->getLink(2);
    nts::Tristate clock = this->getLink(3);
    nts::Tristate oldQ7 = _shift[6];

    // Montant / Descandant
    bool upClock = (_prevClock == nts::Tristate::False && clock == nts::Tristate::True);
    bool downClock = (_prevClock == nts::Tristate::True && clock == nts::Tristate::False);

    if (upClock) {
        // Qs = Q7
        _outputs[0] = oldQ7;
        if (strobe == nts::Tristate::True) {
            for (int i = 7; i > 0; i--) {
                // Qn-1
                _shift[i] = _shift[i - 1];
            }
            // Q1 = d
            _shift[0] = data;
        }
    }

    if (downClock) {
        // Q's = Q7
        _outputs[1] = oldQ7;
    }
    _prevClock = clock;
}

}