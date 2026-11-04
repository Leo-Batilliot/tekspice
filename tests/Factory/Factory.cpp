#include <gtest/gtest.h>
#include "Factory.hpp"
#include "ErrorHandling.hpp"
#include "IComponent.hpp"

TEST(FactoryTest, CreateValidInputComponent)
{
    nts::Factory factory;

    auto comp = factory.createComponent("input", "a");

    ASSERT_NE(comp, nullptr);
}

TEST(FactoryTest, CreateValidAndComponent)
{
    nts::Factory factory;

    auto comp = factory.createComponent("and", "gate");

    ASSERT_NE(comp, nullptr);
}

TEST(FactoryTest, CreateUnknownComponentThrows)
{
    nts::Factory factory;

    EXPECT_THROW(factory.createComponent("unknown_type", "x"), NanoException);
}

TEST(FactoryTest, CreateUnknownComponentThrowsWithCorrectMessage)
{
    nts::Factory factory;

    try {
        factory.createComponent("unknown_type", "x");
        FAIL() << "Expected NanoException";
    } catch (const NanoException &e) {
        EXPECT_STREQ("Unknown component type: unknown_type (x)", e.what());
    }
}

TEST(FactoryTest, GetUnknownComponentThrows)
{
    nts::Factory factory;

    EXPECT_THROW(factory.getComponent("missing"), NanoException);
}

TEST(FactoryTest, GetExistingComponent)
{
    nts::Factory factory;

    factory.getComponents()["a"] = factory.createComponent("input", "a");

    nts::IComponent &comp = factory.getComponent("a");

    EXPECT_NE(&comp, nullptr);
}