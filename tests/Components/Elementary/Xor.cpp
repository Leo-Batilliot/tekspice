#include "Xor.hpp"
#include "IComponent.hpp"
#include "Input.hpp"
#include <gtest/gtest.h>

TEST(elementaryComponentsXor, badPins) {
    nts::XorComp comp("xor");

    EXPECT_THROW(comp.compute(1), NanoException);
}

TEST(elementaryComponentsXor, verifUndefined) {
    nts::XorComp comp("xor");
    nts::Input i1("i1");
    nts::Input i2("i2");

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    i1.saveValue(nts::Tristate::Undefined);
    i2.saveValue(nts::Tristate::True);

    i1.simulate(1);
    i2.simulate(1);
    comp.simulate(1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::Undefined);
}

TEST(elementaryComponentsXor, verifUndefined2) {
    nts::XorComp comp("xor");
    nts::Input i1("i1");
    nts::Input i2("i2");

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    i1.saveValue(nts::Tristate::True);
    i2.saveValue(nts::Tristate::Undefined);

    i1.simulate(1);
    i2.simulate(1);
    comp.simulate(1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::Undefined);
}

TEST(elementaryComponentsXor, verifEqual) {
    nts::XorComp comp("xor");
    nts::Input i1("i1");
    nts::Input i2("i2");

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    i1.saveValue(nts::Tristate::True);
    i2.saveValue(nts::Tristate::True);

    i1.simulate(1);
    i2.simulate(1);
    comp.simulate(1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::False);
}

TEST(elementaryComponentsXor, verifEqual2) {
    nts::XorComp comp("xor");
    nts::Input i1("i1");
    nts::Input i2("i2");

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    i1.saveValue(nts::Tristate::False);
    i2.saveValue(nts::Tristate::False);

    i1.simulate(1);
    i2.simulate(1);
    comp.simulate(1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::False);
}


TEST(elementaryComponentsXor, verifTrue) {
    nts::XorComp comp("xor");
    nts::Input i1("i1");
    nts::Input i2("i2");

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    i1.saveValue(nts::Tristate::True);
    i2.saveValue(nts::Tristate::False);

    i1.simulate(1);
    i2.simulate(1);
    comp.simulate(1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::True);
}