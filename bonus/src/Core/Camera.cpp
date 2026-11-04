/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-11
** File description:
** Camera
*/

#include "Camera.hpp"

Camera::Camera(sf::Vector2f size) : _view(size / 2.f, size), _initialViewSize(size) {}

void Camera::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (const auto* scroll = event.getIf<sf::Event::MouseWheelScrolled>()) {
        float factor = (scroll->delta > 0) ? CAMERA_ZOOM_IN_FACTOR : CAMERA_ZOOM_OUT_FACTOR;
        _view.zoom(factor);
    }

    if (const auto* mouseBtn = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseBtn->button == sf::Mouse::Button::Right) {
            _isPanning = true;
            _lastMousePos = window.mapPixelToCoords(mouseBtn->position, _view);
        }
    }

    if (event.is<sf::Event::MouseButtonReleased>()) {
        _isPanning = false;
    }

    if (const auto* mouseMove = event.getIf<sf::Event::MouseMoved>()) {
        if (_isPanning) {
            sf::Vector2f currentMousePos = window.mapPixelToCoords(mouseMove->position, _view);
            _view.move(_lastMousePos - currentMousePos);
            _lastMousePos = window.mapPixelToCoords(mouseMove->position, _view);
        }
    }

    if (const auto* keyPress = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPress->code == CAMERA_KEY_UP || keyPress->code == CAMERA_KEY_UP_ALT) _moveUp = true;
        if (keyPress->code == CAMERA_KEY_DOWN || keyPress->code == CAMERA_KEY_DOWN_ALT) _moveDown = true;
        if (keyPress->code == CAMERA_KEY_LEFT || keyPress->code == CAMERA_KEY_LEFT_ALT) _moveLeft = true;
        if (keyPress->code == CAMERA_KEY_RIGHT || keyPress->code == CAMERA_KEY_RIGHT_ALT) _moveRight = true;
    }

    if (const auto* keyRelease = event.getIf<sf::Event::KeyReleased>()) {
        if (keyRelease->code == CAMERA_KEY_UP || keyRelease->code == CAMERA_KEY_UP_ALT) _moveUp = false;
        if (keyRelease->code == CAMERA_KEY_DOWN || keyRelease->code == CAMERA_KEY_DOWN_ALT) _moveDown = false;
        if (keyRelease->code == CAMERA_KEY_LEFT || keyRelease->code == CAMERA_KEY_LEFT_ALT) _moveLeft = false;
        if (keyRelease->code == CAMERA_KEY_RIGHT || keyRelease->code == CAMERA_KEY_RIGHT_ALT) _moveRight = false;
    }
}

void Camera::update() {
    sf::Vector2f movement(0.f, 0.f);
    float zoomFactor = _view.getSize().y / _initialViewSize.y;
    float adjustedSpeed = CAMERA_KEYBOARD_SPEED * zoomFactor;
    
    if (_moveUp) movement.y -= adjustedSpeed;
    if (_moveDown) movement.y += adjustedSpeed;
    if (_moveLeft) movement.x -= adjustedSpeed;
    if (_moveRight) movement.x += adjustedSpeed;
    
    if (movement != sf::Vector2f(0.f, 0.f)) {
        _view.move(movement);
    }
}

void Camera::onResize(sf::Vector2u newSize) {
    sf::Vector2f center = _view.getCenter();
    _view.setSize(sf::Vector2f(newSize));
    _view.setCenter(center);
}