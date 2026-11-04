#include <memory>
#include "Factory.hpp"
#include "ErrorHandling.hpp"

// Include objet
#include "4013.hpp"
#include "4081.hpp"
#include "Input.hpp"
#include "OutPut.hpp"
#include "Logger.hpp"
#include "True.hpp"
#include "False.hpp"
#include "Clock.hpp"
#include "And.hpp"
#include "Or.hpp"
#include "Xor.hpp"
#include "Not.hpp"
#include "4001.hpp"
#include "4011.hpp"
#include "4030.hpp"
#include "4069.hpp"
#include "4071.hpp"
#include "4008.hpp"
#include "4017.hpp"
#include "4040.hpp"
#include "4094.hpp"
#include "4512.hpp"
#include "4514.hpp"
#include "4801.hpp"
#include "2716.hpp"

namespace nts {

Factory::Factory()
{
    // Special Components
    _factory["input"] = [](const std::string &name) { return std::make_unique<Input>(name); };
    _factory["output"] = [](const std::string &name) { return std::make_unique<OutPut>(name); };
    _factory["true"] = [](const std::string &name) { return std::make_unique<TrueComp>(name); };
    _factory["false"] = [](const std::string &name) { return std::make_unique<FalseComp>(name); };
    _factory["clock"] = [](const std::string &name) { return std::make_unique<Clock>(name); };
    _factory["logger"] = [](const std::string &name) { return std::make_unique<logger>(name); };

    // Elementary components
    _factory["and"] = [](const std::string &name) { return std::make_unique<And>(name); };
    _factory["or"] = [](const std::string &name) { return std::make_unique<Or>(name); };
    _factory["xor"] = [](const std::string &name) { return std::make_unique<XorComp>(name); };
    _factory["not"] = [](const std::string &name) { return std::make_unique<Not>(name); };

    // Gates components
    _factory["4001"] = [](const std::string &name) { return std::make_unique<Hef4001b>(name); };
    _factory["4011"] = [](const std::string &name) { return std::make_unique<Cd4011b>(name); };
    _factory["4030"] = [](const std::string &name) { return std::make_unique<Cd4030c>(name); };
    _factory["4069"] = [](const std::string &name) { return std::make_unique<Cd4069ubc>(name); };
    _factory["4071"] = [](const std::string &name) { return std::make_unique<Hef4071b>(name); };
    _factory["4081"] = [](const std::string &name) { return std::make_unique<Hcf4081b>(name); };

    // Advanced components
    _factory["4008"] = [](const std::string &name) { return std::make_unique<Cd4008bms>(name); };
    _factory["4013"] = [](const std::string &name) { return std::make_unique<Cd4013bc>(name); };
    _factory["4017"] = [](const std::string &name) { return std::make_unique<Hc4017>(name); };
    _factory["4040"] = [](const std::string &name) { return std::make_unique<Mc14040b>(name); };
    _factory["4094"] = [](const std::string &name) { return std::make_unique<Cd4094bc>(name); };
    _factory["4512"] = [](const std::string &name) { return std::make_unique<Cd4512bm>(name); };
    _factory["4514"] = [](const std::string &name) { return std::make_unique<Cd4514bc>(name); };
    _factory["4801"] = [](const std::string &name) { return std::make_unique<Mk4801a>(name); };
    _factory["2716"] = [](const std::string &name) { return std::make_unique<Mm2716e>(name); };
}

std::unique_ptr<IComponent> Factory::createComponent(const std::string &type, const std::string &name) const
{
    auto it = _factory.find(type);

    if (it == _factory.end())
        throw NanoException("Unknown component type: " + type + " (" + name + ")");
    return it->second(name);
}

nts::IComponent& Factory::getComponent(const std::string& name)
{
    auto it = _components.find(name);
    
    if (it == _components.end() || it->second == nullptr)
        throw NanoException("Unknown component: " + name);
    return *it->second;
}

}
