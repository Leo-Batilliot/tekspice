#include "Input.hpp"
#include <gtest/gtest.h>
#include "IComponent.hpp"
#include <gtest/gtest.h>

TEST(specialComponentsInput, Init) {
    nts::Input comp("input");

    EXPECT_EQ(comp.compute(1), nts::Tristate::Undefined);
}

TEST(specialComponentsInput, WithOneTick) {
    nts::Input comp("input");

    comp.saveValue(nts::Tristate::True);
    comp.simulate(1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(1), nts::Tristate::True);
}

TEST(specialComponentsInput, ThrowsOnBadPin) {
    nts::Input comp("comp");

    EXPECT_THROW(comp.compute(2), NanoException);
}

TEST(Input, CacheSameTickAndUpdateNextTick)
{
    nts::Input comp("comp");

    comp.saveValue(nts::Tristate::True);
    comp.simulate(1);

    nts::gEvalId++;
    nts::Tristate v1 = comp.compute(1);
    nts::Tristate v2 = comp.compute(1);
    EXPECT_EQ(v1, v2);
    EXPECT_EQ(v1, nts::Tristate::True);

    comp.saveValue(nts::Tristate::False);
    comp.simulate(2);

    nts::gEvalId++;
    nts::Tristate v3 = comp.compute(1);
    EXPECT_EQ(v3, nts::Tristate::False);
}

