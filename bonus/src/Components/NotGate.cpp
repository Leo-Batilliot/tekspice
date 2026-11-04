#include "NotGate.hpp"
#include "Config.hpp"

NotGate::NotGate(sf::Vector2f pos, const sf::Font& font) : Component("NOT", pos, font) {
    inputs.push_back(Port());
    outputs.push_back(Port());
    initGeometry();
}
void NotGate::update() {
    if (inputs[0].state == UNDEFINED) {
        outputs[0].state = UNDEFINED;
    } else {
        outputs[0].state = !inputs[0].state;
    }
    outputs[0].shape.setFillColor(getPinColor(outputs[0].state));
    refresh_inputs_colors();
}