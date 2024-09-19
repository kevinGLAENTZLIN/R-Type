/*
** EPITECH PROJECT, 2024
** Missile.cpp
** File description:
** Missile class implementation
*/

#include "Missile.hh"

Missile::Missile(std::size_t id):
    _id(id)
{}

std::size_t Missile::getId() const
{
    return _id;
}
