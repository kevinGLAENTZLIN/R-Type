#include "Pod.hh"

ECS::Components::Pod::Pod(std::size_t player):
    _player(player), _level(0), _isUp(false)
{}


std::size_t ECS::Components::Pod::getPlayer()
{
    return _player;
}

void ECS::Components::Pod::setPlayer(std::size_t player)
{
    _player = player;
}

std::size_t ECS::Components::Pod::getLevel()
{
    return _level;
}

void ECS::Components::Pod::setLevel(std::size_t level)
{
    _level = level;
}

bool ECS::Components::Pod::isUp()
{
    return _isUp;
}

void ECS::Components::Pod::setIsUp(bool isUp)
{
    _isUp = isUp;
}

