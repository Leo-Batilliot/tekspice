#include "Clock.hpp"
#include <gtest/gtest.h>
#include "IComponent.hpp"
#include <gtest/gtest.h>

TEST(specialComponentsClock, Init) {
    nts::Clock comp("clock");

    EXPECT_EQ(comp.compute(1), nts::Tristate::Undefined);
}

TEST(specialComponentsClock, WithOneTick) {
    nts::gEvalId++;
    nts::Clock comp("clock");

    EXPECT_EQ(comp.compute(1), nts::Tristate::Undefined);
    nts::gEvalId++;
    comp.saveValue(nts::Tristate::True);
    comp.simulate(1);

    EXPECT_EQ(comp.compute(1), nts::Tristate::True);
    nts::gEvalId++;
    comp.simulate(1);
    EXPECT_EQ(comp.compute(1), nts::Tristate::False);
}

TEST(specialComponentsClock, ThrowsOnBadPin) {
    nts::Clock comp("clock");

    EXPECT_THROW(comp.compute(2), NanoException);
}