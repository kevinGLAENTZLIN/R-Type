/*
** EPITECH PROJECT, 2024
** Utils.hh
** File description:
** Utils class
*/

#include "Utils.hh"

bool ECS::Utils::checkCollision(
    const ECS::Components::Position &posA, const ECS::Components::Hitbox &hitboxA,
    const ECS::Components::Position &posB, const ECS::Components::Hitbox &hitboxB)
{
    return (posA.getX() < posB.getX() + hitboxB.getWidth() &&
            posA.getX() + hitboxA.getWidth() > posB.getX() &&
            posA.getY() < posB.getY() + hitboxB.getHeight() &&
            posA.getY() + hitboxA.getHeight() > posB.getY());
}
