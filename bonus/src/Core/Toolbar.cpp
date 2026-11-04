#include "Toolbar.hpp"
#include "Config.hpp"
#include "Components/AndGate.hpp"
#include "Components/OrGate.hpp"
#include "Components/NotGate.hpp"
#include "Components/Input.hpp"
#include "Components/Output.hpp"
#include "Components/TrueInput.hpp"
#include "Components/FalseInput.hpp"

Toolbar::Toolbar(const sf::Font& font, sf::Vector2u windowSize) 
    : _font(font), _arrowLeft(font, "<", 20), _arrowRight(font, ">", 20) {
    
    _typeNames = {"And", "Or", "Not", "Input", "Output", "True", "False"};

    for (auto& name : _typeNames) {
        if (name == "And") _previews[name] = std::make_unique<AndGate>(sf::Vector2f(0,0), font);
        else if (name == "Or") _previews[name] = std::make_unique<OrGate>(sf::Vector2f(0,0), font);
        else if (name == "Not") _previews[name] = std::make_unique<NotGate>(sf::Vector2f(0,0), font);
        else if (name == "Input") _previews[name] = std::make_unique<Input>(sf::Vector2f(0,0), font);
        else if (name == "Output") _previews[name] = std::make_unique<Output>(sf::Vector2f(0,0), font);
        else if (name == "True") _previews[name] = std::make_unique<TrueInput>(sf::Vector2f(0,0), font);
        else if (name == "False") _previews[name] = std::make_unique<FalseInput>(sf::Vector2f(0,0), font);
    }
    
    updateLayout(windowSize);
}

void Toolbar::updateLayout(sf::Vector2u size) {
    float height = size.y * TOOLBAR_SCREEN_SIZE;
    _background.setSize({(float)size.x, height});
    _background.setPosition({0, size.y - height});
    _background.setFillColor(TOOLBAR_COLOR);
    _background.setOutlineThickness(TOOLBAR_OUTLINE_THICKNESS);
    _background.setOutlineColor(TOOLBAR_OUTLINE_COLOR);

    _btnLeft.setSize({height, height});
    _btnLeft.setPosition({0, size.y - height});
    _btnLeft.setFillColor(TOOLBAR_ARROWS_COLOR);

    _btnRight.setSize({height, height});
    _btnRight.setPosition({(float)size.x - height, size.y - height});
    _btnRight.setFillColor(TOOLBAR_ARROWS_COLOR);

    sf::FloatRect lb = _arrowLeft.getLocalBounds();
    _arrowLeft.setOrigin({lb.position.x + lb.size.x / 2.f, lb.position.y + lb.size.y / 2.f});
    _arrowLeft.setPosition(_btnLeft.getPosition() + sf::Vector2f(height/2.f, height/2.f));
    _arrowLeft.setFillColor(sf::Color::White);

    sf::FloatRect rb = _arrowRight.getLocalBounds();
    _arrowRight.setOrigin({rb.position.x + rb.size.x / 2.f, rb.position.y + rb.size.y / 2.f});
    _arrowRight.setPosition(_btnRight.getPosition() + sf::Vector2f(height/2.f, height/2.f));
    _arrowRight.setFillColor(sf::Color::White);
}

void Toolbar::render(sf::RenderWindow& window) {
    window.draw(_background);
    window.draw(_btnLeft);
    window.draw(_btnRight);
    window.draw(_arrowLeft);
    window.draw(_arrowRight);

    float height = _background.getSize().y;
    float padding = height * TOOLBAR_COMPONENTS_PADDING_RATIO;
    float itemSize = height - (padding * 2.f);
    float startX = _btnLeft.getSize().x + padding;
    float currentX = startX;

    for (size_t i = (size_t)_offset; i < _typeNames.size(); ++i) {
        if (currentX + itemSize + padding > _btnRight.getPosition().x) break;

        std::string name = _typeNames[i];
        auto& comp = _previews[name];
        sf::Vector2f slotPos(currentX, _background.getPosition().y + padding);

        sf::RectangleShape slot({itemSize, itemSize});
        slot.setPosition(slotPos);
        slot.setFillColor(TOOLBAR_COMPONENT_SLOT_COLOR);
        window.draw(slot);

        sf::Vector2f originalSize = comp->getSize();
        float finalScale = std::min((itemSize * TOOLBAR_COMPONENT_INSLOT_SCALE) / originalSize.x, (itemSize * TOOLBAR_COMPONENT_INSLOT_SCALE) / originalSize.y);

        sf::Transform transform;
        transform.translate(slotPos + sf::Vector2f(itemSize/2.f, itemSize/2.f));
        transform.scale({finalScale, finalScale});
        transform.translate(-originalSize / 2.f);

        sf::RenderStates states;
        states.transform = transform;
        comp->renderWithStates(window, states);

        currentX += itemSize + padding;
    }
}

std::string Toolbar::handleInteraction(sf::Vector2f mousePosUI) {
    if (_btnLeft.getGlobalBounds().contains(mousePosUI)) {
        if (_offset > 0) _offset--;
        return "";
    }
    if (_btnRight.getGlobalBounds().contains(mousePosUI)) {
        if (static_cast<size_t>(_offset + 1) < _typeNames.size()) _offset++;
        return "";
    }

    float height = _background.getSize().y;
    float padding = height * TOOLBAR_COMPONENTS_PADDING_RATIO;
    float itemSize = height - (padding * 2.f);
    float startX = _btnLeft.getSize().x + padding;
    float currentX = startX;

    for (size_t i = static_cast<size_t>(_offset); i < _typeNames.size(); ++i) {
        if (currentX + itemSize + padding > _btnRight.getPosition().x) break;
        sf::FloatRect slotBounds({currentX, _background.getPosition().y + padding}, {itemSize, itemSize});
        if (slotBounds.contains(mousePosUI)) {
            return _typeNames[i];
        }

        currentX += itemSize + padding;
    }

    return "";
}