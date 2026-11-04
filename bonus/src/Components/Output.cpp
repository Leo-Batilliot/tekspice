#include "Output.hpp"
#include "Config.hpp"

Output::Output(sf::Vector2f pos, const sf::Font& font) : Component("OUTPUT", pos, font) {
    inputs.push_back(Port());
    initGeometry();
}

void Output::update() {
    _body.setFillColor(getBodyColor(inputs[0].state));
    refresh_inputs_colors();
}