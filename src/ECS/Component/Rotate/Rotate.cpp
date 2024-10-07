/*
** EPITECH PROJECT, 2024
** R-Type - Components : Rotate
** File description:
** Position Component
*/

#include "Rotate.hh"

ECS::Components::Rotate::Rotate(float x, float y, float z):
    _x(x), _y(y), _z(z)
{}

float ECS::Components::Rotate::getRotateX() const
{
    return _x;
}

float ECS::Components::Rotate::getRotateY() const
{
    return _y;
}

float ECS::Components::Rotate::getRotateZ() const
{
    return _z;
}

void ECS::Components::Rotate::setRotateX(float x)
{
    _x = x;
}

void ECS::Components::Rotate::setRotateY(float y)
{
    _y = y;
}

void ECS::Components::Rotate::setRotateZ(float z)
{
    _z = z;
}
