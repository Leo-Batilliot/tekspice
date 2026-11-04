#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>
#include <map>
#include "4017.hpp"

namespace nts {

Hc4017::Hc4017(const std::string name) : AComponent(name, 16) {}

nts::Tristate Hc4017::compute(std::size_t pin) {
    // Q5-9
    if (pin == 12) {
        nts::Tristate res = (_state <= 4) ? nts::Tristate::True : nts::Tristate::False;
        storeValue(pin, res);
        return res;
    }

    // Init output / input
    static const std::map<std::size_t, char> pins = {
        {3, 0},
        {2, 1},
        {4, 2},
        {7, 3},
        {10, 4},
        {1, 5},
        {5, 6},
        {6, 7},
        {9, 8},
        {11, 9}
    };

    auto find = pins.find(pin);

    if (find == pins.end()) {
       throw NanoException("Pin is not a valid output pin");
    }

    if (!shouldCompute(pin)) return cachedValue(pin);
    nts::Tristate res = (_state == find->second) ? nts::Tristate::True : nts::Tristate::False;
    storeValue(pin, res);
    return res;
}

void Hc4017::simulate(std::size_t tick) {
    (void)tick;

    nts::Tristate mr = this->getLink(15);
    nts::Tristate cp0 = this->getLink(14);
    nts::Tristate cp1 = this->getLink(13);

    if (mr == nts::Tristate::True) {
        _state = 0;
    } 
    else if (cp0 != nts::Tristate::Undefined && cp1 != nts::Tristate::Undefined) {
        bool clock_up_cp0 = (_prevCp0 == nts::Tristate::False && cp0 == nts::Tristate::True);
        if (clock_up_cp0 && cp1 == nts::Tristate::False) {
            _state = (_state + 1) % 10;
        }
        bool clock_down_cp1 = (_prevCp1 == nts::Tristate::True && cp1 == nts::Tristate::False);
        if (clock_down_cp1 && cp0 == nts::Tristate::True) {
            _state = (_state + 1) % 10;
        }
    }
    _prevCp0 = cp0;
    _prevCp1 = cp1;
}

}