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
    ECS::RessourcePool &ressourcePool)
{
    for (auto &entity : entities) {
            if (!(renders[entity].has_value() || positions[entity].has_value())){
               continue;
            }
            auto &position = positions[entity].value();
            auto &render = renders[entity].value();
            raylib::Vector3 pos = Vector3(position.getX()/100, 0, position.getY()/100);
            render.render(ressourcePool.getModel(render.getPath()), pos);
            std::cout << "Cordonnées : " << position.getX() << " " << position.getY() << std::endl;
            std::cout << "rendering" << std::endl;
    }
}
