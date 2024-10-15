#include "UpdateVelocityAI.hh"

void ECS::Systems::UpdateVelocityAI::update(
    ECS::ComponentManager::SparseArray<ECS::Components::Velocity> & velocities,
    ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
    ECS::ComponentManager::SparseArray<ECS::Components::AI> & AIs,
    std::vector<std::size_t> entities) {
    for (std::size_t i = 0; i < entities.size(); i++) {
        if (AIs[entities[i]]->getEnemyType() == PATAPATA) {
            float amplitude = 0.1f;
            float frequency = 2.0f;
            velocities[entities[i]]->setX(-0.05f);
            velocities[entities[i]]->setY(
                amplitude * std::sin(frequency * positions[entities[i]]->getX()));
        }
    }
}
