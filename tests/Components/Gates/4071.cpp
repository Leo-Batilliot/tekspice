#include "4071.hpp"
#include "ErrorHandling.hpp"
#include "IComponent.hpp"
#include "Input.hpp"
#include <gtest/gtest.h>

TEST(GatesComponents4071, badPins) {
    nts::Hef4071b comp("4071");

    EXPECT_THROW(comp.compute(1), NanoException);
}

TEST(GatesComponents4071, verifTrue) {
    nts::Hef4071b comp("4071");
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

TEST(GatesComponents4071, verifTrue2) {
    nts::Hef4071b comp("4071");
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

TEST(GatesComponents4071, verifTrue3) {
    nts::Hef4071b comp("4071");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::True);
    i2.saveValue(nts::Tristate::Undefined);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::True);
}

TEST(GatesComponents4071, verifTrue4) {
    nts::Hef4071b comp("4071");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::Undefined);
    i2.saveValue(nts::Tristate::True);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::True);
}

TEST(GatesComponents4071, verifFalse) {
    nts::Hef4071b comp("4071");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::False);
    i2.saveValue(nts::Tristate::False);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::False);
}


TEST(GatesComponents4071, verifUndefined) {
    nts::Hef4071b comp("4071");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::False);
    i2.saveValue(nts::Tristate::Undefined);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::Undefined);
}

TEST(GatesComponents4071, verifUndefined2) {
    nts::Hef4071b comp("4071");
    nts::Input i1("i1");
    nts::Input i2("i1");

    i1.saveValue(nts::Tristate::Undefined);
    i2.saveValue(nts::Tristate::False);

    i1.simulate(1);
    i2.simulate(1);

    comp.setLink(1, i1, 1);
    comp.setLink(2, i2, 1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(3), nts::Tristate::Undefined);
}