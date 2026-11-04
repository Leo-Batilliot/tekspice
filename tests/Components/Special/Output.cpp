#include "OutPut.hpp"
#include <gtest/gtest.h>
#include "IComponent.hpp"
#include "Input.hpp"
#include <gtest/gtest.h>

TEST(specialComponentsOutput, Init) {
    nts::OutPut comp("output");

    EXPECT_EQ(comp.compute(1), nts::Tristate::Undefined);
}

TEST(SpecialComponentsOutput, ReadsInputValue)
{
    nts::OutPut out("out");
    nts::Input in("in");

    nts::gEvalId++;
    out.setLink(1, in, 1);
    in.setLink(1, out, 1);

    in.saveValue(nts::Tristate::True);
    in.simulate(1);
    out.simulate(1);

    EXPECT_EQ(out.compute(1), nts::Tristate::True);

    in.saveValue(nts::Tristate::False);
    in.simulate(2);
    out.simulate(2);

    nts::gEvalId++;
    EXPECT_EQ(out.compute(1), nts::Tristate::False);
}

TEST(specialComponentsOutput, ThrowsOnBadPin) {
    nts::OutPut comp("output");

    EXPECT_THROW(comp.compute(2), NanoException);
}