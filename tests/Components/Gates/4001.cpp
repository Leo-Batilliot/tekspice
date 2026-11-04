#include "4001.hpp"
#include "IComponent.hpp"
#include "Input.hpp"
#include <gtest/gtest.h>

TEST(GatesComponents4001, badPins) {
    nts::Hef4001b comp("4001");

    EXPECT_THROW(comp.compute(1), NanoException);
}

TEST(GatesComponents4001, verifTrue) {

    nts::Hef4001b comp("4001");
    nts::Input i1("i1");
    nts::Input i2("i2");

    i1.saveValue(nts::Tristate::False);
    i2.saveValue(nts::Tristate::False);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::True);
}

TEST(GatesComponents4001, verifFalse) {

    nts::Hef4001b comp("4001");
    nts::Input i1("i1");
    nts::Input i2("i2");

    i1.saveValue(nts::Tristate::True);
    i2.saveValue(nts::Tristate::False);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::False);
}

TEST(GatesComponents4001, verifFalse2) {

    nts::Hef4001b comp("4001");
    nts::Input i1("i1");
    nts::Input i2("i2");

    i1.saveValue(nts::Tristate::False);
    i2.saveValue(nts::Tristate::True);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::False);
}

TEST(GatesComponents4001, verifUndefined) {

    nts::Hef4001b comp("4001");
    nts::Input i1("i1");
    nts::Input i2("i2");

    i1.saveValue(nts::Tristate::Undefined);
    i2.saveValue(nts::Tristate::False);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::Undefined);
}