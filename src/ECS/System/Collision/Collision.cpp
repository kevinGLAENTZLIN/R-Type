/*
** EPITECH PROJECT, 2024
** hitbox.hh
** File description:
** System hitbox class
*/

#include "Collision.hh"
#include "../../Utils/Utils.hh"

void ECS::Systems::Collision::playerIsHit(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> &hitboxes,
    ECS::ComponentManager::SparseArray<ECS::Components::Health> &healths,
    std::size_t player, std::vector<std::size_t> &entities)
{
    if (healths[player]->getInvincibility() > 0)
        healths[player]->modifyInvincibilityBy(-1);
    
    for (std::size_t i = 0; i < entities.size(); ++i) {
        std::size_t entity = entities[i];
        auto &posEntity = positions[entity].value();
        auto &hitboxEntity = hitboxes[entity].value();
        auto &posPlayer = positions[player].value();
        auto &hitboxPlayer = hitboxes[player].value();

        if (ECS::Utils::checkCollision(posEntity, hitboxEntity, posPlayer, hitboxPlayer)) {
            if (healths[player]->getInvincibility() == 0) {
                std::cout << "OOF!!" << std::endl;
                healths[player]->modifyHealthBy(-1);
                healths[player]->setInvincibility(200);
            } 
        }
    }
}
