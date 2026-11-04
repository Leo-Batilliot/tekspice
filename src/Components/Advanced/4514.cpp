#include "AComponent.hpp"
#include "IComponent.hpp"
#include <algorithm>
#include <cstddef>
#include <vector>
#include "4514.hpp"

namespace nts {

Cd4514bc::Cd4514bc(const std::string name) : AComponent(name, 24) {}

nts::Tristate Cd4514bc::compute(std::size_t pin) {
    if (!shouldCompute(pin)) return cachedValue(pin);
    // check inhibit
    nts::Tristate inhibit = this->getLink(23);
    if (inhibit == nts::Tristate::Undefined) {
        storeValue(pin, nts::Tristate::Undefined);
        return nts::Tristate::Undefined;
    }

    if (inhibit == nts::Tristate::True) {
        storeValue(pin, nts::Tristate::False);
        return nts::Tristate::False;
    }

    // init index
    std::size_t index = 0;
    std::size_t i = 1;

    // Calcul index
    static const std::vector<std::size_t> vecs = {2, 3, 21, 22};

    for (std::size_t k = 0; k < vecs.size(); k++) {
        nts::Tristate tmp = this->getLink(vecs[k]);

        if (tmp == nts::Tristate::Undefined) {
            storeValue(pin, nts::Tristate::Undefined);
            return nts::Tristate::Undefined;
        }

        std::size_t val = (tmp == nts::Tristate::True) ? 1 : 0;
        index += val * i;
        i = i + i;
    }

    // check Pin Entry (vector are ranged)
    static const std::vector<std::size_t> Out = {11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19, 14, 13, 16, 15};

    auto find = std::find(Out.begin(), Out.end(), pin);
    if (find == Out.end()) {
        throw NanoException("Pin is not a valid output pin");
    }

    nts::Tristate res = (pin == Out[index]) ? nts::Tristate::True : nts::Tristate::False;
    storeValue(pin, res);
    return res;
}

}