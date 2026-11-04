#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>
#include <map>
#include <utility>
#include "4040.hpp"

namespace nts {

Mc14040b::Mc14040b(const std::string name) : AComponent(name, 16) {}

nts::Tristate Mc14040b::compute(std::size_t pin) {
    static const std::map<std::size_t, int> maps = {
        {9, 0},
        {7, 1},
        {6, 2},
        {5, 3},
        {3, 4},
        {2, 5},
        {4, 6},
        {13, 7},
        {12, 8},
        {14, 9},
        {15, 10},
        {1, 11}
    };

    auto it = maps.find(pin);

    if (it == maps.end()) {
        throw NanoException("Pin is not a valid output pin");
    }
    if (!shouldCompute(pin)) return cachedValue(pin);

    // example : (_count >> bit) & masque
    // example : (1 >> 2) & 1
    // example : (0001 >> 0010) & 0001 = 0000 --> 0
    bool flag = (_count >> it->second) & 1;

    nts::Tristate res = (flag == true) ? nts::Tristate::True : nts::Tristate::False;
    storeValue(pin, res);
    return res;
}

void Mc14040b::simulate(std::size_t tick) {
    (void)tick;

    nts::Tristate clockFlag = this->getLink(10);
    nts::Tristate resetFlag = this->getLink(11);

    if (clockFlag == nts::Tristate::Undefined) {
        _prevClock = clockFlag;
        return;
    }

    if (resetFlag == nts::Tristate::True) {
        _prevClock = clockFlag;
        _count = 0;
        return;
    }

    // front descandant
    if (_prevClock == nts::Tristate::True && clockFlag == nts::Tristate::False) {
        _count = (_count + 1) % 4096;
    }
    _prevClock = clockFlag;
}

}