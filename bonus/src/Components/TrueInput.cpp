#include "TrueInput.hpp"
#include "Config.hpp"

TrueInput::TrueInput(sf::Vector2f pos, const sf::Font& font) : Component("TRUE", pos, font) {
    outputs.push_back(Port());
    outputs[0].state = TRUE;
    initGeometry();
}
void TrueInput::update() { outputs[0].shape.setFillColor(getPinColor(outputs[0].state)); }