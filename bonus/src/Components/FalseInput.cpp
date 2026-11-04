#include "FalseInput.hpp"
#include "Config.hpp"

FalseInput::FalseInput(sf::Vector2f pos, const sf::Font& font) : Component("FALSE", pos, font)
{
    outputs.push_back(Port());
    outputs[0].state = FALSE;
    initGeometry();
}

void FalseInput::update()
{
    outputs[0].shape.setFillColor(getPinColor(outputs[0].state));
}