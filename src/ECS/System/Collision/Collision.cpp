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
    auto &posPlayer = positions[player].value();
    auto &hitboxPlayer = hitboxes[player].value();
    
    for (std::size_t i = 0; i < entities.size(); ++i) {
        std::size_t entity = entities[i];
        auto &posEntity = positions[entity].value();
        auto &hitboxEntity = hitboxes[entity].value();

        if (ECS::Utils::checkCollision(posEntity, hitboxEntity, posPlayer, hitboxPlayer)) {
            if (healths[player]->getInvincibility() == 0) {
                std::cout << "OOF!!" << std::endl;
                healths[player]->modifyHealthBy(-1);
                healths[player]->setInvincibility(200);
            } 
        }
    }
}

void ECS::Systems::Collision::AIHitPod(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> &hitboxes,
    ECS::ComponentManager::SparseArray<ECS::Components::Health> &healths,
    std::vector<std::size_t> &pods, std::vector<std::size_t> &AIs)
{
    for (std::size_t i = 0; i < AIs.size(); i++) {
        if (healths[AIs[i]]->getInvincibility() > 0)
            healths[AIs[i]]->modifyInvincibilityBy(-1);
    }
    for (std::size_t j = 0; j < pods.size(); j++) {
        auto &posPod = positions[pods[j]].value();
        auto &hitboxPod = hitboxes[pods[j]].value();

        for (std::size_t i = 0; i < AIs.size(); ++i) {
            std::size_t AI = AIs[i];
            auto &posAI = positions[AI].value();
            auto &hitboxAI = hitboxes[AI].value();

            if (ECS::Utils::checkCollision(posAI, hitboxAI, posPod, hitboxPod)) {
                if (healths[AI]->getInvincibility() == 0) {
                    std::cout << "pod is working hassoul!!" << std::endl;
                    healths[AI]->modifyHealthBy(-1);
                    healths[AI]->setInvincibility(50);
                } 
            }
        }
    }
}
