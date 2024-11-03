/*
** EPITECH PROJECT, 2024
** R-Type - Components : Health
** File description:
** Health Component
*/

#include "Health.hh"

ECS::Components::Health::Health(int health, int invincibility):
    _health(health), _invincibility(invincibility)
{}

int ECS::Components::Health::getHealth() const
{
    return _health;
}

void ECS::Components::Health::setHealth(int health)
{
    _health = health;
}

void ECS::Components::Health::modifyHealthBy(int delta)
{
    _health += delta;
}

int ECS::Components::Health::getInvincibility() const
{
    return _invincibility;
}

void ECS::Components::Health::setInvincibility(int invincibility)
{
    _invincibility = invincibility;
}

void ECS::Components::Health::modifyInvincibilityBy(int delta)
{
    _invincibility += delta;
}
