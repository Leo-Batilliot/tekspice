#include "Input.hpp"
#include "Config.hpp"

Input::Input(sf::Vector2f pos, const sf::Font& font) : Component("INPUT", pos, font) {
    outputs.push_back(Port());
    initGeometry();
    outputs[0].state = TRUE;
}

void Input::update()
{
    outputs[0].shape.setFillColor(getBodyColor(outputs[0].state));
}

void Input::handleInteraction(const sf::Vector2f&) {
    if (outputs[0].state == UNDEFINED) {
        outputs[0].state = FALSE;
    } else {
        outputs[0].state = !outputs[0].state;
    }
}