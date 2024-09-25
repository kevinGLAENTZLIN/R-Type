/*
** EPITECH PROJECT, 2024
** Player.cpp
** File description:
** Player class
*/
#include "Player.hh"

ECS::Entities::Player::Player(std::size_t id):
    _id(id)
{}

std::size_t ECS::Entities::Player::getId() const
{
    return _id;
}
