/*
** EPITECH PROJECT, 2024
** R-Type - Components : Hitbox
** File description:
** Hitbox Component
*/

#include "Hitbox.hh"

ECS::Components::Hitbox::Hitbox(float width, float height):
    _width(width), _height(height)
{}

float ECS::Components::Hitbox::getWidth() const
{
    return _width;
}

float ECS::Components::Hitbox::getHeight() const
{
    return _height;
}

void ECS::Components::Hitbox::setWidth(float width)
{
    _width = width;
}

void ECS::Components::Hitbox::setHeight(float height)
{
    _height = height;
}
