/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-11
** File description:
** OrGate
*/

#pragma once
#include "Core/Component.hpp"

class OrGate : public Component {
public:
    OrGate(sf::Vector2f pos, const sf::Font& font);
    void update() override;
};