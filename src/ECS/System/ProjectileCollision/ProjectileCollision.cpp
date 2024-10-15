/*
** EPITECH PROJECT, 2024
** R-Type - ECS : ProjectileCollision
** Fie description:
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
        std::size_t projectile = projectileEntities[j];
        auto &projectilePos = positions[projectile].value();
        auto &projectileHitbox = hitboxes[projectile].value();

        if (projectilePos.getX() >= 11.0 || projectilePos.getX() <= -11.0)
            return projectile;
        
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
            auto &entityPos = positions[entity].value();
            auto &entityHitbox = hitboxes[entity].value();

            if (ECS::Utils::checkCollision(entityPos, entityHitbox, projectilePos, projectileHitbox))
                return projectile;
        }
    }
    return 100000;
}
