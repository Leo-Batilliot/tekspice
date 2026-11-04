#include "AComponent.hpp"
#include "ErrorHandling.hpp"
#include "IComponent.hpp"
#include <cstddef>
#include <ios>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include "Logger.hpp"

namespace nts {

logger::logger(const std::string name) : AComponent(name, 10) {
    _filePath = "log.bin";
}

nts::Tristate logger::compute(std::size_t pin) {
    if (pin < 1 || pin > 10)
        throw NanoException("Pin is not a valid output pin");
    if (!shouldCompute(pin)) return cachedValue(pin);

    nts::Tristate val = this->getLink(pin);
    storeValue(pin, val);
    return val;
}

void logger::simulate(std::size_t tick) {
    (void)tick;

    nts::Tristate clock = this->getLink(9);

    if (clock == nts::Tristate::Undefined) {
        _prevClock = clock;
        return;
    }
    nts::Tristate inhibit = this->getLink(10);

    // Detect front montant
    bool upClock = (_prevClock == nts::Tristate::False && clock == nts::Tristate::True && inhibit == nts::Tristate::False);

    if (upClock) {
        // Calcul value
        auto addr = this->calculAddr();
        if (addr == -1)
            return;

        // Write in file
        std::ofstream file(_filePath, std::ios::binary | std::ios::app);
        if (!file.is_open())
            throw NanoException("Failed to open log file: " + _filePath);

        char c = static_cast<char>(addr);
        file.write(&c, 1);
    }
    _prevClock = clock;
}

int logger::calculAddr() {
    // Calcul addr
    int addr = 0;
    int i = 1;
    static const std::vector<std::size_t> vecs = {1,2,3,4,5,6,7,8};
    for (std::size_t k = 0; k < vecs.size(); k++) {
        nts::Tristate tmp = this->getLink(vecs[k]);
        if (tmp == nts::Tristate::Undefined)
            return -1;

        std::size_t val = (tmp == nts::Tristate::True) ? 1 : 0;
        addr += val * i;
        i = i + i;
    }
    return addr;
}

}