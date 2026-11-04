#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Core/Circuit.hpp"
#include "Core/Camera.hpp"
#include "Core/Toolbar.hpp"
#include "Components/AndGate.hpp"
#include "Components/OrGate.hpp"
#include "Components/NotGate.hpp"
#include "Components/Input.hpp"
#include "Components/Output.hpp"
#include "Components/TrueInput.hpp"
#include "Components/FalseInput.hpp"
#include "Config.hpp"

int main() {
    sf::err().rdbuf(nullptr);
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), WINDOW_NAME);
    window.setFramerateLimit(WINDOW_FPS);

    sf::Font font;
    if (!font.openFromFile(FONT))
        return -1;

    Camera camera(sf::Vector2f(window.getSize()));
    sf::View uiView(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize())));
    Toolbar toolbar(font, window.getSize());
    Circuit world("WORLD", {0, 0}, font);

    bool isDragging = false;
    sf::Vector2f pressPosWorld;

    while (window.isOpen()) {
        sf::Vector2i mousePosPix = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosWorld = window.mapPixelToCoords(mousePosPix, camera.getView());
        sf::Vector2f mousePosUI = window.mapPixelToCoords(mousePosPix, uiView);

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == KEY_QUIT) window.close();
            }

            if (const auto* resize = event->getIf<sf::Event::Resized>()) {
                sf::Vector2u newSize = resize->size;
                uiView.setSize({(float)newSize.x, (float)newSize.y});
                uiView.setCenter({(float)newSize.x / 2.f, (float)newSize.y / 2.f});
                camera.onResize(newSize);
                toolbar.updateLayout(newSize);
            }

            if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseBtn->button == sf::Mouse::Button::Left) {
                    std::string type = toolbar.handleInteraction(mousePosUI);
                    if (type != "") {
                        sf::Vector2f spawn = camera.getView().getCenter();
                        if (type == "And") world.addComponent(std::make_unique<AndGate>(spawn, font));
                        else if (type == "Or") world.addComponent(std::make_unique<OrGate>(spawn, font));
                        else if (type == "Not") world.addComponent(std::make_unique<NotGate>(spawn, font));
                        else if (type == "Input") world.addComponent(std::make_unique<Input>(spawn, font));
                        else if (type == "Output") world.addComponent(std::make_unique<Output>(spawn, font));
                        else if (type == "True") world.addComponent(std::make_unique<TrueInput>(spawn, font));
                        else if (type == "False") world.addComponent(std::make_unique<FalseInput>(spawn, font));
                    } else {
                        isDragging = false;
                        pressPosWorld = mousePosWorld;
                        world.startConnection(mousePosWorld);
                        world.handleInteraction(mousePosWorld);
                    }
                }
            }

            if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonReleased>()) {
                if (mouseBtn->button == sf::Mouse::Button::Left) {
                    if (!isDragging) {
                        for (auto& comp : world.getSubComponents()) {
                            if (comp->getBounds().contains(mousePosWorld)) {
                                comp->handleInteraction(mousePosWorld);
                                break;
                            }
                        }
                    }
                    world.endConnection(mousePosWorld);
                    world.endDrag();
                    isDragging = false;
                }
            }

            if (event->is<sf::Event::MouseMoved>()) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    float dist = std::hypot(mousePosWorld.x - pressPosWorld.x, mousePosWorld.y - pressPosWorld.y);
                    if (dist > CIRCUIT_DRAG_THRESHOLD) isDragging = true;
                    world.handleDrag(mousePosWorld);
                }
            }

            camera.handleEvent(*event, window);

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == KEY_DELETE_PRIMARY || key->code == KEY_DELETE_SECONDARY) {
                    world.removeConnectionAt(mousePosWorld);
                    world.removeComponentAt(mousePosWorld);
                    world.endConnection(mousePosWorld);
                    world.endDrag();
                }
            }
        }

        camera.update();
        world.update();

        window.clear(BACKGROUND_COLOR);
        
        window.setView(camera.getView());
        {
            sf::Vector2f viewSize = camera.getView().getSize();
            sf::Vector2f viewCenter = camera.getView().getCenter();
            float left = viewCenter.x - viewSize.x / 2.f;
            float right = viewCenter.x + viewSize.x / 2.f;
            float top = viewCenter.y - viewSize.y / 2.f;
            float bottom = viewCenter.y + viewSize.y / 2.f;
            
            for (float x = std::floor(left / GRID_SIZE) * GRID_SIZE; x <= right; x += GRID_SIZE) {
                sf::Vertex line[] = {
                    sf::Vertex({x, top}, GRID_COLOR),
                    sf::Vertex({x, bottom}, GRID_COLOR)
                };
                window.draw(line, 2, sf::PrimitiveType::Lines);
            }
            
            for (float y = std::floor(top / GRID_SIZE) * GRID_SIZE; y <= bottom; y += GRID_SIZE) {
                sf::Vertex line[] = {
                    sf::Vertex({left, y}, GRID_COLOR),
                    sf::Vertex({right, y}, GRID_COLOR)
                };
                window.draw(line, 2, sf::PrimitiveType::Lines);
            }
        }
        world.renderCircuit(window, mousePosWorld);

        window.setView(uiView);
        toolbar.render(window);

        window.display();
    }
    return 0;
}