/*
** EPITECH PROJECT, 2024
** R-Type - Components : Health
** File description:
** Health Component
*/

#include "Health.hh"

/**
 * @brief Constructor to health component.
 *
 * Returns void
 *
 * @tparam Integer to create health component.
 * @return void.
 */
ECS::Components::Health::Health(int health):
    _health(health)
{}

int ECS::Components::Health::getHealth() const
{
    return _health;
}

void ECS::Components::Health::setHealth(int health)
{
    _health = health;
}
