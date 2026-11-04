#include "And.hpp"
#include "IComponent.hpp"
#include "Input.hpp"
#include <gtest/gtest.h>

TEST(elementaryComponentsAnd, badPins) {
    nts::And comp("and");

    EXPECT_THROW(comp.compute(1), NanoException);
}

TEST(elementaryComponentsAnd, verifTrue) {
    nts::And comp("and");
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
    EXPECT_EQ(comp.compute(3), nts::Tristate::True);
}

TEST(elementaryComponentsAnd, verifFalse) {
    nts::And comp("and");
    nts::Input i1("i1");
    nts::Input i2("i2");

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    i1.saveValue(nts::Tristate::False);
    i2.saveValue(nts::Tristate::True);

    i1.simulate(1);
    i2.simulate(1);
    comp.simulate(1);

    nts::gEvalId++; 
    EXPECT_EQ(comp.compute(3), nts::Tristate::False);
}

TEST(elementaryComponentsAnd, verifUndefined) {
    nts::And comp("and");
    nts::Input i1("i1");
    nts::Input i2("i2");

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    i1.saveValue(nts::Tristate::Undefined);
    i2.saveValue(nts::Tristate::Undefined);

    i1.simulate(1);
    i2.simulate(1);
    comp.simulate(1);

    nts::gEvalId++; 
    EXPECT_EQ(comp.compute(3), nts::Tristate::Undefined);
}

TEST(elementaryComponentsAnd, verifOneUndefined) {
    nts::And comp("and");
    nts::Input i1("i1");
    nts::Input i2("i2");

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    i1.saveValue(nts::Tristate::False);
    i2.saveValue(nts::Tristate::Undefined);

    i1.simulate(1);
    i2.simulate(1);
    comp.simulate(1);

    nts::gEvalId++; 
    EXPECT_EQ(comp.compute(3), nts::Tristate::False);
}