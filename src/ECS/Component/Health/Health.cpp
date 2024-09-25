/*
** EPITECH PROJECT, 2024
** R-Type - Components : Health
** File description:
** Health Component
*/

#include "Health.hh"

<<<<<<< HEAD
ECS::Components::Health::Health(int health):
    _health(health)
{}

int ECS::Components::Health::getHealth() const
=======
Components::Health::Health(int health):
    _health(health)
{}

int Components::Health::GetHealth() const
>>>>>>> main
{
    return _health;
}

<<<<<<< HEAD
void ECS::Components::Health::setHealth(int health)
=======
void Components::Health::SetHealth(int health)
>>>>>>> main
{
    _health = health;
}
