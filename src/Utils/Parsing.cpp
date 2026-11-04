#include "Parsing.hpp"
#include "ErrorHandling.hpp"
#include "IComponent.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

nts::Parsing::Parsing(std::string filePath) : _filePath(filePath), _factory() {}

void nts::Parsing::checkExt()
{
    size_t pos = _filePath.find_last_of('.');
    std::string ext = (pos == std::string::npos) ? "" : _filePath.substr(pos + 1);

    if (ext.empty() || ext != "nts")
        throw NanoException("Invalid file extension: expected .nts");

}

std::ifstream nts::Parsing::openFile()
{
    std::ifstream file(_filePath);

    if (!file.is_open())
        throw NanoException("Failed to open file: " + _filePath);

    return file;
}

std::pair<std::size_t, std::string> nts::Parsing::getData(std::string n)
{
    size_t pos_a = n.find(":");

    if (pos_a == std::string::npos) {
        throw NanoException("Invalid link syntax: expected component:pin");
    }
    std::string name = n.substr(0, pos_a);
    std::size_t pin = std::stoul(n.substr(pos_a + 1));

    return {pin, name};
}

std::unordered_map<std::string, std::unique_ptr<nts::IComponent>>& nts::Parsing::run()
{
    // Check Extensions of file (verif if the file over with .nts)
    this->checkExt();

    // OpenFile
    std::ifstream file = this->openFile();

    // Parse
    std::string line;

    Section section = Section::None;

    while (std::getline(file, line)) {
        size_t diezPos = line.find('#');
        if (diezPos != std::string::npos)
            line = line.substr(0, diezPos);
        
        std::stringstream ss(line);
        std::vector<std::string> tokens;
        std::string token;

        while (ss >> token)
            tokens.push_back(token);
        
        if (tokens.empty())
            continue;

        // Chipset Section
        if (tokens.size() == 1 && tokens[0] == ".chipsets:") {
            section = Section::Chipsets;
            continue;
        }

        // Links Section
        if (tokens.size() == 1 && tokens[0] == ".links:") {
            section = Section::Links;
            continue;
        }

        // Section Chipset
        if (section == Section::Chipsets) {
            if (tokens.size() != 2)
                throw NanoException("Invalid number of arguments in line: " + line);

            if (_factory.getComponents()[tokens[1]])
                throw NanoException("Duplicate component name: " + tokens[1]);
            
            _factory.getComponents()[tokens[1]] = _factory.createComponent(tokens[0], tokens[1]);
            continue;
        }
        // Secion Links
        if (section == Section::Links) {
            if (tokens.size() != 2) {
                throw NanoException("Link declaration must contain exactly two arguments: " + line);
            }
            auto [pin_a, name_a] = getData(tokens[0]);
            auto [pin_b, name_b] = getData(tokens[1]);
            
            nts::IComponent& obj_a = _factory.getComponent(name_a);
            nts::IComponent& obj_b = _factory.getComponent(name_b);
            
            obj_a.setLink(pin_a, obj_b, pin_b);
            obj_b.setLink(pin_b, obj_a, pin_a);
            continue;
        }
        throw NanoException("Invalid line: " + line);
    }
    return _factory.getComponents();
}