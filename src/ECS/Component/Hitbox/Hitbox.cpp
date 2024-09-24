/*
** EPITECH PROJECT, 2024
** R-Type - Components : Hitbox
** File description:
** Hitbox Component
*/

#include "Hitbox.hh"

Components::Hitbox::Hitbox(float width, float height):
    _width(width), _height(height)
{}

float Components::Hitbox::getWidth() const
{
    return _width;
}

float Components::Hitbox::getHeight() const
{
    return _height;
}

void Components::Hitbox::setWidth(float width)
{
    _width = width;
}

void Components::Hitbox::setHeight(float height)
{
    _height = height;
}
