/*
** EPITECH PROJECT, 2024
** R-Type - ECS : ProjectileCollision
** File description:
** Handles collision between projectiles and other entities.
*/

#include "ProjectileCollision.hh"
#include "../../Utils/Utils.hh"

void ECS::Systems::ProjectileCollision::projectileIsHit(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> &hitboxes,
    std::vector<std::size_t> & projectileEntities, std::vector<std::size_t> & entities)
{
    bool selfCollision = false;
    for (std::size_t j = 0; j < projectileEntities.size(); ++j) {
        for (std::size_t i = 0; i < entities.size(); ++i) {
            for (std::size_t temp = 0; temp < projectileEntities.size(); temp++)
                if (entities[i] == projectileEntities[temp]) {
                    selfCollision = true;
                    break;
                }
            if (selfCollision)
                continue;
            std::size_t entityA = entities[i];
            std::size_t entityB = projectileEntities[j];
            
            if (positions[entityA].has_value() && hitboxes[entityA].has_value() &&
                positions[entityB].has_value() && hitboxes[entityB].has_value()) {
                
                auto &posA = positions[entityA].value();
                auto &hitboxA = hitboxes[entityA].value();
                
                auto &posB = positions[entityB].value();
                auto &hitboxB = hitboxes[entityB].value();
                
                if (ECS::Utils::checkCollision(posA, hitboxA, posB, hitboxB)) {
                    std::cout << "Projectile " << entityA << " collided with Entity " << entityB << " and should be destroyed" << std::endl;
                    
                }
            }
        }
    }
}
