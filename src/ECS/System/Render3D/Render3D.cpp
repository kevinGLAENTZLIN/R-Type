/*
** EPITECH PROJECT, 2024
** SystemRender3D.cpp
** File description:
** SystemRender3D cpp
*/
#include "Render3D.hh"

void ECS::Systems::SystemRender3D::update(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Render3D> &renders,
    std::vector<std::size_t> &entities,
    ECS::RessourcePool &ressourcePool,
    raylib::Camera3D &camera)
{
    raylib::Vector3 rotation = {0.0f, 0.0f, 0.0f};
    raylib::Vector3 scale = {1.0f, 1.0f, 1.0f};
    bool drawHitBox = true;

    camera.BeginMode();
    if (drawHitBox)
        DrawGrid(100, 1.0f);

    for (auto &entity : entities) {
        if (!(renders[entity].has_value() || positions[entity].has_value())) {
            continue;
        }
        auto &position = positions[entity].value();
        auto &render = renders[entity].value();
        raylib::Vector3 pos(position.getX() , 0.0f, position.getY());
        const std::string path = render.getPath();
        if (drawHitBox) {
            std::pair<float, float> TmpHitbox = ECS::Utils::getModelSize(ressourcePool.getModel(path));
            DrawCubeWires(pos, TmpHitbox.first, 1.0f, TmpHitbox.second, RED);
        }
        render.render(ressourcePool.getModel(path), pos, rotation, scale);
    }
    camera.EndMode();
}
