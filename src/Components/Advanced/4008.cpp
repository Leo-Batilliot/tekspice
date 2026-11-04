#include "AComponent.hpp"
#include "IComponent.hpp"
#include <cstddef>
#include <map>
#include <utility>
#include <vector>
#include "Utils.hpp"
#include "4008.hpp"

namespace nts {

Cd4008bms::Cd4008bms(const std::string name) : AComponent(name, 16) {}

nts::Tristate Cd4008bms::compute(std::size_t pin) {
    static const std::map<std::size_t, std::vector<std::pair<std::size_t, std::size_t>>> map  = {
        {10,  {{6, 7}}},
        {11,  {{6, 7}, {4, 5}}},
        {12,  {{6, 7}, {4, 5}, {2, 3}}},
        {13,  {{6, 7}, {4, 5}, {2, 3}, {15, 1}}},
        {14,  {{6, 7}, {4, 5}, {2, 3}, {15, 1}}}
    };

    const auto it = map.find(pin);

    if (it == map.end()) {
        throw NanoException("Pin is not a valid output pin");
    }
    
    if (!shouldCompute(pin)) return cachedValue(pin);

    nts::Tristate carry = getLink(9);
    nts::Tristate sum = nts::Tristate::Undefined;

    for (const auto& [pinB, pinA] : it->second) {
        nts::Tristate a = getLink(pinA);
        nts::Tristate b = getLink(pinB);

        // Sum = A ^ B ^ CARRY
        sum = Utils::xor_func(Utils::xor_func(a, b), carry);
        carry = Utils::carry_func(a, b, carry);
    }
    nts::Tristate res = (pin == 14) ? carry : sum;
    storeValue(pin, res);
    return res;
}

}