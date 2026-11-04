#include "4011.hpp"
#include "ErrorHandling.hpp"
#include "IComponent.hpp"
#include "Input.hpp"
#include <gtest/gtest.h>

TEST(GatesComponents4011, badPins) {
    nts::Cd4011b comp("4011");

    EXPECT_THROW(comp.compute(1), NanoException);
}

TEST(GatesComponents4011, verifTrue) {
    nts::Cd4011b comp("4011");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::False);
    i2.saveValue(nts::Tristate::True);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::True);
}

TEST(GatesComponents4011, verifTrue2) {
    nts::Cd4011b comp("4011");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::False);
    i2.saveValue(nts::Tristate::Undefined);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::True);
}

TEST(GatesComponents4011, verifTrue3) {
    nts::Cd4011b comp("4011");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::True);
    i2.saveValue(nts::Tristate::False);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::True);
}

TEST(GatesComponents4011, verifTrue4) {
    nts::Cd4011b comp("4011");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::Undefined);
    i2.saveValue(nts::Tristate::False);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::True);
}

TEST(GatesComponents4011, verifFalse) {
    nts::Cd4011b comp("4011");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::True);
    i2.saveValue(nts::Tristate::True);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::False);
}

TEST(GatesComponents4011, verifUndefined) {
    nts::Cd4011b comp("4011");
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

TEST(GatesComponents4011, verifUndefined2) {
    nts::Cd4011b comp("4011");
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