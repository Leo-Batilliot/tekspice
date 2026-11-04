/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-11
** File description:
** Input
*/

#pragma once
#include "Core/Component.hpp"

class Input : public Component {
public:
    Input(sf::Vector2f pos, const sf::Font& font);
    void update() override;
    void handleInteraction(const sf::Vector2f& mousePos) override;

private:
    bool m_state = false;
};