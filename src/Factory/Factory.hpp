#pragma once

#include <functional>
#include <map>
#include <memory>
#include "IComponent.hpp"
#include <unordered_map>
#include <string>

namespace nts {

class Factory {
public:
    Factory();
    std::unique_ptr<IComponent> createComponent(const std::string &type, const std::string &name) const;

    std::unordered_map<std::string, std::unique_ptr<nts::IComponent>>& getComponents() { return _components; }

    nts::IComponent& getComponent(const std::string& name);

private:
    std::map<std::string, std::function<std::unique_ptr<IComponent>(const std::string&)>> _factory;
    std::unordered_map<std::string, std::unique_ptr<nts::IComponent>> _components;
};
}