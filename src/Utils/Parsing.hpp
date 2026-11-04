#ifndef PARSING_HPP
#define PARSING_HPP

#include <cstddef>
#include <fstream>
#include <iostream>
#include <utility>
#include "Factory/Factory.hpp"

namespace nts {

class Parsing {
public:
    Parsing(std::string filePath);

    void checkExt();
    std::ifstream openFile();

    std::pair<std::size_t, std::string> getData(std::string);

    std::unordered_map<std::string, std::unique_ptr<nts::IComponent>>& run();

private:
    std::string _filePath;
    Factory _factory;
    enum class Section { None, Chipsets, Links };
};

}

#endif