/*
** EPITECH PROJECT, 2024
** Player.cpp
** File description:
** Player class
*/

#include "Player.hh"

Player::Player(std::size_t id):
    _id(id)
{}

std::size_t Player::getId() const
{
    return _id;
}
