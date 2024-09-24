/*
** EPITECH PROJECT, 2024
** R-Type - Components : Render
** File description:
** Render Component
*/

#include "Render.hh"

Components::Render::Render(std::string path, float rotation, float scale):
    _texture(path), _rotation(rotation), _scale(scale)
{}

Texture2D &Components::Render::getTexture() const
{
    return _texture;
}

float Components::Render::getRotation() const
{
    return _rotation;
}

float Components::Render::getScale() const
{
    return _scale;
}

void Components::Render::setRotation(float rotation)
{
    _rotation = rotation;
}

void Components::Render::setScale(float scale)
{
    _scale = scale;
}
