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

std::vector<std::size_t> ECS::Systems::Collision::AIHitPod(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> &hitboxes,
    ECS::ComponentManager::SparseArray<ECS::Components::Health> &healths,
    ECS::ComponentManager::SparseArray<ECS::Components::Pod> &pods,
    const std::vector<std::size_t> &podsEntity, const std::vector<std::size_t> &AIs)
{
    std::vector<std::size_t> AIHitByPod;

    for (std::size_t j = 0; j < podsEntity.size(); j++) {
        std::size_t pod = podsEntity[j];

        if (pods[pod]->getPlayer() == 10000)
            continue;

        auto &posPod = positions[pod].value();
        auto &hitboxPod = hitboxes[pod].value();

        for (std::size_t i = 0; i < AIs.size(); ++i) {
            std::size_t AI = AIs[i];
            auto &posAI = positions[AI].value();
            auto &hitboxAI = hitboxes[AI].value();

            if (ECS::Utils::checkCollision(posAI, hitboxAI, posPod, hitboxPod)) {
                if (healths[AI]->getInvincibility() == 0) {
                    std::cout << "pod is working hassoul!!" << std::endl;
                    AIHitByPod.push_back(AI);
                }
            }
        }
    }
    return AIHitByPod;
}

std::vector<std::size_t> ECS::Systems::Collision::PlayerPickedUpPod(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
    ECS::ComponentManager::SparseArray<ECS::Components::Hitbox> & hitboxes,
    ECS::ComponentManager::SparseArray<ECS::Components::Pod> & pods,
    std::vector<std::size_t> & podsEntity, std::vector<std::size_t> & playersEntity)
{
    std::vector<std::size_t> playerPickedUpPod;

    for (std::size_t j = 0; j < podsEntity.size(); j++) {
        std::size_t pod = podsEntity[j];

        if (pods[pod]->getPlayer() < 10000)
            continue;

        auto &posPod = positions[pod].value();
        auto &hitboxPod = hitboxes[pod].value();

        for (std::size_t i = 0; i < playersEntity.size(); ++i) {
            std::size_t player = playersEntity[i];
            auto &posPlayer = positions[player].value();
            auto &hitboxPlayer = hitboxes[player].value();

            if (ECS::Utils::checkCollision(posPlayer, hitboxPlayer, posPod, hitboxPod)) {
                std::cout << "pod is picked up hassoul!!" << std::endl;
                int nbPods = 0;
                int indexPod1 = -1;
                int indexPod2 = -1;
                for (int i = 0; i < podsEntity.size(); i++)
                    if (pods[podsEntity[i]]->getPlayer() == player){
                        if (nbPods == 0)
                            indexPod1 = podsEntity[i];
                        if (nbPods == 1)
                            indexPod2 = podsEntity[i];
                        nbPods++;
                    }
                if (nbPods < 2) {
                    if (nbPods == 0)
                        pods[pod]->setIsUp(true);
                    pods[pod]->setPlayer(player);
                    playerPickedUpPod.push_back(pod);
                    continue;
                }
                std::cout << "pod level: " << pods[indexPod1]->getLevel() << std::endl;
                if (pods[indexPod1]->getLevel() == 0) {
                    pods[indexPod1]->setLevel(1);
                    pods[pod]->setLevel(-1);
                    playerPickedUpPod.push_back(pod);
                    continue;
                }
                if (pods[indexPod2]->getLevel() == 0) {
                    pods[indexPod2]->setLevel(1);
                    pods[pod]->setLevel(-1);
                    playerPickedUpPod.push_back(pod);
                    continue;
                }
                if (pods[indexPod1]->getLevel() == 1 && pods[indexPod1]->getLevel() == 1) {
                    pods[indexPod1]->setLevel(2);
                    pods[indexPod2]->setLevel(2);
                    pods[pod]->setLevel(-1);
                    playerPickedUpPod.push_back(pod);
                    continue;
                }
            }
        }
    }
    return playerPickedUpPod;
}
