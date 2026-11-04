/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-11
** File description:
** NotGate
*/

#pragma once
#include "Core/Component.hpp"

class NotGate : public Component {
public:
    NotGate(sf::Vector2f pos, const sf::Font& font);
    void update() override;
};