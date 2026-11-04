#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>
#include <map>
#include <utility>
#include "4030.hpp"

namespace nts {

Cd4030c::Cd4030c(const std::string name) : AComponent(name, 14) {}

nts::Tristate Cd4030c::compute(std::size_t pin) {
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

    if (a == nts::Tristate::Undefined || b == nts::Tristate::Undefined) {
        storeValue(pin, nts::Tristate::Undefined);
        return nts::Tristate::Undefined;
    }

    nts::Tristate res = (a == b) ? nts::Tristate::False : nts::Tristate::True;
    storeValue(pin, res);
    return res;
}

}