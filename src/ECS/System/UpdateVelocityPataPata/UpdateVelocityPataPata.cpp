#include "UpdateVelocityPataPata.hh"

void ECS::Systems::UpdateVelocityPataPata::update(
    ECS::ComponentManager::SparseArray<ECS::Components::Velocity> & velocities,
    ECS::ComponentManager::SparseArray<ECS::Components::Position> & positions,
    std::vector<std::size_t> pataPatas) {
    for (std::size_t i = 0; i < pataPatas.size(); i++) {
        float amplitude = 0.1f;
        float frequency = 2.0f;
        velocities[pataPatas[i]]->setX(-0.05f);
        velocities[pataPatas[i]]->setY(
            amplitude * std::sin(frequency * positions[pataPatas[i]]->getX()));
    }
}
