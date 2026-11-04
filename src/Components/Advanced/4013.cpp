#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>
#include "4013.hpp"

namespace nts {
 
Cd4013bc::Cd4013bc(const std::string name) : AComponent(name, 14) {}

nts::Tristate Cd4013bc::compute(std::size_t pin) {
    if (!shouldCompute(pin)) return cachedValue(pin);
    // First entry
    if (pin == 1) {
        storeValue(pin, _q[0]);
        return _q[0];
    }
    if (pin == 2) {
        storeValue(pin, _qb[0]);
        return _qb[0];
    }

    // Second entry
    if (pin == 13) {
        storeValue(pin, _q[1]);
        return _q[1];
    }
    if (pin == 12) {
        storeValue(pin, _qb[1]);
        return _qb[1];
    }

    throw NanoException("Pin is not a valid output pin");
    return nts::Tristate::Undefined;
}

nts::Tristate Cd4013bc::invert(nts::Tristate value) {
    if (value == nts::Tristate::Undefined) {
        return nts::Tristate::Undefined;
    }

    return (value == nts::Tristate::True) ? nts::Tristate::False : nts::Tristate::True;
}

void Cd4013bc::simulate(size_t tick) {
    (void)tick;

    // Init flipFlop tab
    static const std::size_t flipFlop[2][4] = {
        {3, 5, 4, 6},
        {11, 9, 10, 8}
    };

    for (int i = 0; i < 2; i++) {
        // Load data
        auto clock = getLink(flipFlop[i][0]);
        auto data = getLink(flipFlop[i][1]);
        auto reset = getLink(flipFlop[i][2]);
        auto set = getLink(flipFlop[i][3]);

        // SI RESET = 1 et SET = 1 --> UNDIFINED
        if (reset == nts::Tristate::True && set == nts::Tristate::True) {
            _q[i] = nts::Tristate::True;
            _qb[i] = nts::Tristate::True;
        }

        // Si RESET = 1 --> _q = 0
        else if (reset == nts::Tristate::True) {
            _q[i] = nts::Tristate::False;
            _qb[i] = nts::Tristate::True;
        }

        // Si SET = 1 --> _q = 1
        else if (set == nts::Tristate::True) {
            _q[i] = nts::Tristate::True;
            _qb[i] = nts::Tristate::False;
        }

        // Front Montant (mise en mémoire)
        else if (_prevClock[i] == nts::Tristate::False && clock == nts::Tristate::True) {
            _q[i] = data;
            _qb[i] = invert(data);
        }

        // Save clock for the next simulate
        _prevClock[i] = clock;
    }
}

}