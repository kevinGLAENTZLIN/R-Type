/*
** EPITECH PROJECT, 2024
** hitbox.hh
** File description:
** System hitbox class
*/

#include "Collision.hh"

void ECS::Systems::Collision::isHit(ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
                            ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> &hitboxes,
                            std::vector<std::size_t> &entities)
{
    for (std::size_t i = 0; i < entities.size(); ++i) {
        for (std::size_t j = i + 1; j < entities.size(); ++j) {
            std::size_t entityA = entities[i];
            std::size_t entityB = entities[j];

            if (positions[entityA].has_value() && hitboxes[entityA].has_value() &&
                positions[entityB].has_value() && hitboxes[entityB].has_value()) {

                auto &posA = positions[entityA].value();
                auto &hitboxA = hitboxes[entityA].value();

                auto &posB = positions[entityB].value();
                auto &hitboxB = hitboxes[entityB].value();

                if (checkCollision(posA, hitboxA, posB, hitboxB)) {
                    std::cout << "Entity " << entityA << " collided with Entity " << entityB << std::endl;
                }
            }
        }
    }
}

bool ECS::Systems::Collision::checkCollision(const ECS::Components::Position &posA, const ECS::Components::Hitbox &hitboxA,
                                     const ECS::Components::Position &posB, const ECS::Components::Hitbox &hitboxB)
{
    float coucou = hitboxB.getWidth();

    return (posA.getX() < posB.getX() + coucou &&
            posA.getX() + hitboxA.getWidth() > posB.getX() &&
            posA.getY() < posB.getY() + hitboxB.getHeight() &&
            posA.getY() + hitboxA.getHeight() > posB.getY());
}
