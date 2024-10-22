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

        if (aiType == POWARMOR) {
            if (AIs[aiId]->isFiring())
                break;
            velocities[aiId]->setX(-0.1);
            velocities[aiId]->setY(0.01);
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
            std::size_t targetPlayer = getClosestPlayer(positions, aiId, serverToLocalPlayersId);
            if (positions[aiId]->getX() > positions[targetPlayer]->getX())
                velocities[aiId]->setX(-0.033);
            else
                velocities[aiId]->setX(0.033);
        }
    }
}

float ECS::Systems::UpdateVelocityAI::getDistance(
    const std::optional<ECS::Components::Position> & pos1,
    const std::optional<ECS::Components::Position> & pos2) const
{
    float X1 = pos1->getX();
    float Y1 = pos1->getY();
    float X2 = pos2->getX();
    float Y2 = pos2->getY();

    return std::sqrt((X2 - X1) * (X2 - X1) +
                     (Y2 - Y1) * (Y2 - Y1));
}

std::size_t ECS::Systems::UpdateVelocityAI::getClosestPlayer(
    ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
    std::size_t ai, std::map<int, std::size_t> serverToLocalPlayersId) const
{
    float dist = 1000;
    float tempDist = 0;
    std::size_t closestId = 0;

    for (const auto& player : serverToLocalPlayersId) {
        tempDist = getDistance(positions[ai], positions[player.second]);
        if (dist > tempDist) {
            dist = tempDist;
            closestId = player.second;
        }
    }
    return closestId;
}
