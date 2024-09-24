/*
** EPITECH PROJECT, 2024
** R-Type - Components : Health
** File description:
** Health Component
*/

#include "Health.hh"

Health::Health(int health):
    _health(health)
{}

int Health::getHealth() const
{
    return _health;
}

void Health::setHealth(int health)
{
    _health = health;
}
