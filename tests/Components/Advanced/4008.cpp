#include "4008.hpp"
#include "AComponent.hpp"
#include "IComponent.hpp"
#include "Input.hpp"
#include <gtest/gtest.h>

TEST(advancedComponents4008, badPins) {
    nts::Cd4008bms comp("4008");

    EXPECT_THROW(comp.compute(1), NanoException);
}

TEST(advancedComponents4008, oneSumFalse) {
    nts::Cd4008bms comp("4008");

    nts::Input i1("i1");
    nts::Input i2("i2");
    nts::Input carr("carry");

    nts::gEvalId++;
    i1.saveValue(nts::Tristate::True);
    i2.saveValue(nts::Tristate::True);
    carr.saveValue(nts::Tristate::False);

    i1.simulate(1);
    i2.simulate(1);
    carr.simulate(1);

    comp.setLink(6, i1, 1);
    comp.setLink(7, i2, 1);
    comp.setLink(9, carr, 1);

    nts::gEvalId++;
    // Sum = A ^ B ^ CARRY
    // SUM = FALSE xor CARRY
    // SUM = FALSE
    EXPECT_EQ(comp.compute(10), nts::Tristate::False);
}

TEST(advancedComponents4008, oneSumTrue) {
    nts::Cd4008bms comp("4008");

    nts::Input i1("i1");
    nts::Input i2("i2");
    nts::Input carr("carry");

    nts::gEvalId++;
    i1.saveValue(nts::Tristate::False);
    i2.saveValue(nts::Tristate::True);
    carr.saveValue(nts::Tristate::False);

    i1.simulate(1);
    i2.simulate(1);
    carr.simulate(1);

    comp.setLink(6, i1, 1);
    comp.setLink(7, i2, 1);
    comp.setLink(9, carr, 1);

    // Sum = A ^ B ^ CARRY
    // SUM = FALSE xor CARRY
    // SUM = FALSE
    nts::gEvalId++;
    EXPECT_EQ(comp.compute(10), nts::Tristate::True);
}

TEST(advancedComponents4008, maxSumTrue) {
    nts::Cd4008bms comp("4008");

    nts::Input i1("i1");
    nts::Input i2("i2");

    nts::Input carr("carry");

    i1.saveValue(nts::Tristate::False);
    i2.saveValue(nts::Tristate::True);
    carr.saveValue(nts::Tristate::False);

    i1.simulate(1);
    i2.simulate(1);
    carr.simulate(1);

    comp.setLink(6, i1, 1);
    comp.setLink(7, i2, 1);
    comp.setLink(9, carr, 1);

    // Sum = A ^ B ^ CARRY
    // SUM = FALSE xor CARRY
    // SUM = FALSE
    nts::gEvalId++;
    EXPECT_EQ(comp.compute(10), nts::Tristate::True);
}

TEST(advancedComponents4008, maxSum) {
    nts::Cd4008bms comp("4008");

    nts::Input A1("A1"), A2("A2"), A3("A3"), A4("A4");
    nts::Input B1("B1"), B2("B2"), B3("B3"), B4("B4");
    nts::Input Carry("Carry");

    comp.setLink(7, A1, 1);
    comp.setLink(5, A2, 1);
    comp.setLink(3, A3, 1);
    comp.setLink(1, A4, 1);

    comp.setLink(6,  B1, 1);
    comp.setLink(4,  B2, 1);
    comp.setLink(2,  B3, 1);
    comp.setLink(15, B4, 1);

    comp.setLink(9, Carry, 1);

    // A=1111, B=1111, Carry=0
    A1.saveValue(nts::Tristate::True);
    A2.saveValue(nts::Tristate::True);
    A3.saveValue(nts::Tristate::True);
    A4.saveValue(nts::Tristate::True);

    B1.saveValue(nts::Tristate::True);
    B2.saveValue(nts::Tristate::True);
    B3.saveValue(nts::Tristate::True);
    B4.saveValue(nts::Tristate::True);

    Carry.saveValue(nts::Tristate::False);

    A1.simulate(1); A2.simulate(1); A3.simulate(1); A4.simulate(1);
    B1.simulate(1); B2.simulate(1); B3.simulate(1); B4.simulate(1);
    Carry.simulate(1);

    nts::gEvalId++;
    comp.simulate(1);
    EXPECT_EQ(comp.compute(10), nts::Tristate::False);

    comp.simulate(1);
    EXPECT_EQ(comp.compute(11), nts::Tristate::True);

    comp.simulate(1);
    EXPECT_EQ(comp.compute(12), nts::Tristate::True);

    comp.simulate(1);
    EXPECT_EQ(comp.compute(13), nts::Tristate::True);

    comp.simulate(1);
    EXPECT_EQ(comp.compute(14), nts::Tristate::True);
}