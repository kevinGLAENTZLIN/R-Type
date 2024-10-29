/*
** EPITECH PROJECT, 2024
** R-Type - ECS : ProjectileCollision
** Fie description:
** Handles collision between projectiles and other entities.
*/

#include "ProjectileCollision.hh"
#include "../../Utils/Utils.hh"

std::vector<std::size_t> ECS::Systems::ProjectileCollision::projectileIsHit(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> &hitboxes,
    ECS::ComponentManager::SparseArray<ECS::Components::AI> &AIs,
    std::vector<std::size_t> & projectileEntities, std::vector<std::size_t> & entities)
{
    bool selfCollision = false;
    std::vector<std::size_t> entityCollided;

    for (std::size_t j = 0; j < projectileEntities.size(); ++j) {
        bool isAIShot = false;
        std::size_t projectile = projectileEntities[j];
        auto &projectilePos = positions[projectile].value();
        auto &projectileHitbox = hitboxes[projectile].value();

        if (projectilePos.getX() >= 11.0 || projectilePos.getX() <= -11.0) {
            entityCollided.push_back(projectile);
            continue;
        }

        isAIShot = AIs.size() > 0 && AIs[projectile].has_value();

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
            bool isAIEntity = AIs.size() > 0 && AIs[entity].has_value();

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
