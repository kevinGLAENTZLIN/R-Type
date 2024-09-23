/*
** EPITECH PROJECT, 2024
** R-Type - Components : Position
** File description:
** Position Component
*/

#include "Position.hpp"
#include <ostream>

Components::Position::Position(float x, float y):
    _x(x), _y(y)
{}

float Components::Position::getX() const
{
    return _x;
}

float Components::Position::getY() const
{
    return _y;
}

void Components::Position::setX(float x)
{
    _x = x;
}

void Components::Position::setY(float y)
{
    _y = y;
}

std::pair<float, float> Components::Position::getPosPair() const
{
    return std::make_pair(_x, _y);
}
