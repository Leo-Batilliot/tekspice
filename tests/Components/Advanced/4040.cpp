#include "4040.hpp"
#include "ErrorHandling.hpp"
#include "IComponent.hpp"
#include "Input.hpp"
#include <gtest/gtest.h>


TEST(advancedComponents4040, badPins) {
    nts::Mc14040b comp("4040");

    EXPECT_THROW(comp.compute(8), NanoException);
}

TEST(advancedComponents4040, resetTest) {
    nts::Mc14040b comp("4040");
    nts::Input clock("clock");
    nts::Input reset("reset");

    comp.setLink(10, clock, 1);
    comp.setLink(11, reset, 1);

    clock.saveValue(nts::Tristate::False);
    reset.saveValue(nts::Tristate::True);

    clock.simulate(1);
    reset.simulate(1);
    comp.simulate(1);

    nts::gEvalId++;
    comp.simulate(1);
    EXPECT_EQ(comp.compute(9), nts::Tristate::False);
    comp.simulate(1);
    EXPECT_EQ(comp.compute(7), nts::Tristate::False);
    comp.simulate(1);
    EXPECT_EQ(comp.compute(1), nts::Tristate::False);
}

extern std::size_t nts::gEvalId;

TEST(advancedComponents4040, testFrontDescendant) {
    nts::Mc14040b comp("4040");
    nts::Input clock("clock");
    nts::Input reset("reset");

    comp.setLink(10, clock, 1);
    comp.setLink(11, reset, 1);

    reset.saveValue(nts::Tristate::False);
    reset.simulate(1);

    clock.saveValue(nts::Tristate::True);
    clock.simulate(1);

    nts::gEvalId++;
    comp.simulate(1);

    clock.saveValue(nts::Tristate::False);
    clock.simulate(1);

    nts::gEvalId++;
    comp.simulate(1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(9), nts::Tristate::True);
}

TEST(advancedComponents4040, clockUndefined) {
    nts::Mc14040b comp("4040");
    nts::Input clock("clock");
    nts::Input reset("reset");

    comp.setLink(10, clock, 1);
    comp.setLink(11, reset, 1);

    reset.saveValue(nts::Tristate::False);
    reset.simulate(1);

    clock.saveValue(nts::Tristate::Undefined);
    clock.simulate(1);
    comp.simulate(1);

    comp.simulate(2);
    nts::gEvalId++;
    EXPECT_EQ(comp.compute(9), nts::Tristate::False);
}