#pragma once

#include <iostream>
#include "IComponent.hpp"

class Utils {
public:
    static nts::Tristate xor_func(nts::Tristate a, nts::Tristate b) {
        if (a == nts::Tristate::Undefined || b == nts::Tristate::Undefined)
            return nts::Tristate::Undefined;

        return (a == b) ? nts::Tristate::False : nts::Tristate::True;
    }

    static nts::Tristate and_func(nts::Tristate a, nts::Tristate b) {
        if (a == nts::Tristate::False || b == nts::Tristate::False)
            return nts::Tristate::False;

        if (a == nts::Tristate::True && b == nts::Tristate::True)
            return nts::Tristate::True;

        return nts::Tristate::Undefined;
    }

    static nts::Tristate or_func(nts::Tristate a, nts::Tristate b) {
        if (a == nts::Tristate::True || b == nts::Tristate::True)
            return nts::Tristate::True;

        if (a == nts::Tristate::False && b == nts::Tristate::False)
            return nts::Tristate::False;

        return nts::Tristate::Undefined;
    }

    static nts::Tristate carry_func(nts::Tristate a, nts::Tristate b, nts::Tristate carry) {
        // & = and
        // | = or
        // ^ = xor
        // Formule carry = (A & B) | (Cin & (A ^ B))
        nts::Tristate res_y = and_func(carry, xor_func(a, b));
        nts::Tristate res_x = and_func(a, b);
        nts::Tristate new_carry = or_func(res_x, res_y);

        return new_carry;
    }
};