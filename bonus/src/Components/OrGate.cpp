#include "OrGate.hpp"
#include "Config.hpp"

OrGate::OrGate(sf::Vector2f pos, const sf::Font& font) : Component("OR", pos, font) {
    inputs.push_back(Port());
    inputs.push_back(Port());
    outputs.push_back(Port());
    initGeometry();
}
void OrGate::update() {
    if (inputs[0].state == UNDEFINED || inputs[1].state == UNDEFINED) {
        outputs[0].state = UNDEFINED;
    } else {
        outputs[0].state = (inputs[0].state || inputs[1].state);
    }
    outputs[0].shape.setFillColor(getPinColor(outputs[0].state));
    refresh_inputs_colors();
}