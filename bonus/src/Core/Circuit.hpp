#pragma once
#include "Component.hpp"
#include <memory>

struct Connection {
    size_t fromIdx;
    size_t outPort;
    size_t toIdx;
    size_t inPort;
};

struct PendingConnection {
    size_t fromIdx;
    size_t outPort;
    bool active = false;
};

class Circuit : public Component {
public:
    Circuit(const std::string& name, sf::Vector2f pos, const sf::Font& font);

    void addComponent(std::unique_ptr<Component> comp);
    void addConnection(size_t f, size_t op, size_t t, size_t ip);
    
    void update() override;
    void renderCircuit(sf::RenderWindow& window, sf::Vector2f mousePos);

    void handleInteraction(const sf::Vector2f& mousePos) override;
    void handleDrag(sf::Vector2f mousePos);
    void endDrag();
    void startConnection(sf::Vector2f mousePos);
    void endConnection(sf::Vector2f mousePos);
    auto& getSubComponents() { return _subComponents; }
    void removeComponentAt(sf::Vector2f mousePos);
    void removeConnectionAt(sf::Vector2f mousePos);

private:
    std::vector<std::unique_ptr<Component>> _subComponents;
    std::vector<Connection> _connections;
    PendingConnection _pending;
    Component* _draggedComponent = nullptr;
    sf::Vector2f _dragOffset;
};