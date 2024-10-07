/*
** EPITECH PROJECT, 2024
** R-Type - Components : Render
** File description:
** Render Component
*/

#include "Render.hh"

ECS::Components::Render::Render(const std::string path, float rotation, float scale):
    _color(WHITE), _path(path), _rotation(rotation), _scale(scale)
{
}

ECS::Components::Render::Render(const Render& other):
    _color(other._color),
    _path(other._path),
    _rotation(other._rotation),
    _scale(other._scale)

{
}

ECS::Components::Render& ECS::Components::Render::operator=(const Render& other)
{
    if (this != &other) {
        _color = other._color;
        _rotation = other._rotation;
        _scale = other._scale;
        _path = other._path;
    }
    return *this;
}

void ECS::Components::Render::render(raylib::Model &model, raylib::Vector3 position, raylib::Vector3 rotation, raylib::Vector3 scale)
{
    model.Draw(position, rotation, 45.0f, scale, _color);
}

void ECS::Components::Render::render(raylib::Texture &texture, raylib::Vector3 position, raylib::Vector3 rotation, raylib::Vector3 scale)
{
    Vector2 pos = {position.GetX(), position.GetY()};

    texture.Draw(pos, rotation.GetZ(), scale.GetX(), _color);
}

const raylib::Color& ECS::Components::Render::getColor() const
{
    return _color;
}

void ECS::Components::Render::setColor(const raylib::Color& color)
{
    _color = color;
}

const std::string ECS::Components::Render::getPath() const
{
    return _path;
}
