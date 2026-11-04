/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-tekspice-11
** File description:
** Output
*/

#pragma once
#include "Core/Component.hpp"

class Output : public Component {
public:
    Output(sf::Vector2f pos, const sf::Font& font);
    void update() override;
};