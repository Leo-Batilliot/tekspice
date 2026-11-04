#include "4030.hpp"
#include "ErrorHandling.hpp"
#include "Input.hpp"
#include <gtest/gtest.h>

TEST(GatesComponents4030, badPins) {
    nts::Cd4030c comp("4030");

    EXPECT_THROW(comp.compute(1), NanoException);
}

TEST(GatesComponents4030, verifUndefined) {

    nts::Cd4030c comp("4030");
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

TEST(GatesComponents4030, verifUndefined2) {

    nts::Cd4030c comp("4030");
    nts::Input i1("i1");
    nts::Input i2("i2");

    i1.saveValue(nts::Tristate::False);
    i2.saveValue(nts::Tristate::Undefined);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::Undefined);
}

TEST(GatesComponents4030, verifUndefined3) {

    nts::Cd4030c comp("4030");
    nts::Input i1("i1");
    nts::Input i2("i2");

    i1.saveValue(nts::Tristate::Undefined);
    i2.saveValue(nts::Tristate::True);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::Undefined);
}

TEST(GatesComponents4030, verifUndefined4) {

    nts::Cd4030c comp("4030");
    nts::Input i1("i1");
    nts::Input i2("i2");

    i1.saveValue(nts::Tristate::True);
    i2.saveValue(nts::Tristate::Undefined);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::Undefined);
}

TEST(GatesComponents4030, verifFalse) {

    nts::Cd4030c comp("4030");
    nts::Input i1("i1");
    nts::Input i2("i2");

    i1.saveValue(nts::Tristate::True);
    i2.saveValue(nts::Tristate::True);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::False);
}

TEST(GatesComponents4030, verifFalse2) {

    nts::Cd4030c comp("4030");
    nts::Input i1("i1");
    nts::Input i2("i2");

    i1.saveValue(nts::Tristate::False);
    i2.saveValue(nts::Tristate::False);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::False);
}

TEST(GatesComponents4030, verifTrue) {

    nts::Cd4030c comp("4030");
    nts::Input i1("i1");
    nts::Input i2("i2");

    i1.saveValue(nts::Tristate::True);
    i2.saveValue(nts::Tristate::False);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::True);
}

TEST(GatesComponents4030, verifTrue2) {

    nts::Cd4030c comp("4030");
    nts::Input i1("i1");
    nts::Input i2("i2");

    i1.saveValue(nts::Tristate::False);
    i2.saveValue(nts::Tristate::True);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::True);
}