#include "UpdateVelocityPataPata.hh"

void ECS::Systems::UpdateVelocityPataPata::update(
    ECS::ComponentManager::SparseArray<ECS::Components::Velocity> & velocities,
    std::vector<std::size_t> pataPatas) {
    for (std::size_t i = 0; i < pataPatas.size(); i++)
        velocities[pataPatas[i]]->setX(-1);
}
