/*
** EPITECH PROJECT, 2024
** R-Type - Components : Position
** File description:
** Position Component
*/

#include "Position.hpp"
#include <ostream>

ECS::Components::Position::Position(float x, float y):
    _x(x), _y(y)
{}

float ECS::Components::Position::getX() const
{
    return _x;
}

float ECS::Components::Position::getY() const
{
    return _y;
}

void ECS::Components::Position::setX(float x)
{
    _x = x;
}

void ECS::Components::Position::setY(float y)
{
    _y = y;
}

std::pair<float, float> ECS::Components::Position::getPosPair() const
{
    return std::make_pair(_x, _y);
}
