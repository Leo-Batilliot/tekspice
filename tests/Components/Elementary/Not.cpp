#include "Not.hpp"
#include "IComponent.hpp"
#include "Input.hpp"
#include <gtest/gtest.h>

TEST(elementaryComponentsNot, badPins) {
    nts::Not comp("not");

    EXPECT_THROW(comp.compute(1), NanoException);
}

TEST(elementaryComponentsNot, verifTrue) {
    nts::Not comp("not");
    nts::Input i1("i1");

    comp.setLink(1, i1, 1);

    i1.saveValue(nts::Tristate::False);

    i1.simulate(1);
    comp.simulate(1);

    nts::gEvalId++; 
    EXPECT_EQ(comp.compute(2), nts::Tristate::True);
}

TEST(elementaryComponentsNot, verifFalse) {
    nts::Not comp("not");
    nts::Input i1("i1");

    comp.setLink(1, i1, 1);

    i1.saveValue(nts::Tristate::True);

    i1.simulate(1);
    comp.simulate(1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(2), nts::Tristate::False);
}

TEST(elementaryComponentsNot, verifUndefined) {
    nts::Not comp("not");
    nts::Input i1("i1");

    comp.setLink(1, i1, 1);

    i1.saveValue(nts::Tristate::Undefined);

    i1.simulate(1);
    comp.simulate(1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(2), nts::Tristate::Undefined);
}
