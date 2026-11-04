#include <gtest/gtest.h>
#include "IComponent.hpp"
#include "False.hpp"

TEST(specialComponentsFalse, VerifFalse) {
    nts::FalseComp comp("false");

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(1), nts::Tristate::False);
}

TEST(specialComponentsFalse, ThrowsOnBadPin) {
    nts::FalseComp comp("false");

    EXPECT_THROW(comp.compute(2), NanoException);
}

TEST(specialComponentsFalse, CallSameTick)
{
    nts::gEvalId++;
    nts::FalseComp comp("false");
    nts::Tristate v1 = comp.compute(1);
    nts::Tristate v2 = comp.compute(1);

    nts::gEvalId++;
    EXPECT_EQ(v1, nts::Tristate::False);
    EXPECT_EQ(v2, nts::Tristate::False);
}