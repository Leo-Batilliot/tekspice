#include <gtest/gtest.h>
#include "IComponent.hpp"
#include "True.hpp"

TEST(specialComponentsTrue, VerifTrue) {
    nts::TrueComp comp("true");

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(1), nts::Tristate::True);
}

TEST(specialComponentsTrue, BadPinThrows)
{
    nts::TrueComp comp("true");

    EXPECT_THROW(comp.compute(2), NanoException);
}

TEST(specialComponentsTrue, CallSameTick)
{
    nts::gEvalId++;
    nts::TrueComp comp("true");
    nts::Tristate v1 = comp.compute(1);
    nts::Tristate v2 = comp.compute(1);

    nts::gEvalId++;
    EXPECT_EQ(v1, nts::Tristate::True);
    EXPECT_EQ(v2, nts::Tristate::True);
}
