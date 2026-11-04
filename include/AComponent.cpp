#include "AComponent.hpp"
#include "ErrorHandling.hpp"
#include "IComponent.hpp"

void nts::AComponent::simulate(std::size_t tick)
{
    (void)tick;
}

void nts::AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    if (_links.count(pin) == 0)
        throw NanoException("Pin is not in the list of available pins for this component");
    _links[pin].push_back(Link(otherPin, &other));
}

nts::Tristate nts::AComponent::getLink(std::size_t pin)
{
    auto it = _links.find(pin);

    if (it == _links.end())
        return nts::Undefined;

    nts::Tristate value = nts::Undefined;

    for (auto &tmp : it->second) {
        nts::Tristate check = tmp.getLinkedComponent()->compute(tmp.getPinNumber());

        if (check == nts::Undefined)
            continue;

        if (value == nts::Undefined) {
            value = check;
            continue;
        }
        if (check != value)
            throw NanoException("All output pins connected to this pin must have the same tristate value");
    }
    return value;
}
