#include "Component.hpp"
#include <cmath>
#include "Config.hpp"

Component::Component(const std::string& name, sf::Vector2f pos, const sf::Font& font)
    : _position(pos), 
      _label(font, name, 15), 
      _typeName(name) {
}

void Component::initGeometry() {
    float textWidth = _label.getLocalBounds().size.x;
    float width = std::max(MIN_COMPONENT_WIDTH, textWidth + 30.f);

    size_t maxPorts = std::max(inputs.size(), outputs.size());
    float height = MIN_COMPONENT_HEIGHT + (maxPorts > 1 ? (maxPorts - 1) * COMPONENT_HEIGHT_PER_PIN : 0.f);

    _size = {width, height};
    _body.setSize(_size);
    _body.setPosition(_position);
    _body.setFillColor(COMPONENT_FILL_COLOR);
    _body.setOutlineThickness(COMPONENT_OUTLINE_THICKNESS);
    _body.setOutlineColor(COMPONENT_OUTLINE_COLOR);

    sf::FloatRect textBounds = _label.getLocalBounds();
    _label.setOrigin({textBounds.position.x + textBounds.size.x / 2.f, 
                       textBounds.position.y + textBounds.size.y / 2.f});
    _label.setPosition(_position + _size / 2.f);

    auto alignPorts = [&](std::vector<Port>& ports, float xOffset) {
        float spacing = _size.y / (ports.size() + 1);
        for (size_t i = 0; i < ports.size(); ++i) {
            ports[i].relativePos = {xOffset, spacing * (i + 1)};
            ports[i].shape.setRadius(PINS_RADIUS);
            ports[i].shape.setOrigin({5.f, 5.f});
            ports[i].shape.setPosition(_position + ports[i].relativePos);
            ports[i].shape.setFillColor(getPinColor(ports[i].state));
            ports[i].shape.setOutlineThickness(PINS_OUTLINE_THICKNESS);
            ports[i].shape.setOutlineColor(PINS_OUTLINE_COLOR);
        }
    };

    alignPorts(inputs, 0.f);
    alignPorts(outputs, _size.x);
}

void Component::render(sf::RenderWindow& window) {
    renderWithStates(window, sf::RenderStates::Default);
}

void Component::renderWithStates(sf::RenderWindow& window, sf::RenderStates states) {
    window.draw(_body, states);
    window.draw(_label, states);
    for (auto& p : inputs) window.draw(p.shape, states);
    for (auto& p : outputs) window.draw(p.shape, states);
}

void Component::setPosition(sf::Vector2f pos) {
    _position = pos;
    _body.setPosition(_position);
    _label.setPosition(_position + _size / 2.f);
    for (auto& p : inputs) p.shape.setPosition(_position + p.relativePos);
    for (auto& p : outputs) p.shape.setPosition(_position + p.relativePos);
}

void Component::refresh_inputs_colors() {
    for (auto& input : inputs) input.shape.setFillColor(getPinColor(input.state));
}

sf::Color Component::getPinColor(int state) const {
    if (state == UNDEFINED) return OUTPUT_PIN_UNDEFINED;
    if (state == TRUE) return OUTPUT_PIN_ON;
    return OUTPUT_PIN_OFF;
}

sf::Color Component::getBodyColor(int state) const {
    if (state == UNDEFINED) return OUTPUT_COLOR_OFF;
    if (state == TRUE) return OUTPUT_COLOR_ON;
    return OUTPUT_COLOR_OFF;
}

sf::Vector2f Component::getPortFullPosition(size_t index, bool isInput) const {
    if (isInput && index < inputs.size())
        return _position + inputs[index].relativePos;
    if (!isInput && index < outputs.size())
        return _position + outputs[index].relativePos;
    return _position;
}