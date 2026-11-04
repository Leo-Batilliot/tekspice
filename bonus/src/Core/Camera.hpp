/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-11
** File description:
** Camera
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "../Config.hpp"

class Camera {
public:
    Camera(sf::Vector2f size);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void update();
    const sf::View& getView() const { return _view; }
    void onResize(sf::Vector2u newSize);

private:
    sf::View _view;
    sf::Vector2f _initialViewSize;
    bool _isPanning = false;
    sf::Vector2f _lastMousePos;
    bool _moveUp = false;
    bool _moveDown = false;
    bool _moveLeft = false;
    bool _moveRight = false;
};
