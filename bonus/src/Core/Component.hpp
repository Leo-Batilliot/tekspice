#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct Port {
    sf::CircleShape shape;
    sf::Vector2f relativePos;
    int state = -1;
};

class Component {
public:
    Component(const std::string& name, sf::Vector2f pos, const sf::Font& font);
    virtual ~Component() = default;

    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window);
    virtual void renderWithStates(sf::RenderWindow& window, sf::RenderStates states);
    virtual void handleInteraction(const sf::Vector2f&) {}

    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition() const { return _position; }
    sf::FloatRect getBounds() const { return _body.getGlobalBounds(); }
    sf::Vector2f getSize() const { return _size; }
    sf::Vector2f getPortFullPosition(size_t index, bool isInput) const;
    void refresh_inputs_colors();

    std::vector<Port> inputs;
    std::vector<Port> outputs;

protected:
    void initGeometry();
    sf::Color getPinColor(int state) const;
    sf::Color getBodyColor(int state) const;

    sf::Vector2f _position;
    sf::Vector2f _size;
    sf::RectangleShape _body;
    sf::Text _label;
    std::string _typeName; 
};