/*
** EPITECH PROJECT, 2024
** R-Type - Components : Velocity
** File description:
** Velocity Component
*/

#include "Velocity.hh"

Components::Velocity::Velocity(float x, float y):
    _x(x), _y(y)
{}

Components::Velocity::Velocity(std::pair<float, float> vel):
    _x(vel.first), _y(vel.second)
{}

float Components::Velocity::getX() const
{
    return _x;
}

float Components::Velocity::getY() const
{
    return _y;
}

std::pair<float, float> Components::Velocity::getVelPair() const
{
    return std::make_pair(_x, _y);
}

std::ostream & operator<< (std::ostream & stream, const Components::Velocity & velocity) {
    stream << "(" << velocity.getX() << ", " << velocity.getY() << ")";
    return stream;
}
