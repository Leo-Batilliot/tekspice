#include "AComponent.hpp"
#include "ErrorHandling.hpp"
#include "IComponent.hpp"
#include <array>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <ostream>
#include "2716.hpp"

namespace nts {

Mm2716e::Mm2716e(const std::string name) : AComponent(name, 24) {
    // Load info of file
    _file = "rom.bin";
    _size = 2048;

    // Init DATA
    for (auto &row : _data)
        row.fill(nts::Tristate::Undefined);

    // Parse file
    this->parseRom();
}

nts::Tristate Mm2716e::compute(std::size_t pin) {
    if (!shouldCompute(pin)) return cachedValue(pin);
    // PINS
    static const std::map<std::size_t, std::size_t> Pins = {
        {9, 0},
        {10, 1},
        {11, 2},
        {13, 3},
        {14, 4},
        {15, 5},
        {16, 6},
        {17, 7}
    };

    auto it = Pins.find(pin);

    if (it == Pins.end()) {
        throw NanoException("Pin is not a valid output pin");
    }

    // Load addr input
    int addr = this->loadAddr();

    if (addr == -1) {
        storeValue(pin, nts::Tristate::Undefined);
        return nts::Tristate::Undefined;
    }

    // CE OE
    nts::Tristate CE = this->getLink(18);
    nts::Tristate OE = this->getLink(20);

    if (CE == nts::Tristate::Undefined || OE == nts::Tristate::Undefined) {
        storeValue(pin, nts::Tristate::Undefined);
        return nts::Tristate::Undefined;
    }

    if (CE == nts::Tristate::True || OE == nts::Tristate::True) {
        storeValue(pin, nts::Tristate::Undefined);
        return nts::Tristate::Undefined;
    }

    nts::Tristate res = _data[addr][it->second];
    storeValue(pin, res);
    return res;
}

void Mm2716e::parseRom() {
    std::ifstream file(_file, std::ios::binary);
    
    if (!file) {
        throw NanoException("Failed to open file: " + _file);
    }
    for (std::size_t addr = 0; addr < _size; addr++) {
        // char (1 octet = 8 bit)
        char c;
        if (!file.get(c)) {
            throw NanoException("Invalid ROM file: expected one byte per address");
        }

        unsigned char byte = static_cast<unsigned char>(c);

        // for each bit in octet add in data
        for (std::size_t i = 0; i < 8; i++) {
            bool bit = ((byte >> i) & 1);
            nts::Tristate value = (bit == true) ? nts::Tristate::True : nts::Tristate::False;
            _data[addr][i] = value;
        }
    }
}

int Mm2716e::loadAddr() {
    // Calcul addr
    int addr = 0;
    int i = 1;

    // load Adresse Input
    static const std::vector<int> vecs = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22, 19};
    for (std::size_t k = 0; k < vecs.size(); k++) {
        nts::Tristate tmp = this->getLink(vecs[k]);
        if (tmp == nts::Tristate::Undefined)
            return -1;

        int val = (tmp == nts::Tristate::True) ? 1 : 0;
        addr += val * i;
        i = i + i;
    }

    return (addr < 0 || addr >= 2048) ? -1 : addr;
}

}