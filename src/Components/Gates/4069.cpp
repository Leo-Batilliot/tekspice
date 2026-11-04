#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>
#include <map>
#include <utility>
#include "4069.hpp"

namespace nts {

Cd4069ubc::Cd4069ubc(const std::string name) : AComponent(name, 14) {}

nts::Tristate Cd4069ubc::compute(std::size_t pin) {
    static const std::map<std::size_t, std::size_t> map  = {
        {2,  1},
        {4,  3},
        {6,  5},
        {8,  9},
        {10, 11},
        {12, 13}
    };

    const auto it = map.find(pin);

    if (it == map.end()) {
        throw NanoException("Pin is not a valid output pin");
    }

    if (!shouldCompute(pin)) return cachedValue(pin);

    auto Pin = it->second;

    nts::Tristate a = getLink(Pin);

    if (a == nts::Tristate::Undefined) {
        storeValue(pin, nts::Tristate::Undefined);
        return nts::Tristate::Undefined;
    }
    
    nts::Tristate result = (a == nts::Tristate::False) ? nts::Tristate::True : nts::Tristate::False;
    storeValue(pin, result);
    return result;
}

}