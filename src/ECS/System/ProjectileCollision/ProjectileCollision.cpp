/*
** EPITECH PROJECT, 2024
** R-Type - ECS : ProjectileCollision
** Fie description:
** Handles collision between projectiles and other entities.
*/

#include "ProjectileCollision.hh"
#include "../../Utils/Utils.hh"

#include <cassert>

std::vector<std::size_t> ECS::Systems::ProjectileCollision::projectileIsHit(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> &hitboxes,
    ECS::ComponentManager::SparseArray<ECS::Components::AI> &AIs,
    std::vector<std::size_t> &projectileEntities, std::vector<std::size_t> &entities)
{
    bool selfCollision = false;
    std::vector<std::size_t> entityCollided;

    for (std::size_t j = 0; j < projectileEntities.size(); ++j) {
        bool isAIShot = false;
        std::size_t projectile = projectileEntities[j];
        assert(positions[projectile].has_value());
        assert(hitboxes[projectile].has_value());
        auto &projectilePos = positions[projectile].value();
        auto &projectileHitbox = hitboxes[projectile].value();

        if (projectilePos.getX() >= 11.0 || projectilePos.getX() <= -11.0) {
            entityCollided.push_back(projectile);
            continue;
        }

        if (AIs.size() > 0 && AIs[projectile].has_value()) {
            isAIShot = true;
        }

        for (std::size_t i = 0; i < entities.size(); ++i) {
            for (std::size_t temp = 0; temp < projectileEntities.size(); temp++) {
                if (entities[i] == projectileEntities[temp]) {
                    selfCollision = true;
                    break;
                } else {
                    selfCollision = false;
                }
            }
            if (selfCollision == true) {
                continue;
            }
            std::size_t entity = entities[i];
            assert(positions[entity].has_value());
            assert(hitboxes[entity].has_value());
            auto &entityPos = positions[entity].value();
            auto &entityHitbox = hitboxes[entity].value();
            bool isAIEntity = false;
            if (AIs.size() > 0 && AIs[entity].has_value()) {
                isAIEntity = true;
            }

            if ((isAIShot && isAIEntity) || (!isAIShot && !isAIEntity)) {
                continue;
            }
            if (ECS::Utils::checkCollision(entityPos, entityHitbox, projectilePos, projectileHitbox)) {
                entityCollided.push_back(entity);
                entityCollided.push_back(projectile);
            }
        }
    }
    return entityCollided;
}
