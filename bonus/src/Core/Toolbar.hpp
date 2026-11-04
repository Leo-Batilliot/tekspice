#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <map>
#include "Component.hpp"

class Toolbar {
public:
    Toolbar(const sf::Font& font, sf::Vector2u windowSize);
    void render(sf::RenderWindow& window);
    std::string handleInteraction(sf::Vector2f mousePosUI);
    void updateLayout(sf::Vector2u size);

private:
    sf::RectangleShape _background;
    const sf::Font& _font;
    int _offset = 0;

    std::vector<std::string> _typeNames;
    std::map<std::string, std::unique_ptr<Component>> _previews;

    sf::RectangleShape _btnLeft;
    sf::RectangleShape _btnRight;
    sf::Text _arrowLeft;
    sf::Text _arrowRight;
};