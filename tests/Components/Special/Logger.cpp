#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <vector>

#include "Components/Special/Logger.hpp"
#include "Components/Special/Input.hpp"
#include "Components/Special/Clock.hpp"

static unsigned char readFile(const std::string& path)
{
    std::ifstream file(path, std::ios::binary);

    unsigned char byte = 0;
    file.read(reinterpret_cast<char*>(&byte), 1);
    return byte;
}

TEST(Logger, LoggerTest)
{
    std::remove("log.bin");

    nts::logger log("log");

    std::vector<nts::Input> bits;
    bits.reserve(8);
    for (int i = 0; i < 8; ++i)
        bits.emplace_back("b" + std::to_string(i));

    nts::Clock clock("clock");
    nts::Input in("in");

    for (int i = 0; i < 8; ++i)
        log.setLink(i + 1, bits[i], 1);

    log.setLink(9, clock, 1);
    log.setLink(10, in, 1);

    nts::gEvalId++;

    for (int i = 0; i < 8; i++)
        bits[i].saveValue((5 >> i) & 1 ? nts::Tristate::True : nts::Tristate::False);

    for (auto& b : bits)
        b.simulate(1);

    in.saveValue(nts::Tristate::False);
    in.simulate(1);

    clock.saveValue(nts::Tristate::False);
    clock.simulate(1);

    log.simulate(1);

    nts::gEvalId++;

    clock.saveValue(nts::Tristate::True);
    clock.simulate(2);
    log.simulate(2);

    EXPECT_EQ(readFile("log.bin"), 5);

    std::remove("log.bin");
}