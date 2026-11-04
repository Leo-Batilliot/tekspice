#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <filesystem>
#include "Parsing.hpp"
#include "ErrorHandling.hpp"

static void writeFile(const std::string &path, const std::string &content)
{
    std::ofstream file(path);
    ASSERT_TRUE(file.is_open());
    file << content;
}

TEST(ParsingTest, InvalidExtensionThrows)
{
    nts::Parsing parsing("test.txt");
    EXPECT_THROW(parsing.run(), NanoException);
}

TEST(ParsingTest, MissingFileThrows)
{
    nts::Parsing parsing("missing_file.nts");
    EXPECT_THROW(parsing.run(), NanoException);
}

TEST(ParsingTest, ValidFileParsesSuccessfully)
{
    const std::string path = "valid_test.nts";

    writeFile(path,
        ".chipsets:\n"
        "input a\n"
        "input b\n"
        "and gate\n"
        "output out\n"
        "\n"
        ".links:\n"
        "a:1 gate:1\n"
        "b:1 gate:2\n"
        "gate:3 out:1\n"
    );

    nts::Parsing parsing(path);

    EXPECT_NO_THROW({
        auto &components = parsing.run();
        EXPECT_FALSE(components.empty());
        EXPECT_EQ(components.size(), 4);
    });

    std::filesystem::remove(path);
}

TEST(ParsingTest, DuplicateComponentNameThrows)
{
    const std::string path = "duplicate_test.nts";

    writeFile(path,
        ".chipsets:\n"
        "input a\n"
        "output a\n"
    );

    nts::Parsing parsing(path);

    EXPECT_THROW(parsing.run(), NanoException);

    std::filesystem::remove(path);
}

TEST(ParsingTest, InvalidLinkSyntaxThrows)
{
    const std::string path = "bad_link_syntax.nts";

    writeFile(path,
        ".chipsets:\n"
        "input a\n"
        "output out\n"
        "\n"
        ".links:\n"
        "a out:1\n"
    );

    nts::Parsing parsing(path);

    EXPECT_THROW(parsing.run(), NanoException);

    std::filesystem::remove(path);
}

TEST(ParsingTest, InvalidChipsetDeclarationThrows)
{
    const std::string path = "bad_chipset.nts";

    writeFile(path,
        ".chipsets:\n"
        "input a extra\n"
    );

    nts::Parsing parsing(path);

    EXPECT_THROW(parsing.run(), NanoException);

    std::filesystem::remove(path);
}

TEST(ParsingTest, InvalidLinkDeclarationThrows)
{
    const std::string path = "bad_links.nts";

    writeFile(path,
        ".chipsets:\n"
        "input a\n"
        "output out\n"
        "\n"
        ".links:\n"
        "a:1 out:1 extra\n"
    );

    nts::Parsing parsing(path);

    EXPECT_THROW(parsing.run(), NanoException);

    std::filesystem::remove(path);
}

TEST(ParsingTest, InvalidLineThrows)
{
    const std::string path = "invalid_line.nts";

    writeFile(path, "bonjour\n");

    nts::Parsing parsing(path);

    EXPECT_THROW(parsing.run(), NanoException);

    std::filesystem::remove(path);
}