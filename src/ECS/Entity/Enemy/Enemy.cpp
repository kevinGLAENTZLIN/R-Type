/*
** EPITECH PROJECT, 2024
** Enemy.cpp
** File description:
** Enemy class
*/

#include "Enemy.hh"

Enemy::Enemy(std::size_t id):
    _id(id)
{}

std::size_t Enemy::getId() const
{
    return _id;
}
