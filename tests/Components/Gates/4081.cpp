#include "4081.hpp"
#include "ErrorHandling.hpp"
#include "IComponent.hpp"
#include "Input.hpp"
#include <gtest/gtest.h>

TEST(GatesComponents4081, badPins) {
    nts::Hcf4081b comp("4081");

    EXPECT_THROW(comp.compute(1), NanoException);
}

TEST(GatesComponents4081, verifTrue) {
    nts::Hcf4081b comp("4081");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::True);
    i2.saveValue(nts::Tristate::True);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::True);
}

TEST(GatesComponents4081, verifFalse) {
    nts::Hcf4081b comp("4081");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::False);
    i2.saveValue(nts::Tristate::True);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::False);
}

TEST(GatesComponents4081, verifFalse2) {
    nts::Hcf4081b comp("4081");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::True);
    i2.saveValue(nts::Tristate::False);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::False);
}


TEST(GatesComponents4081, verifFalse3) {
    nts::Hcf4081b comp("4081");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::False);
    i2.saveValue(nts::Tristate::Undefined);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::False);
}

TEST(GatesComponents4081, verifFalse4) {
    nts::Hcf4081b comp("4081");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::Undefined);
    i2.saveValue(nts::Tristate::False);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::False);
}

TEST(GatesComponents4081, verifUndefined) {
    nts::Hcf4081b comp("4081");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::True);
    i2.saveValue(nts::Tristate::Undefined);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::Undefined);
}

TEST(GatesComponents4081, verifUndefined2) {
    nts::Hcf4081b comp("4081");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::Undefined);
    i2.saveValue(nts::Tristate::True);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::Undefined);
}