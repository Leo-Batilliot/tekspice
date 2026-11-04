#include "4512.hpp"
#include "IComponent.hpp"
#include "Input.hpp"
#include <gtest/gtest.h>

TEST(advancedComponents4512, badPins) {
    nts::Cd4512bm comp("4512");

    EXPECT_EQ(comp.compute(1), nts::Tristate::Undefined);
}

TEST(advancedComponents4512, oeDisable) {
    nts::Cd4512bm comp("4512");
    nts::Input oe("oe");

    // SetLink
    comp.setLink(15, oe, 1);

    // SaveValue + simulate
    oe.saveValue(nts::Tristate::True);
    oe.simulate(1);

    comp.simulate(1);

    EXPECT_EQ(comp.compute(14), nts::Tristate::Undefined);
}


TEST(advancedComponents4512, inhibitDisable) {
    nts::Cd4512bm comp("4512");
    nts::Input ih("inhibit");
    nts::Input oe("oe");

    // SetLink
    comp.setLink(10, ih, 1);
    comp.setLink(15, oe, 1);


    // SaveValue + simulate
    ih.saveValue(nts::Tristate::True);
    oe.saveValue(nts::Tristate::False);
    ih.simulate(1);
    oe.simulate(1);

    comp.simulate(1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(14), nts::Tristate::False);
}

TEST(advancedComponents4512, selectIndex5ReadsX5) {
    nts::Cd4512bm comp("4512");

    // Init
    nts::Input oe("oe");
    nts::Input ih("inh");
    nts::Input a("a");
    nts::Input b("b");
    nts::Input c("c");
    nts::Input x5("x5");

    // OE actif
    comp.setLink(15, oe, 1);
    oe.saveValue(nts::Tristate::False);

    // INHIBIT = False
    comp.setLink(10, ih, 1);
    ih.saveValue(nts::Tristate::False);

    // 101 -> x5
    comp.setLink(11, a, 1);
    a.saveValue(nts::Tristate::True);
    comp.setLink(12, b, 1);
    b.saveValue(nts::Tristate::False);
    comp.setLink(13, c, 1);
    c.saveValue(nts::Tristate::True);

    // set X5
    comp.setLink(6, x5, 1);
    x5.saveValue(nts::Tristate::True);

    // Simulate
    oe.simulate(1);
    ih.simulate(1);
    a.simulate(1);
    b.simulate(1);
    c.simulate(1);
    x5.simulate(1);
    comp.simulate(1);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(14), nts::Tristate::True);
}