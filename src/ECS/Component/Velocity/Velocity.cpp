/*
** EPITECH PROJECT, 2024
** R-Type - Components : Velocity
** File description:
** Velocity Component
*/

#include "Velocity.hh"

ECS::Components::Velocity::Velocity(float x, float y):
    _x(x), _y(y)
{}

ECS::Components::Velocity::Velocity(std::pair<float, float> vel):
    _x(vel.first), _y(vel.second)
{}

float ECS::Components::Velocity::getX() const
{
    return _x;
}

float ECS::Components::Velocity::getY() const
{
    return _y;
}

void ECS::Components::Velocity::setX(float x)
{
    _x = x;
}

void ECS::Components::Velocity::setY(float y)
{
    _y = y;
}

std::pair<float, float> ECS::Components::Velocity::getVelPair() const
{
    return std::make_pair(_x, _y);
}

void ECS::Components::Velocity::setVelPair(std::pair<float, float> vel)
{
    _x = vel.first;
    _y = vel.second;
}
