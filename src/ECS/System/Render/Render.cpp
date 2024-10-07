/*
** EPITECH PROJECT, 2024
** SystemRender.cpp
** File description:
** SystemRender cpp
*/
#include "Render.hh"
void ECS::Systems::SystemRender::update(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Render> &renders,
    std::vector<std::size_t> &entities,
    ECS::RessourcePool &ressourcePool,
    raylib::Camera3D &camera)
{
    raylib::Vector3 rotation = {0.0f, 0.0f, 0.0f};
    raylib::Vector3 scale = {1.0f, 1.0f, 1.0f};
    for (auto &entity : entities) {
        if (!(renders[entity].has_value() || positions[entity].has_value())) {
            continue;
        }
        auto &position = positions[entity].value();
        auto &render = renders[entity].value();
        raylib::Vector3 pos(position.getX() , 0, position.getY());
        const std::string path = render.getPath();

        if (ECS::Utils::getRaylibFileType(path) == ECS::Utils::FileType::Model) {
            camera.BeginMode();
            render.render(ressourcePool.getModel(render.getPath()), pos, rotation, scale);
            camera.EndMode();
        } else if (ECS::Utils::getRaylibFileType(path) == ECS::Utils::FileType::Texture) {
            render.render(ressourcePool.getTexture(render.getPath()), pos, rotation, scale);
        } else {
            continue;
        }
    }
}
