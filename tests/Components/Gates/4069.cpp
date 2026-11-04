#include "4069.hpp"
#include "ErrorHandling.hpp"
#include "IComponent.hpp"
#include "Input.hpp"
#include <gtest/gtest.h>

TEST(GatesComponents4069, badPins) {
    nts::Cd4069ubc comp("4069");

    EXPECT_THROW(comp.compute(1), NanoException);
}

TEST(GatesComponents4069, verifUndefined) {
    nts::Cd4069ubc comp("4069");
    nts::Input i1("i1");

    i1.saveValue(nts::Tristate::Undefined);

    i1.simulate(1);

    comp.setLink(1, i1, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(2), nts::Tristate::Undefined);
}

TEST(GatesComponents4069, verifTrue) {
    nts::Cd4069ubc comp("4069");
    nts::Input i1("i1");

    i1.saveValue(nts::Tristate::False);

    i1.simulate(1);

    comp.setLink(1, i1, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(2), nts::Tristate::True);
}

TEST(GatesComponents4069, verifFalse) {
    nts::Cd4069ubc comp("4069");
    nts::Input i1("i1");

    i1.saveValue(nts::Tristate::True);

    i1.simulate(1);

    comp.setLink(1, i1, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(2), nts::Tristate::False);
}