/*
** EPITECH PROJECT, 2024
** R-Type - Components : Render
** File description:
** Render Component
*/

#include "Render.hh"

ECS::Components::Render::Render(std::string path, float rotation, float scale):
    _texture(path), _rotation(rotation), _scale(scale)
{}

Texture2D &ECS::Components::Render::getTexture() const
{
    return _texture;
}

float ECS::Components::Render::getRotation() const
{
    return _rotation;
}

float ECS::Components::Render::getScale() const
{
    return _scale;
}

void ECS::Components::Render::setRotation(float rotation)
{
    _rotation = rotation;
}

void ECS::Components::Render::setScale(float scale)
{
    _scale = scale;
}
