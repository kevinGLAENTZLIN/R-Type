/*
** EPITECH PROJECT, 2024
** R-Type - Components : Text
** File description:
** Text Component
*/

#include "Text.hh"

ECS::Components::Text::Text(std::string text, int fontSize, raylib::Color color):
    _text(text), _fontSize(fontSize), _color(color)
{}

std::string ECS::Components::Text::getText() const
{
    return _text;
}

void ECS::Components::Text::setText(std::string text)
{
    _text = text;
}

void ECS::Components::Text::setFontSize(int fontSize)
{
    _fontSize = fontSize;
}

int ECS::Components::Text::getFontSize() const
{
    return _fontSize;
}

void ECS::Components::Text::setColor(raylib::Color color)
{
    _color = color;
}

raylib::Color ECS::Components::Text::getColor() const
{
    return _color;
}
