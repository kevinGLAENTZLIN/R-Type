/*
** EPITECH PROJECT, 2024
** R-Type - ECS : ProjectileCollision
** File description:
** Handles collision between projectiles and other entities.
*/

#include "ProjectileCollision.hh"
#include "../../Utils/Utils.hh"

std::size_t ECS::Systems::ProjectileCollision::projectileIsHit(
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
                } else
                    selfCollision = false;
            if (selfCollision) {
                continue;
            }
            std::size_t entity = entities[i];
            std::size_t projectile = projectileEntities[j];

            auto &posA = positions[entity].value();
            auto &hitboxA = hitboxes[entity].value();
            
            auto &posB = positions[projectile].value();
            auto &hitboxB = hitboxes[projectile].value();
                
            if (ECS::Utils::checkCollision(posA, hitboxA, posB, hitboxB)) {
                std::cout << "Projectile " << projectile << " collided with Entity ";
                std::cout << entity << " and should be destroyed" << std::endl;
                return projectile;
            }
        }
    }
    return 100000;
}
