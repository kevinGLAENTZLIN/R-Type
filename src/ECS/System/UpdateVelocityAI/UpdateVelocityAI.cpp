#include "UpdateVelocityAI.hh"

void ECS::Systems::UpdateVelocityAI::update (
    ECS::ComponentManager::SparseArray<ECS::Components::Velocity> & velocities,
    ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
    ECS::ComponentManager::SparseArray<ECS::Components::AI> & AIs,
    std::vector<std::size_t> entities,
    const std::map<int, std::size_t> & serverToLocalPlayersId) const
{
    for (std::size_t i = 0; i < entities.size(); i++) {
        std::size_t aiId = entities[i];
        enemiesTypeEnum_t aiType = AIs[aiId]->getEnemyType();

        if (aiType == MINIKIT) {
            float amplitude = 0.05f;
            float frequency = 2.0f;
            velocities[aiId]->setX(0.05f);
            velocities[aiId]->setY(
                amplitude * std::sin(frequency * positions[aiId]->getX()));
        }
        if (aiType == PATAPATA) {
            float amplitude = 0.05f;
            float frequency = 2.0f;
            velocities[aiId]->setX(-0.1f);
            velocities[aiId]->setY(
                amplitude * std::sin(frequency * positions[aiId]->getX()));
        }
        if (aiType == BUG) {
            float amplitude = 0.025f;
            float frequency = 1.0f;
            float offset = 0.01f;
            if (positions[aiId]->getOriginalY() > 0)
                offset *= -1; 
            velocities[aiId]->setX(-0.1f);
            velocities[aiId]->setY(
                amplitude * std::sin(frequency * positions[aiId]->getX()) + offset);
        }
        if (aiType == BINK) {
            velocities[aiId]->setY(0.5);
            if (positions[aiId]->getY() > 4.0)
                velocities[aiId]->setY(0);
            if (AIs[aiId]->isFiring())
                break;
            
            std::vector<std::pair<float, float>> playersPos;
            for (const auto& player : serverToLocalPlayersId)
                playersPos.push_back(positions[player.second]->getPosPair());
            std::size_t targetPlayer = ecsUtils::getClosestPlayer(
                positions[aiId]->getPosPair(), playersPos);
            for (const auto& player : serverToLocalPlayersId)
                if (positions[player.second]->getPosPair() == playersPos[targetPlayer])
                    targetPlayer = player.second;

            if (positions[aiId]->getX() > positions[targetPlayer]->getX())
                velocities[aiId]->setX(-0.033);
            else
                velocities[aiId]->setX(0.033);
        }
    }
}

