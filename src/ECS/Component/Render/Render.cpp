/*
** EPITECH PROJECT, 2024
** R-Type - Components : Render
** File description:
** Render Component
*/

#include "Render.hh"

ECS::Components::Render::Render(const std::string path, float rotation, float scale):
    _color(RED), _path(path), _rotation(rotation), _scale(scale)
{
}

ECS::Components::Render::Render(const Render& other):
    _color(other._color),
    _path(other._path),
    _rotation(other._rotation),
    _scale(other._scale)

{

    //_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
}

ECS::Components::Render& ECS::Components::Render::operator=(const Render& other)
{
    if (this != &other) {
        _color = other._color;
        _rotation = other._rotation;
        _scale = other._scale;
        _path = other._path;

        // _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
    }
    return *this;
}

void ECS::Components::Render::render(raylib::Model &model, raylib::Vector3 position)
{
    raylib::Vector3 rotation = {0.0f, 1.0f, 0.0f};
    raylib::Vector3 scale = {1.0f, 1.0f, 1.0f};
    model.Draw(position, rotation, 45.0f, scale, WHITE);
}
const std::string ECS::Components::Render::getPath() const
{
    return _path;
}
