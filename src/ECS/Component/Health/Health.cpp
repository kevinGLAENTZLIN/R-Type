/*
** EPITECH PROJECT, 2024
** R-Type - Components : Health
** File description:
** Health Component
*/

#include "Health.hh"

Components::Health::Health(int health):
    _health(health)
{}

int Components::Health::GetHealth() const
{
    return _health;
}

void Components::Health::SetHealth(int health)
{
    _health = health;
}
