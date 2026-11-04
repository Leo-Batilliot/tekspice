#pragma once

#include "IComponent.hpp"
#include <cstddef>
#include <unordered_map>
#include <vector>
#include "ErrorHandling.hpp"

namespace nts {

extern std::size_t gEvalId;

class Link {
public:
    Link(std::size_t pin, nts::IComponent *component) : _otherPinNumber(pin), _linkedComponent(component) {};

    std::size_t getPinNumber() { return _otherPinNumber; };
    nts::IComponent *getLinkedComponent() { return _linkedComponent; };
private:
    std::size_t _otherPinNumber;
    nts::IComponent *_linkedComponent;
};

class AComponent : public IComponent {
    public:
        AComponent(std::string name, std::size_t nb_links)
            : _lastEvalIds(nb_links + 1, 0),
              _lastReturnValues(nb_links + 1, nts::Tristate::Undefined),
              _name(std::move(name))
        {
            for (std::size_t i = 1; i <= nb_links; i++) {
                _links.emplace(i, std::vector<Link>{});
            }
        };

        void simulate(std::size_t tick) override;
        virtual nts::Tristate compute(std::size_t pin) override = 0;
        void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) override;

        nts::Tristate getLink(std::size_t pin);
    protected:
        std::vector<std::size_t> _lastEvalIds;
        std::vector<nts::Tristate> _lastReturnValues;
        std::unordered_map<std::size_t, std::vector<Link>> _links;
        std::string _name;

        bool shouldCompute(std::size_t pin) {
            if (_lastEvalIds[pin] == gEvalId)
                return false;
            _lastEvalIds[pin] = gEvalId;
            return true;
        }
        nts::Tristate cachedValue(std::size_t pin) const {
            return _lastReturnValues[pin];
        }
        void storeValue(std::size_t pin, nts::Tristate v) {
            _lastReturnValues[pin] = v;
        }
};

}