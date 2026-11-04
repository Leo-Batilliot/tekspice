#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>
#include <map>
#include <utility>
#include "4001.hpp"

namespace nts {

Hef4001b::Hef4001b(const std::string name) : AComponent(name, 14) {}

nts::Tristate Hef4001b::compute(std::size_t pin) {
    // MAP
    static const std::map<std::size_t, std::pair<std::size_t, std::size_t>> map  = {
        {3,  {1, 2}},
        {4,  {5, 6}},
        {10, {8, 9}},
        {11, {12, 13}}
    };

    const auto it = map.find(pin);

    if (it == map.end()) {
        throw NanoException("Pin is not a valid output pin");
    }

    if (!shouldCompute(pin)) return cachedValue(pin);

    auto [pinA, pinB] = it->second;

    nts::Tristate a = getLink(pinA);
    nts::Tristate b = getLink(pinB);

    if (a == nts::Tristate::True || b == nts::Tristate::True) {
        storeValue(pin, nts::Tristate::False);
        return nts::Tristate::False;
    }

    if (a == nts::Tristate::False && b == nts::Tristate::False) {
        storeValue(pin, nts::Tristate::True);
        return nts::Tristate::True;
    }
    
    storeValue(pin, nts::Tristate::Undefined);
    return nts::Tristate::Undefined;
}

}