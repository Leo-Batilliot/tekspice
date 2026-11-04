#include "4017.hpp"
#include "ErrorHandling.hpp"
#include "IComponent.hpp"
#include "Input.hpp"
#include <gtest/gtest.h>

TEST(advancedComponents4017, badPins) {
    nts::Hc4017 comp("4017");

    EXPECT_THROW(comp.compute(8), NanoException);
}

TEST(advancedComponents4017, resetTest) {
    nts::Hc4017 comp("4017");
    nts::Input mr("mr"), cp0("cp0"), cp1("cp1");

    comp.setLink(15, mr, 1);
    comp.setLink(14, cp0, 1);
    comp.setLink(13, cp1, 1);

    cp1.saveValue(nts::Tristate::False);
    cp1.simulate(1);
    cp0.saveValue(nts::Tristate::False);
    cp0.simulate(1);
    mr.saveValue(nts::Tristate::True);
    mr.simulate(1);

    comp.simulate(1);

    nts::gEvalId++;
    comp.simulate(2);
    EXPECT_EQ(comp.compute(3), nts::Tristate::True);  // Q0
    comp.simulate(2); 
    EXPECT_EQ(comp.compute(2), nts::Tristate::False); // Q1
    comp.simulate(2); 
    EXPECT_EQ(comp.compute(4), nts::Tristate::False); // Q2
    comp.simulate(2); 
    EXPECT_EQ(comp.compute(7), nts::Tristate::False); // Q3
    comp.simulate(2); 
    EXPECT_EQ(comp.compute(10),nts::Tristate::False); // Q4
    comp.simulate(2); 
    EXPECT_EQ(comp.compute(1), nts::Tristate::False); // Q5
    comp.simulate(2); 
    EXPECT_EQ(comp.compute(5), nts::Tristate::False); // Q6
    comp.simulate(2); 
    EXPECT_EQ(comp.compute(6), nts::Tristate::False); // Q7
    comp.simulate(2); 
    EXPECT_EQ(comp.compute(9), nts::Tristate::False); // Q8
    comp.simulate(2); 
    EXPECT_EQ(comp.compute(11),nts::Tristate::False); // Q9
}

TEST(advancedComponents4017, oneUp) {
    nts::Hc4017 comp("4017");
    nts::Input mr("mr");
    nts::Input cp0("cp0");
    nts::Input cp1("cp1");

    comp.setLink(15, mr, 1);
    comp.setLink(14, cp0, 1);
    comp.setLink(13, cp1, 1);

    cp1.saveValue(nts::Tristate::False);
    cp1.simulate(1);

    cp0.saveValue(nts::Tristate::False);
    cp0.simulate(1);

    mr.saveValue(nts::Tristate::True);
    mr.simulate(1);

    nts::gEvalId++;
    comp.simulate(1);

    mr.saveValue(nts::Tristate::False);
    mr.simulate(2);

    nts::gEvalId++;
    comp.simulate(2);

    cp0.saveValue(nts::Tristate::False);
    cp0.simulate(3);

    nts::gEvalId++;
    comp.simulate(3);

    cp0.saveValue(nts::Tristate::True);
    cp0.simulate(4);

    nts::gEvalId++;
    comp.simulate(4);

    cp0.saveValue(nts::Tristate::False);
    cp0.simulate(5);

    nts::gEvalId++;
    comp.simulate(5);

    nts::gEvalId++;
    EXPECT_EQ(comp.compute(2), nts::Tristate::True);
    EXPECT_EQ(comp.compute(3), nts::Tristate::False);
}